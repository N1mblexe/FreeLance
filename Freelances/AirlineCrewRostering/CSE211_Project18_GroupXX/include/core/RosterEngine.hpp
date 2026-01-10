/**
 * @file RosterEngine.hpp
 * @brief High-level engine that creates pairings and assigns crews.
 */

#pragma once

#include <data_structures/LinkedList.hpp>
#include <data_structures/PriorityQueue.hpp>
#include <data_structures/HashMap.hpp>
#include <data_structures/Graph.hpp>
#include <models/Crew.hpp>
#include <models/Flight.hpp>
#include <models/Pairing.hpp>
#include <core/Validator.hpp>

namespace core {

/**
 * @class RosterEngine
 * @brief Orchestrates loading flights/crews and generating a roster.
 */
class RosterEngine {
private:
    ds::LinkedList<models::Flight> allFlights;
    ds::PriorityQueue<models::Crew> availableCrew;
    ds::Graph flightNetwork;
    ds::HashMap<std::string, models::Pairing> roster;

public:
    RosterEngine();
    void addFlight(const models::Flight& f);
    void addCrew(const models::Crew& c);
    void generateRoster();
    models::Pairing createPairingForCrew(models::Crew& crew);
    ds::HashMap<std::string, models::Pairing>* getRoster();
};

}