#include "../../include/core/FileParser.hpp"
#include <vector>

namespace core {

int FileParser::timeToMinutes(const std::string& timeStr) {
    if (timeStr.find(':') == std::string::npos) return 0;
    int h = std::stoi(timeStr.substr(0, 2));
    int m = std::stoi(timeStr.substr(3, 2));
    return h * 60 + m;
}

std::string FileParser::extractValue(const std::string& block, const std::string& key) {
    std::string searchKey = "\"" + key + "\":";
    size_t pos = block.find(searchKey);
    if (pos == std::string::npos) return "";

    size_t after = pos + searchKey.length();
    while (after < block.size() && isspace((unsigned char)block[after])) ++after;

    if (after < block.size() && block[after] == '"') {
        size_t start = block.find('"', after);
        if (start == std::string::npos) return "";
        start++;
        size_t end = block.find('"', start);
        if (end == std::string::npos) return "";
        return block.substr(start, end - start);
    } else {
        size_t start = after;
        while (start < block.size() && isspace((unsigned char)block[start])) ++start;
        size_t end = start;
        while (end < block.size() && block[end] != ',' && block[end] != '}' && block[end] != ']') ++end;
        std::string val = block.substr(start, end - start);
        size_t a = 0; while (a < val.size() && isspace((unsigned char)val[a])) ++a;
        size_t b = val.size(); while (b > a && isspace((unsigned char)val[b-1])) --b;
        return val.substr(a, b - a);
    }
}

std::vector<std::string> FileParser::extractArray(const std::string& block, const std::string& key) {
    std::vector<std::string> out;
    std::string searchKey = "\"" + key + "\":";
    size_t pos = block.find(searchKey);
    if (pos == std::string::npos) return out;

    size_t arrStart = block.find('[', pos);
    if (arrStart == std::string::npos) return out;
    size_t cur = arrStart + 1;
    while (true) {
        size_t q = block.find('"', cur);
        if (q == std::string::npos) break;
        size_t q2 = block.find('"', q + 1);
        if (q2 == std::string::npos) break;
        out.push_back(block.substr(q + 1, q2 - q - 1));
        cur = q2 + 1;
        size_t closing = block.find(']', cur);
        if (closing == std::string::npos) continue;
        size_t nextQ = block.find('"', cur);
        if (nextQ == std::string::npos || nextQ > closing) break;
    }
    return out;

}

void FileParser::loadData(const std::string& filename, RosterEngine& engine) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: failed to open file: " << filename << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    size_t flightsStart = content.find("\"flights\"");
    size_t flightsEnd = content.find("\"crew\"");

    if (flightsStart != std::string::npos) {
        size_t cursor = flightsStart;
        while (true) {
            size_t objStart = content.find('{', cursor);
            size_t objEnd = content.find('}', objStart);
            if (objStart == std::string::npos || (flightsEnd != std::string::npos && objStart > flightsEnd)) break;

            std::string objBlock = content.substr(objStart, objEnd - objStart + 1);

            std::string id = extractValue(objBlock, "id");
            std::string from = extractValue(objBlock, "from");
            std::string to = extractValue(objBlock, "to");
            std::string depStr = extractValue(objBlock, "depart");
            std::string arrStr = extractValue(objBlock, "arrive");
            std::string aircraft = extractValue(objBlock, "aircraft");

            if (!id.empty()) {
                models::Flight f(id, from, to, timeToMinutes(depStr), timeToMinutes(arrStr), aircraft);
                engine.addFlight(f);
            }

            cursor = objEnd + 1;
        }
    }

    size_t crewStart = content.find("\"crew\"");
    if (crewStart != std::string::npos) {
        size_t cursor = crewStart;
        while (true) {
            size_t objStart = content.find('{', cursor);
            size_t objEnd = content.find('}', objStart);
            if (objStart == std::string::npos) break;

            std::string objBlock = content.substr(objStart, objEnd - objStart + 1);

            std::string id = extractValue(objBlock, "id");
            std::string roleStr = extractValue(objBlock, "role");
            std::string base = extractValue(objBlock, "base");

            int seniority = 1;
            std::string seniorityStr = extractValue(objBlock, "seniority");
            if (!seniorityStr.empty()) {
                try { seniority = std::stoi(seniorityStr); } catch(...) { seniority = 1; }
            }

            models::CrewRole role = (roleStr == "pilot") ? models::CrewRole::PILOT : models::CrewRole::ATTENDANT;

            if (!id.empty()) {
                models::Crew c(id, id, role, base, seniority);

                auto quals = extractArray(objBlock, "qualifications");
                for (auto &q : quals) c.addQualification(q);

                engine.addCrew(c);
            }

            cursor = objEnd + 1;
        }
    }

    std::cout << "Data load complete." << std::endl;
}

}