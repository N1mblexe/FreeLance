#include "../include/Manager.h"
#include <iostream>
#include <cstring>

int main(int argc, char **argv)
{
    Manager manager;
    bool debug = false;
    if (argc > 1)
    {
        if (std::strcmp(argv[1], "debug") == 0 || std::strcmp(argv[1], "-d") == 0)
            debug = true;
    }
    manager.setDebug(debug);
    manager.readDataFile("Data.txt");
    int turns;
    std::cout << "Enter number of turns: ";
    std::cin >> turns;
    manager.runSimulation(turns);
    return 0;
}
