#include <core/Validator.hpp>

namespace core {

bool Validator::canConnect(const models::Flight& f1, const models::Flight& f2, int minRestTime) {
    if (f1.destination != f2.origin) return false;
    if (f1.arrivalTime + minRestTime > f2.departureTime) return false;
    return true;
}

bool Validator::isQualified(models::Crew& crew, const models::Flight& flight) {
    return crew.hasQualification(flight.aircraftType);
}

bool Validator::isPairingLegal(models::Pairing& pairing, const models::Crew& crew, int maxDutyTime) {
    if (pairing.getTotalDutyTime() > maxDutyTime) return false;
    long currentMinutes = crew.getHours() * 60;
    if ((currentMinutes + pairing.getTotalDutyTime()) > 6000) return false;
    auto* flights = pairing.getFlights();
    if (flights->isEmpty()) return true;
    if (flights->getHead()->data.origin != crew.getBase()) return false;
    auto* curr = flights->getHead();
    while (curr->next != nullptr) curr = curr->next;
    if (curr->data.destination != crew.getBase()) return false;
    return true;
}

}