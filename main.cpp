#include "computer_club.h"

#include <fstream>

int main(int argc, char const *argv[]) {
    ComputerClub c("../input", std::cout);
    c.ProcessInput();
    return 0;
}

