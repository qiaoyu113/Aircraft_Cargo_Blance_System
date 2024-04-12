/**
 * @file   weight_sensor_test.cpp
 * @brief  Unit test of gravity sensor
 *
 * @author Yu Qiao
 * @date   2024-03-15
 *
 * Additional notes:
 * - ...
 */

#define BOOST_TEST_MODULE WeightSensorTest
#include <boost/test/included/unit_test.hpp>
#include "../app/weight_sensor/WeightSensor/WeightSensor.hpp"
// #include "../app/weight_sensor/hx711_sensor/hx711_sensor.cpp"

// Mock the pigpio functions if needed
// ...

BOOST_AUTO_TEST_CASE(test_weight_sensor_initialization)
{
    // Initialize the WeightSensor object with a mock or real GPIO pin number
    WeightSensor ws(17, 18); // Assume that 17 and 18 are the SCK and SDA pins used for testing

    // Test whether the initialization was successful, such as whether an exception was thrown
    BOOST_CHECK_NO_THROW(ws);
}

BOOST_AUTO_TEST_CASE(test_weight_sensor_reading)
{
    WeightSensor ws(17, 18);

    // Here you can simulate the result read by GPIO and then call the readSensor method
    int weight = ws.read_sensor_test();
    
    // Assuming you have an expected weight value, you can check it with BOOST_CHECK_EQUAL
    BOOST_CHECK_GE(weight, 0); // The expected weight here should be positive
}

