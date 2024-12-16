#include "computer_club.h"

#include <fstream>

int main(int argc, char const *argv[]) {
    try {
        ComputerClub c("../input", std::cout);
        c.ProcessInput();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}

