#include "computer_club.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>

#include "event_manager.h"

void ComputerClub::ParseConfiguration() {
    try {
        input_ >> tables_amount_;
        tables_.resize(tables_amount_);
        input_ >> working_hours_.start;
        input_ >> working_hours_.end;
        input_ >> hour_price_;
        // To later use std::getline
        input_.ignore();
    } catch (std::exception const& err) {
        std::cerr << "Error during configuration parsing. Exactly:\n";
        std::cerr << err.what() << '\n';
        throw err;
    }
}

void ComputerClub::ProcessInput() {
    event_manager_.QueueEvent({TimePoint{}, -1, ""});
    std::string line;
    TimePoint previous_event_time{0, 0};
    while (std::getline(input_, line)) {
        try {
            std::istringstream iss(line);
            Event e;
            iss >> e.event_time;
            iss >> e.id;
            // To skip whitespace for prettier output later
            iss.ignore();
            std::getline(iss, e.data);

            if (e.event_time < previous_event_time) {
                std::string error_msg = "Event out of order: " + e.ToString();
                throw std::runtime_error(error_msg);
            }

            event_manager_.QueueEvent(e);
            previous_event_time = e.event_time;

        } catch (std::exception const& err) {
            std::cerr << "Error during processing input events:\n";
            std::cerr << err.what() << '\n';
            throw err;
        }
    }
    event_manager_.QueueEvent({TimePoint{}, 0, ""});
}

bool ComputerClub::ClientExists(Client const& client) {
    auto it_q = clients_.find(client);
    return it_q != clients_.end();
}

void ComputerClub::ConfigureEventHandler() {
    event_manager_.AddEventHandler(-1, std::bind(&ComputerClub::BeginHandler,
                                                 this, std::placeholders::_1));
    event_manager_.AddEventHandler(
        0, std::bind(&ComputerClub::EndHandler, this, std::placeholders::_1));
    event_manager_.AddEventHandler(
        1, std::bind(&ComputerClub::ClientEnteringHandler, this,
                     std::placeholders::_1));
    event_manager_.AddEventHandler(
        2, std::bind(&ComputerClub::ClientSitsDownHandler, this,
                     std::placeholders::_1));
    event_manager_.AddEventHandler(
        3, std::bind(&ComputerClub::ClientWaitsHandler, this,
                     std::placeholders::_1));
    event_manager_.AddEventHandler(
        4, std::bind(&ComputerClub::ClientLeftHandler, this,
                     std::placeholders::_1));
    event_manager_.AddEventHandler(
        11, std::bind(&ComputerClub::ClosingClientLeftHandler, this,
                      std::placeholders::_1));
    event_manager_.AddEventHandler(
        12, std::bind(&ComputerClub::QueueClientSitsHandler, this,
                      std::placeholders::_1));
    event_manager_.AddEventHandler(13, std::bind(&ComputerClub::ErrorHandler,
                                                 this, std::placeholders::_1));
}

void ComputerClub::BeginHandler(Event const& event) {
    os << working_hours_.start << '\n';
}

void ComputerClub::EndHandler(Event const& event) {
    for (Client const& client : clients_) {
        event_manager_.TriggerEvent({working_hours_.end, 11, client});
    }
    os << working_hours_.end << '\n';
}

void ComputerClub::ErrorHandler(Event const& event) {
    os << event.ToString() << '\n';
}

void ComputerClub::ClientEnteringHandler(Event const& event) {
    os << event.ToString() << '\n';
    if (!working_hours_.IsIn(event.event_time)) {
        event_manager_.TriggerEvent({event.event_time, 13, "NotOpenYet"});
        return;
    }
    if (ClientExists(event.data)) {
        event_manager_.TriggerEvent({event.event_time, 13, "YouShallNotPass"});
        return;
    }
    clients_.emplace(event.data);
}

void ComputerClub::ClientSitsDownHandler(Event const& event) {
    os << event.ToString() << '\n';
    Client client;
    unsigned table_id;
    std::stringstream ss(event.data);
    ss >> client;
    ss >> table_id;
    if (tables_[table_id - 1] != "") {
        event_manager_.TriggerEvent({event.event_time, 13, "PlaceIsBusy"});
        return;
    }
    if (!ClientExists(client)) {
        event_manager_.TriggerEvent({event.event_time, 13, "ClientUnknown"});
        return;
    }
    auto table_it = std::find(tables_.begin(), tables_.end(), client);
    if (table_it != tables_.end()) {
        *table_it = "";
    }
    tables_[table_id - 1] = client;
}

void ComputerClub::ClientWaitsHandler(Event const& event) {
    os << event.ToString() << '\n';
    auto table_it = std::find(tables_.begin(), tables_.end(), "");
    if (table_it != tables_.end()) {
        event_manager_.TriggerEvent(
            {event.event_time, 13, "ICanWaitNoLonger!"});
        return;
    }
    if (waiting_queue_.size() > tables_amount_) {
        event_manager_.TriggerEvent({event.event_time, 11, ""});
        return;
    }
    waiting_queue_.push(event.data);
}

void ComputerClub::ClientLeftHandler(Event const& event) {
    os << event.ToString() << '\n';
    Client client{event.data};
    if (!ClientExists(client)) {
        event_manager_.TriggerEvent({event.event_time, 13, "ClientUnknown"});
        return;
    }
    auto table_it = std::find(tables_.begin(), tables_.end(), client);
    if (table_it != tables_.end()) {
        *table_it = "";
        if (!waiting_queue_.empty()) {
            Client next_client{waiting_queue_.back()};
            event_manager_.TriggerEvent({event.event_time, 12, next_client});
            *table_it = next_client;
            waiting_queue_.pop();
        }
    }
    clients_.erase(client);
}

void ComputerClub::ClosingClientLeftHandler(Event const& event) {
    os << event.ToString() << '\n';
}

void ComputerClub::QueueClientSitsHandler(Event const& event) {
    os << event.ToString() << '\n';
}
