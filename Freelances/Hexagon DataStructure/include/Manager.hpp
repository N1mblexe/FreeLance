#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Hexagon.hpp"
#include <string>

class Manager
{
public:
    Manager();
    ~Manager();
    void readDataFile(const char *filename);
    void runSimulation(int turns);
    void visualize(bool showDetails = false) const;

private:
    Hexagon **hexagons;
    int hexagonCount;

    mutable std::string accumulated;
    void flushAccumulated() const;
};

#endif // MANAGER_HPP
