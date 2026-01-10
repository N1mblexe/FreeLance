#pragma once

#include <string>
#include "../data_structures/LinkedList.hpp"

namespace models {

    enum class CrewRole {
        PILOT,
        ATTENDANT
    };

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