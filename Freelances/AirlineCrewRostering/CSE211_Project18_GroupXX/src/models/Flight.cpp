#include <models/Flight.hpp>

using namespace models;

Flight::Flight() : departureTime(0), arrivalTime(0) {}

Flight::Flight(std::string fId, std::string from, std::string to, int dept, int arr, std::string type)
	: id(fId), origin(from), destination(to), departureTime(dept), arrivalTime(arr), aircraftType(type) {}

int Flight::getDuration() const { return arrivalTime - departureTime; }

bool Flight::operator==(const Flight& other) const { return id == other.id; }
