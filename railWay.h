#ifndef RAILWAYSYSTEM_H
#define RAILWAYSYSTEM_H

#include <vector>
#include "direction.h"
#include "train.h"

/**
 * @brief Главный класс системы РЖД
 */
class RailwaySystem {
private:
    std::vector<Direction> directions; 
    std::vector<Train> trains;         

    double currentTime;                
    int nextDirectionId;
    int nextTrainId;

public:

    RailwaySystem();

    void addDirection(const std::string& a,
                      const std::string& b,
                      double dist);

    void addTrain(int directionId,
                  int capacity,
                  double speed,
                  double departure);

    void buyTicket(int trainId,
                   const std::string& name);

    void returnTicket(int trainId,
                      const std::string& name);

    /**
     * @brief Промотка времени
     * @param hours количество часов
     */
    void advanceTime(double hours);

    void showDirections() const;
    void showTrains() const;

    void saveToFile() const;
    void loadFromFile();
};

#endif