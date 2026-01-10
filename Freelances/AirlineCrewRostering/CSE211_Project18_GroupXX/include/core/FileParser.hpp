/**
 * @file FileParser.hpp
 * @brief Lightweight parser for the project's JSON-like sample data format.
 */

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <core/RosterEngine.hpp>
#include <models/Flight.hpp>
#include <models/Crew.hpp>

namespace core {

/**
 * @class FileParser
 * @brief Parses a simplified JSON dataset and populates the `RosterEngine`.
 */
class FileParser {
public:
    /**
     * @brief Load flights and crews from `filename` into `engine`.
     */
    static void loadData(const std::string& filename, RosterEngine& engine);

private:
    static std::string extractValue(const std::string& block, const std::string& key);
    static std::vector<std::string> extractArray(const std::string& block, const std::string& key);
    static int timeToMinutes(const std::string& timeStr);
};

}