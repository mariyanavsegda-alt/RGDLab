#include "direction.h"
#include <iostream>

Direction::Direction() : id(0), distance(0) {}

Direction::Direction(int id,
                     const std::string& a,
                     const std::string& b,
                     double dist)
    : id(id), stationA(a), stationB(b), distance(dist) {}

int Direction::getId() const { return id; }
std::string Direction::getStationA() const { return stationA; }
std::string Direction::getStationB() const { return stationB; }
double Direction::getDistance() const { return distance; }

void Direction::print() const {
    std::cout << "ID: " << id
              << " | " << stationA
              << " - " << stationB
              << " | distance: "
              << distance << " km\n";
}

void Direction::save(std::ofstream& out) const {
    out << id << "\n"
        << stationA << "\n"
        << stationB << "\n"
        << distance << "\n";
}

void Direction::load(std::ifstream& in) {
    in >> id;
    in.ignore();
    std::getline(in, stationA);
    std::getline(in, stationB);
    in >> distance;
    in.ignore();
}
