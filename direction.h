#ifndef DIRECTION_H
#define DIRECTION_H

#include "entity.h"
#include <string>

/**
 * @brief Класс направления движения поезда
 */
class Direction : public Entity {
private:
    int id;                 ///< Идентификатор направления
    std::string stationA;   ///< Начальная станция
    std::string stationB;   ///< Конечная станция
    double distance;        ///< Расстояние между станциями (км)

public:

    Direction();
    Direction(int id,
              const std::string& a,
              const std::string& b,
              double dist);

    int getId() const;
    std::string getStationA() const;
    std::string getStationB() const;
    double getDistance() const;

    void print() const override;
    void save(std::ofstream& out) const override;

    /**
     * @brief Загрузка направления из файла
     */
    void load(std::ifstream& in);
};

#endif
