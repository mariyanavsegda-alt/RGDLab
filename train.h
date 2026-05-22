#ifndef TRAIN_H
#define TRAIN_H

#include "entity.h"
#include "direction.h"
#include "passenger.h"
#include <vector>

/**
 * @brief Статус поезда
 */
enum class TrainStatus {
    WAITING,      ///< Ожидает отправления
    ON_ROUTE_AB,  ///< Движется от A к B
    ON_ROUTE_BA   ///< Движется от B к A
};

/**
 * @brief Класс поезда
 */
class Train : public Entity {
private:
    int id;                      ///< ID поезда
    Direction* direction;        ///< Направление движения
    int capacity;                ///< Вместимость
    double speed;                ///< Скорость (км/ч)
    double departureTime;        ///< Время отправления
    double currentPosition;      ///< Текущая позиция (км)
    TrainStatus status;          ///< Статус поезда

    std::vector<Passenger> passengers; ///< Список пассажиров

public:

    Train();
    Train(int id,
          Direction* dir,
          int cap,
          double spd,
          double dep);

    int getId() const;
    bool hasFreeSeats() const;

    void addPassenger(const std::string& name);
    void removePassenger(const std::string& name);

    /**
     * @brief Обновление состояния поезда
     * @param currentTime текущее системное время
     * @param deltaTime сколько времени прошло
     */
    void update(double currentTime, double deltaTime);

    void print() const override;
    void save(std::ofstream& out) const override;

    void load(std::ifstream& in,
              std::vector<Direction>& directions);
};

#endif