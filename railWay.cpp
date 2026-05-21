#include "railWay.h"
#include <iostream>
#include <fstream>

/**
 * @brief Конструктор системы РЖД
 */
RailwaySystem::RailwaySystem()
    : currentTime(0),
      nextDirectionId(1),
      nextTrainId(1) {}


/**
 * @brief Добавление нового направления
 */
void RailwaySystem::addDirection(const std::string& a,
                                 const std::string& b,
                                 double dist) {

    directions.emplace_back(nextDirectionId++, a, b, dist);

    std::cout << "Direction added successfully.\n";
}


/**
 * @brief Добавление нового поезда
 */
void RailwaySystem::addTrain(int directionId,
                             int capacity,
                             double speed,
                             double departure) {

    for (auto& d : directions) {
        if (d.getId() == directionId) {

            trains.emplace_back(nextTrainId++,
                                &d,
                                capacity,
                                speed,
                                departure);

            std::cout << "Train added successfully.\n";
            return;
        }
    }

    std::cout << "Direction not found.\n";
}


/**
 * @brief Покупка билета
 */
void RailwaySystem::buyTicket(int trainId,
                              const std::string& name) {

    for (auto& t : trains) {
        if (t.getId() == trainId) {

            if (t.hasFreeSeats()) {
                t.addPassenger(name);
                std::cout << "Ticket purchased.\n";
            } else {
                std::cout << "No free seats available.\n";
            }
            return;
        }
    }

    std::cout << "Train not found.\n";
}


/**
 * @brief Возврат билета
 */
void RailwaySystem::returnTicket(int trainId,
                                 const std::string& name) {

    for (auto& t : trains) {
        if (t.getId() == trainId) {

            t.removePassenger(name);
            std::cout << "Ticket returned.\n";
            return;
        }
    }

    std::cout << "Train not found.\n";
}


/**
 * @brief Промотка времени в системе
 *
 * Увеличивает текущее системное время
 * и обновляет состояние всех поездов.
 */
void RailwaySystem::advanceTime(double hours) {

    
    std::cout << "Current system time: "
              << currentTime << " hours\n";

    currentTime += hours;

    std::cout << "Time advanced by "
              << hours << " hours\n";

    std::cout << "New system time: "
              << currentTime << " hours\n\n";

    for (auto& t : trains) {
        t.update(currentTime, hours);
    }
}


/**
 * @brief Вывод всех направлений
 */
void RailwaySystem::showDirections() const {

    if (directions.empty()) {
        std::cout << "No directions available.\n";
        return;
    }

    for (const auto& d : directions) {
        d.print();
    }
}


/**
 * @brief Вывод всех поездов
 */
void RailwaySystem::showTrains() const {

    if (trains.empty()) {
        std::cout << "No trains available.\n";
        return;
    }

    for (const auto& t : trains) {
        t.print();
    }
}


/**
 * @brief Сохранение данных в файл
 */
void RailwaySystem::saveToFile() const {

    std::ofstream out("railway_save.txt");

    if (!out.is_open()) {
        std::cout << "Error opening file for saving.\n";
        return;
    }

    // Сохраняем текущее время
    out << currentTime << "\n";

    // Сохраняем направления
    out << directions.size() << "\n";
    for (const auto& d : directions)
        d.save(out);

    // Сохраняем поезда
    out << trains.size() << "\n";
    for (const auto& t : trains)
        t.save(out);

    out.close();

    std::cout << "Data saved successfully.\n";
}


/**
 * @brief Загрузка данных из файла
 */
void RailwaySystem::loadFromFile() {

    std::ifstream in("railway_save.txt");

    if (!in.is_open())
        return;

    directions.clear();
    trains.clear();

    in >> currentTime;

    
    size_t dirCount;
    in >> dirCount;

    for (size_t i = 0; i < dirCount; ++i) {
        Direction d;
        d.load(in);
        directions.push_back(d);
    }

    
    size_t trainCount;
    in >> trainCount;

    for (size_t i = 0; i < trainCount; ++i) {
        Train t;
        t.load(in, directions);
        trains.push_back(t);
    }

    in.close();

    std::cout << "Data loaded successfully.\n";
}