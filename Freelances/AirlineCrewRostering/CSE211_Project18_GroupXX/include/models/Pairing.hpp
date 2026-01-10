#pragma once

#include "Flight.hpp"
#include "../data_structures/LinkedList.hpp"

namespace models {

    class Pairing {
    private:
        std::string pairingId;
        ds::LinkedList<Flight> flights;
        int totalDutyTime;

    public:
        Pairing(std::string id);

        void addFlight(const Flight& flight);

        ds::LinkedList<Flight>* getFlights();

        int getTotalDutyTime() const;

        bool isValid(const std::string& homeBase);
    };
}