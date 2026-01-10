#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <data_structures/LinkedList.hpp>
#include <data_structures/Graph.hpp>
#include <data_structures/PriorityQueue.hpp>
#include <data_structures/HashMap.hpp>

#include <models/Flight.hpp>
#include <models/Crew.hpp>
#include <models/Pairing.hpp>

#include <core/RosterEngine.hpp>
#include <core/Validator.hpp>
#include <core/FileParser.hpp>

int main(int argc, char** argv) {
    using namespace ds;
    using namespace models;
    using namespace core;
    std::string dataFile = "data/sample_data.json";
    bool verbose = false;
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        if (a == "-v" || a == "--verbose") verbose = true;
        else dataFile = a;
    }

    std::cout << "=== Airline Rostering Runner ===\n";
    std::cout << "Data file: " << dataFile << "\n";

    std::ifstream f(dataFile);
    if (!f.is_open()) {
        std::cerr << "Failed to open data file: " << dataFile << "\n";
        return 1;
    }
    std::stringstream ss; ss << f.rdbuf();
    std::string content = ss.str();
    f.close();

    std::vector<std::string> crewIds;
    size_t crewPos = content.find("\"crew\"");
    if (crewPos != std::string::npos) {
        size_t cursor = crewPos;
        while (true) {
            size_t idPos = content.find("\"id\"", cursor);
            if (idPos == std::string::npos) break;
            size_t brace = content.rfind('{', idPos);
            if (brace == std::string::npos) break;
            size_t quote = content.find('"', idPos + 4);
            if (quote == std::string::npos) break;
            size_t quote2 = content.find('"', quote + 1);
            if (quote2 == std::string::npos) break;
            std::string id = content.substr(quote + 1, quote2 - quote - 1);
            if (std::find(crewIds.begin(), crewIds.end(), id) == crewIds.end()) crewIds.push_back(id);
            cursor = quote2 + 1;
        }
    }

    RosterEngine engine;
    FileParser::loadData(dataFile, engine);
    engine.generateRoster();

    std::cout << "\n=== Assignment Summary ===\n";
    auto roster = engine.getRoster();
    for (auto &cid : crewIds) {
        auto pairingPtr = roster->get(cid);
        if (pairingPtr) {
            int flights = pairingPtr->getFlights() ? pairingPtr->getFlights()->getSize() : 0;
            std::cout << cid << ": assigned (" << flights << " flights, " << pairingPtr->getTotalDutyTime() << " mins)\n";
        } else {
            std::cout << cid << ": unassigned\n";
        }
    }

    std::cout << "\nRunner finished." << std::endl;
    if (verbose) std::cout << "(Verbose mode enabled)\n";
    return 0;
}
