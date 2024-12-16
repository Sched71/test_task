#include <fstream>

#include "computer_club.h"

int main() {
    try {
        ComputerClub c("../input", std::cout);
        c.ProcessInput();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
