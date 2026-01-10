#pragma once

#include <models/Flight.hpp>
#include <models/Crew.hpp>
#include <models/Pairing.hpp>
#include <string>

namespace core {

class Validator {
public:
    static bool canConnect(const models::Flight& f1, const models::Flight& f2, int minRestTime = 60);
    static bool isQualified(models::Crew& crew, const models::Flight& flight);
    static bool isPairingLegal(models::Pairing& pairing, const models::Crew& crew, int maxDutyTime = 840);
};

}