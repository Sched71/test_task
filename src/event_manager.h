#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>

#include "util_structs.h"

struct Event {
    TimePoint event_time;
    int id;
    std::string data;
    std::string ToString() const {
        std::stringstream ss;
        ss << event_time << " " << id << " " << data;
        return ss.str();
    }
};

using EventHandler = std::function<void(const Event&)>;

class EventManager {
   public:
    EventManager() : stop_processing(false) {
        event_thread = std::thread(&EventManager::processEvents, this);
    }

    ~EventManager() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            stop_processing = true;
        }
        condition.notify_one();
        if (event_thread.joinable()) {
            event_thread.join();
        }
    }

    void AddEventHandler(int event_id, const EventHandler& handler) {
        std::unique_lock<std::mutex> lock(mutex);
        event_handlers[event_id] = handler;
    }

    void QueueEvent(const Event& event) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            event_queue.push(event);
        }
        condition.notify_one();
    }

    void TriggerEvent(const Event& event) {
        if (event_handlers.find(event.id) != event_handlers.end()) {
            event_handlers[event.id](event);
        }
    }

   private:
    void processEvents() {
        while (true) {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this] {
                return !event_queue.empty() || stop_processing;
            });

            if (stop_processing && event_queue.empty()) {
                break;
            }

            while (!event_queue.empty()) {
                Event event = event_queue.front();
                event_queue.pop();
                TriggerEvent(event);
            }
        }
    }

    std::unordered_map<int, EventHandler> event_handlers;
    std::queue<Event> event_queue;
    std::thread event_thread;
    std::mutex mutex;
    std::condition_variable condition;
    bool stop_processing;
};
