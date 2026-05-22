#include "train.h"
#include <iostream>

Train::Train()
    : id(0), direction(nullptr), capacity(0),
      speed(0), departureTime(0),
      currentPosition(0),
      status(TrainStatus::WAITING) {}

Train::Train(int id,
             Direction* dir,
             int cap,
             double spd,
             double dep)
    : id(id), direction(dir), capacity(cap),
      speed(spd), departureTime(dep),
      currentPosition(0),
      status(TrainStatus::WAITING) {}

int Train::getId() const { return id; }

bool Train::hasFreeSeats() const {
    return passengers.size() < capacity;
}

void Train::addPassenger(const std::string& name) {
    if (hasFreeSeats())
        passengers.emplace_back(name);
}

void Train::removePassenger(const std::string& name) {
    for (auto it = passengers.begin(); it != passengers.end(); ++it)
        if (it->getName() == name) {
            passengers.erase(it);
            break;
        }
}

void Train::update(double currentTime, double deltaTime) {

    if (status == TrainStatus::WAITING &&
        currentTime >= departureTime) {
        status = TrainStatus::ON_ROUTE_AB;
        std::cout << "Train " << id << " departed.\n";
    }

    if (status == TrainStatus::ON_ROUTE_AB) {
        currentPosition += speed * deltaTime;

        if (currentPosition >= direction->getDistance()) {
            currentPosition = direction->getDistance();
            status = TrainStatus::ON_ROUTE_BA;
            std::cout << "Train " << id << " arrived at destination.\n";
        }
    }
    else if (status == TrainStatus::ON_ROUTE_BA) {
        currentPosition -= speed * deltaTime;

        if (currentPosition <= 0) {
            currentPosition = 0;
            status = TrainStatus::WAITING;
            departureTime = currentTime + 5;
            passengers.clear();
            std::cout << "Train " << id << " returned to origin.\n";
        }
    }
}

void Train::print() const {

    std::cout << "\nTrain ID: " << id << "\n";
    std::cout << "Route: "
              << direction->getStationA()
              << " - "
              << direction->getStationB()
              << "\n";

    std::cout << "Passengers: "
              << passengers.size()
              << "/" << capacity << "\n";

    std::cout << "Current position: "
              << currentPosition << " km\n";

    if (status == TrainStatus::WAITING)
        std::cout << "Status: WAITING\n";
    else if (status == TrainStatus::ON_ROUTE_AB)
        std::cout << "Status: Moving A -> B\n";
    else
        std::cout << "Status: Moving B -> A\n";
}

void Train::save(std::ofstream& out) const {

    out << id << "\n"
        << direction->getId() << "\n"
        << capacity << "\n"
        << speed << "\n"
        << departureTime << "\n"
        << currentPosition << "\n"
        << static_cast<int>(status) << "\n";

    out << passengers.size() << "\n";
    for (const auto& p : passengers)
        out << p.getName() << "\n";
}

void Train::load(std::ifstream& in,
                 std::vector<Direction>& directions) {

    int directionId;
    int statusInt;
    int passengerCount;

    in >> id;
    in >> directionId;
    in >> capacity;
    in >> speed;
    in >> departureTime;
    in >> currentPosition;
    in >> statusInt;
    status = static_cast<TrainStatus>(statusInt);

    for (auto& d : directions)
        if (d.getId() == directionId)
            direction = &d;

    in >> passengerCount;
    in.ignore();

    passengers.clear();
    for (int i = 0; i < passengerCount; ++i) {
        std::string name;
        std::getline(in, name);
        passengers.emplace_back(name);
    }
}