#pragma once

#include <string>

namespace models {

    struct Flight {
        std::string id;
        std::string origin;
        std::string destination;
        int departureTime; 
        int arrivalTime;   
        std::string aircraftType;

        Flight();

        Flight(std::string fId, std::string from, std::string to, int dept, int arr, std::string type);

        int getDuration() const;

        bool operator==(const Flight& other) const;
    };
}