#include <iostream>
#include "user.h"
#include "car.h"
#include "database.h"

void adminMenu() {
    while (true) {
        std::cout << "\nМеню администратора:\n";
        std::cout << "1. Показать все автомобили\n";
        std::cout << "2. Добавить автомобиль\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            Car::showAllCars();
        } else if (choice == 2) {
            std::string license, make, model, fuel, image;
            int year, initial;
            double capacity;
            std::cout << "Номер: "; std::cin >> license;
            std::cout << "Марка: "; std::cin >> make;
            std::cout << "Модель: "; std::cin >> model;
            std::cout << "Год выпуска: "; std::cin >> year;
            std::cout << "Пробег при покупке: "; std::cin >> initial;
            std::cout << "Грузоподъемность: "; std::cin >> capacity;
            std::cout << "Тип топлива: "; std::cin >> fuel;
            std::cout << "Путь к изображению: "; std::cin >> image;

            Car::addCar(license, make, model, year, initial, capacity, fuel, image);
        } else if (choice == 0) {
            break;
        }
    }
}

int main() {
    if (!Database::connect("data/autopark.db")) {
        return 1;
    }

    std::string username, password;
    User currentUser;

    std::cout << "Login: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (!Auth::login(username, password, currentUser)) {
        std::cerr << "Authentication failed!" << std::endl;
        return 1;
    }

    std::cout << "Welcome, " << currentUser.username << " (" << currentUser.role << ")" << std::endl;

    if (currentUser.role == "admin") {
        adminMenu();
    } else if (currentUser.role == "driver") {
        std::cout << "Доступ ограниченный. Только просмотр информации.\n";
        Car::showAllCars();
    }

    return 0;
}
