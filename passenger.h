#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

/**
 * @brief Класс пассажира
 */
class Passenger {
private:
    std::string fullName; ///< ФИО пассажира

public:

    /**
     * @brief Конструктор пассажира
     * @param name ФИО пассажира
     */
    Passenger(const std::string& name = "");

    /**
     * @brief Получить ФИО пассажира
     */
    std::string getName() const;
};

#endif