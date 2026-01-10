/**
 * @file Pairing.hpp
 * @brief Pairing groups flights into a duty pairing for a crew member.
 */

#pragma once

#include <models/Flight.hpp>
#include <data_structures/LinkedList.hpp>
#include <string>

namespace models {

/**
 * @class Pairing
 * @brief Represents a sequence of flights assigned as a single pairing.
 */
class Pairing {
private:
    std::string pairingId;
    ds::LinkedList<Flight> flights;
    int totalDutyTime;

public:
    Pairing(std::string id);
    Pairing(const Pairing& other);
    Pairing& operator=(const Pairing& other);
    Pairing(Pairing&& other) noexcept;
    Pairing& operator=(Pairing&& other) noexcept;
    void addFlight(const Flight& flight);
    ds::LinkedList<Flight>* getFlights();
    int getTotalDutyTime() const;
    bool isValid(const std::string& homeBase);
};

}