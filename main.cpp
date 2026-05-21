#include <iostream>
#include "railWay.h"

/**
 * @brief Точка входа в программу
 *
 * Реализует консольное меню для управления системой РЖД.
 */
int main() {

    RailwaySystem system;

    
    system.loadFromFile();

    int choice;

    while (true) {

        std::cout << "1. Add direction\n";
        std::cout << "2. Add train\n";
        std::cout << "3. Buy ticket\n";
        std::cout << "4. Return ticket\n";
        std::cout << "5. Show directions\n";
        std::cout << "6. Show trains\n";
        std::cout << "7. Advance time\n";
        std::cout << "8. Save data\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";

        std::cin >> choice;

        if (choice == 0) {
            system.saveToFile();
            std::cout << "Exiting program...\n";
            break;
        }

        switch (choice) {

        case 1: {
            std::string a, b;
            double dist;

            std::cout << "Station A: ";
            std::cin >> a;

            std::cout << "Station B: ";
            std::cin >> b;

            std::cout << "Distance (km): ";
            std::cin >> dist;

            system.addDirection(a, b, dist);
            break;
        }

        case 2: {
            int id, cap;
            double speed, dep;

            std::cout << "Direction ID: ";
            std::cin >> id;

            std::cout << "Capacity: ";
            std::cin >> cap;

            std::cout << "Speed (km/h): ";
            std::cin >> speed;

            std::cout << "Departure time (hours): ";
            std::cin >> dep;

            system.addTrain(id, cap, speed, dep);
            break;
        }

        case 3: {
            int id;
            std::string name;

            std::cout << "Train ID: ";
            std::cin >> id;

            std::cin.ignore();
            std::cout << "Full name: ";
            std::getline(std::cin, name);

            system.buyTicket(id, name);
            break;
        }

        case 4: {
            int id;
            std::string name;

            std::cout << "Train ID: ";
            std::cin >> id;

            std::cin.ignore();
            std::cout << "Full name: ";
            std::getline(std::cin, name);

            system.returnTicket(id, name);
            break;
        }

        case 5:
            system.showDirections();
            break;

        case 6:
            system.showTrains();
            break;

        case 7: {
            double hours;
            std::cout << "Enter number of hours to advance: ";
            std::cin >> hours;

            system.advanceTime(hours);
            break;
        }

        case 8:
            system.saveToFile();
            break;

        default:
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}