#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
public:
    static void showAllCars();
    static void addCar(const std::string& licensePlate, const std::string& make,
                       const std::string& model, int year, int initialMileage,
                       double loadCapacity, const std::string& fuelType,
                       const std::string& imagePath);
};

#endif
