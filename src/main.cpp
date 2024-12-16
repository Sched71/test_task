#include <fstream>

#include "computer_club.h"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Incorrect number of arguments. Program accepts 1 argument with input file path" << '\n';
        return -1;
    }
    try {
        ComputerClub c(argv[1], std::cout);
        c.ProcessInput();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
