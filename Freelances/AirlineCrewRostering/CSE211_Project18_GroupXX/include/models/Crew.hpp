#include <string>
#include <data_structures/LinkedList.hpp>

/**
 * @file Crew.hpp
 * @brief Crew model representing a crew member and their attributes.
 */

#pragma once

namespace models {

/**
 * @enum CrewRole
 * @brief Role of a crew member.
 */
enum class CrewRole { PILOT, ATTENDANT };

/**
 * @class Crew
 * @brief Represents an individual crew member with qualifications and hours.
 */
class Crew {
private:
    std::string id;
    std::string name;
    CrewRole role;
    std::string baseAirport;
    int seniorityLevel;
    ds::LinkedList<std::string> qualifications;
    int accumulatedFlightHours;

public:
    Crew();
    Crew(std::string cId, std::string cName, CrewRole cRole, std::string base, int seniority);
    Crew(const Crew& other);
    Crew& operator=(const Crew& other);
    Crew(Crew&& other) noexcept;
    Crew& operator=(Crew&& other) noexcept;
    std::string getId() const;
    std::string getBase() const;
    int getSeniority() const;
    int getHours() const;
    void addQualification(const std::string& aircraftType);
    bool hasQualification(const std::string& aircraftType);
    void addFlightHours(int hours);
    bool operator>(const Crew& other) const;
    bool operator==(const Crew& other) const;
};

}