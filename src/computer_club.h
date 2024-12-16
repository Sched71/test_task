#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>

#include "event_manager.h"
#include "util_structs.h"

class ComputerClub {
   public:
    using Client = std::string;

    explicit ComputerClub(std::string const& input_data, std::ostream& os)
        : input_(input_data), os(os) {
        if (!input_.is_open()) {
            throw std::runtime_error("Could not open the file");
        }
        CheckInputFormat();
        ParseConfiguration();
        ConfigureEventHandler();
    }

    void ProcessInput();

   private:
    void CheckInputFormat();
    void ParseConfiguration();
    void ConfigureEventHandler();

    bool ClientExists(Client const& client);

    void BeginHandler(Event const& event);
    void EndHandler(Event const& event);
    void ClientEnteringHandler(Event const& event);
    void ClientSitsDownHandler(Event const& event);
    void ClientWaitsHandler(Event const& event);
    void ClientLeftHandler(Event const& event);
    void ClosingClientLeftHandler(Event const& event);
    void QueueClientSitsHandler(Event const& event);
    void ErrorHandler(Event const& event);
    void EmptyHandler(Event const& event) {
        std::cout << event.ToString() << '\n';
    }

    std::ifstream input_;
    std::ostream& os;
    unsigned int hour_price_;
    unsigned int tables_amount_;
    Timespan working_hours_;
    std::set<Client> clients_;
    std::queue<Client> waiting_queue_;
    // Index in vector == TableId - 1
    std::vector<Client> tables_;
    std::vector<std::vector<Timespan>> table_times_;
    EventManager event_manager_;
};
