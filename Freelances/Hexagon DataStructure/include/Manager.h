#ifndef MANAGER_H
#define MANAGER_H

#include "Hexagon.h"

class Manager
{
public:
    Manager();
    ~Manager();
    void readDataFile(const char *filename);
    void runSimulation(int turns);
    void visualize() const;
    void setDebug(bool d);

private:
    Hexagon **hexagons;
    int hexagonCount;
    bool debugMode;
};

#endif // MANAGER_H
