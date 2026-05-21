#include "passenger.h"

Passenger::Passenger(const std::string& name)
    : fullName(name) {}

std::string Passenger::getName() const {
    return fullName;
}