#include "WeightSensor/WeightSensor.hpp"

int main() {
    try {
        WeightSensor sensor1(10);
        WeightSensor sensor2(11);
        WeightSensor sensor3(12);
        // Set a callback function for each sensor
        sensor1.setCallback([](bool weightDetected) {
            std::cout << "Sensor 1 detected weight: " << weightDetected << std::endl;
        });
        sensor2.setCallback([](bool weightDetected) {
            std::cout << "Sensor 2 detected weight: " << weightDetected << std::endl;
        });
        sensor3.setCallback([](bool weightDetected) {
            std::cout << "Sensor 3 detected weight: " << weightDetected << std::endl;
        });

        // The main loop of your program, here are just examples
        while (true) {
            sensor1.weightReading();
            sensor2.weightReading();
            sensor3.weightReading();
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}