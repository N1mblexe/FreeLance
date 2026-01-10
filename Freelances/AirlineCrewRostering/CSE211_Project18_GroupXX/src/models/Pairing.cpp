#include <models/Pairing.hpp>
#include <models/Flight.hpp>

using namespace models;

Pairing::Pairing(std::string id) : pairingId(id), totalDutyTime(0) {}

void Pairing::addFlight(const Flight& flight) {
	flights.push_back(flight);
	totalDutyTime += flight.getDuration();
}

ds::LinkedList<Flight>* Pairing::getFlights() { return &flights; }

int Pairing::getTotalDutyTime() const { return totalDutyTime; }

bool Pairing::isValid(const std::string& homeBase) {
	if (flights.isEmpty()) return true;

	auto* first = flights.getHead();
	auto* last = flights.getHead();
	while (last->next) {
		last = last->next;
	}

	return (first->data.origin == homeBase) && (last->data.destination == homeBase);
}
