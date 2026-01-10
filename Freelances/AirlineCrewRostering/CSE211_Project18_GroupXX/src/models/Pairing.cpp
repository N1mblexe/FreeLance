#include <models/Pairing.hpp>
#include <models/Flight.hpp>

using namespace models;

Pairing::Pairing(std::string id) : pairingId(id), totalDutyTime(0) {}

Pairing::Pairing(const Pairing& other) : pairingId(other.pairingId), totalDutyTime(other.totalDutyTime) {
	auto* node = other.flights.getHead();
	while (node) {
		flights.push_back(node->data);
		node = node->next;
	}
}

Pairing& Pairing::operator=(const Pairing& other) {
	if (this == &other) return *this;
	pairingId = other.pairingId;
	totalDutyTime = other.totalDutyTime;
	flights.clear();
	auto* node = other.flights.getHead();
	while (node) {
		flights.push_back(node->data);
		node = node->next;
	}
	return *this;
}

Pairing::Pairing(Pairing&& other) noexcept : pairingId(other.pairingId), totalDutyTime(other.totalDutyTime) {
	auto* node = other.flights.getHead();
	while (node) {
		flights.push_back(node->data);
		node = node->next;
	}
	other.flights.clear();
	other.totalDutyTime = 0;
}

Pairing& Pairing::operator=(Pairing&& other) noexcept {
	if (this == &other) return *this;
	pairingId = other.pairingId;
	totalDutyTime = other.totalDutyTime;
	flights.clear();
	auto* node = other.flights.getHead();
	while (node) {
		flights.push_back(node->data);
		node = node->next;
	}
	other.flights.clear();
	other.totalDutyTime = 0;
	return *this;
}

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
	while (last->next) last = last->next;
	return (first->data.origin == homeBase) && (last->data.destination == homeBase);
}
