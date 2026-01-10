#include <models/Crew.hpp>

using namespace models;

Crew::Crew() : seniorityLevel(0), accumulatedFlightHours(0) {}

Crew::Crew(std::string cId, std::string cName, CrewRole cRole, std::string base, int seniority)
	: id(cId), name(cName), role(cRole), baseAirport(base), seniorityLevel(seniority), accumulatedFlightHours(0) {}

std::string Crew::getId() const { return id; }
std::string Crew::getBase() const { return baseAirport; }
int Crew::getSeniority() const { return seniorityLevel; }
int Crew::getHours() const { return accumulatedFlightHours; }

void Crew::addQualification(const std::string& aircraftType) { qualifications.push_back(aircraftType); }

bool Crew::hasQualification(const std::string& aircraftType) {
	auto* node = qualifications.getHead();
	while (node) {
		if (node->data == aircraftType) return true;
		node = node->next;
	}
	return false;
}

void Crew::addFlightHours(int hours) { accumulatedFlightHours += hours; }

bool Crew::operator>(const Crew& other) const { return seniorityLevel > other.seniorityLevel; }

bool Crew::operator==(const Crew& other) const { return id == other.id; }
