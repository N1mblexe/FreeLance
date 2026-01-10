#include <core/RosterEngine.hpp>
#include <iostream>

namespace core {

void RosterEngine::generateRoster() {
    std::cout << "Generating roster..." << std::endl;
    while (!availableCrew.isEmpty()) {
        models::Crew currentCrew = availableCrew.pop();
        std::cout << "Assigning: " << currentCrew.getId() << " (Seniority: " << currentCrew.getSeniority() << ")" << std::endl;
        models::Pairing assignedPairing = createPairingForCrew(currentCrew);
        if (assignedPairing.getTotalDutyTime() > 0) {
            roster.put(currentCrew.getId(), assignedPairing);
            std::cout << " -> Success: created pairing for " << currentCrew.getId() << "." << std::endl;
        } else {
            std::cout << " -> Warning: no suitable pairing found for " << currentCrew.getId() << "." << std::endl;
        }
    }
}

RosterEngine::RosterEngine() : allFlights(), availableCrew(), flightNetwork(), roster() {}

void RosterEngine::addFlight(const models::Flight& f) {
    allFlights.push_back(f);
    flightNetwork.addAirport(f.origin);
    flightNetwork.addAirport(f.destination);
}

void RosterEngine::addCrew(const models::Crew& c) { availableCrew.push(c); }

models::Pairing RosterEngine::createPairingForCrew(models::Crew& crew) {
    models::Pairing pairing("P_" + crew.getId());
    std::string currentBase = crew.getBase();
    auto* node = allFlights.getHead();
    while (node) {
        models::Flight& f = node->data;
        if (f.origin == currentBase && Validator::isQualified(crew, f)) {
            auto* node2 = allFlights.getHead();
            while (node2) {
                models::Flight& fReturn = node2->data;
                if (Validator::canConnect(f, fReturn)) {
                    if (fReturn.destination == currentBase) {
                        pairing.addFlight(f);
                        pairing.addFlight(fReturn);
                        if (Validator::isPairingLegal(pairing, crew)) return pairing;
                        models::Pairing emptyPairing("TEMP");
                        pairing = emptyPairing;
                    }
                }
                node2 = node2->next;
            }
        }
        node = node->next;
    }
    return pairing;
}

ds::HashMap<std::string, models::Pairing>* RosterEngine::getRoster() { return &roster; }

}