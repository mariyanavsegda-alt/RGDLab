#ifndef ENTITY_H
#define ENTITY_H

#include <fstream>

/**
 * @brief Абстрактный базовый класс системы
 *
 * От него наследуются основные сущности проекта.
 */
class Entity {
public:

    /**
     * @brief Вывод информации о сущности
     */
    virtual void print() const = 0;

    /**
     * @brief Сохранение сущности в файл
     * @param out поток вывода
     */
    virtual void save(std::ofstream& out) const = 0;

    virtual ~Entity() {}
};

#endif