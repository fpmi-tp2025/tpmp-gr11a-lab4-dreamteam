#include "car.h"
#include "database.h"
#include <sqlite3.h>
#include <iostream>

void Car::showAllCars() {
    sqlite3* db = Database::getDB();
    const char* sql = "SELECT CarID, LicensePlate, Make, Model, Year, CurrentMileage, LoadCapacity, ImagePath FROM CARS";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "\nСписок автомобилей:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int carId = sqlite3_column_int(stmt, 0);
        const unsigned char* license = sqlite3_column_text(stmt, 1);
        const unsigned char* make = sqlite3_column_text(stmt, 2);
        const unsigned char* model = sqlite3_column_text(stmt, 3);
        int year = sqlite3_column_int(stmt, 4);
        int mileage = sqlite3_column_int(stmt, 5);
        double capacity = sqlite3_column_double(stmt, 6);
        const unsigned char* image = sqlite3_column_text(stmt, 7);

        std::cout << "ID: " << carId << ", Номер: " << license
                  << ", Марка: " << make << ", Модель: " << model
                  << ", Год: " << year << ", Пробег: " << mileage
                  << ", Грузоподъемность: " << capacity << " кг"
                  << ", Изображение: " << (image ? reinterpret_cast<const char*>(image) : "-")
                  << std::endl;
    }
    sqlite3_finalize(stmt);
}

void Car::addCar(const std::string& licensePlate, const std::string& make,
                 const std::string& model, int year, int initialMileage,
                 double loadCapacity, const std::string& fuelType,
                 const std::string& imagePath) {
    sqlite3* db = Database::getDB();
    const char* sql = R"(
        INSERT INTO CARS(LicensePlate, Make, Model, Year, InitialMileage, CurrentMileage, LoadCapacity, FuelType, ImagePath)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)
    )";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare insert statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, licensePlate.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, make.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, model.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, year);
    sqlite3_bind_int(stmt, 5, initialMileage);
    sqlite3_bind_int(stmt, 6, initialMileage); // CurrentMileage = Initial
    sqlite3_bind_double(stmt, 7, loadCapacity);
    sqlite3_bind_text(stmt, 8, fuelType.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 9, imagePath.c_str(), -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Автомобиль добавлен.\n";
    }
    sqlite3_finalize(stmt);
}
