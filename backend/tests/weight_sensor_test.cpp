#define BOOST_TEST_MODULE WeightSensorTest
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include "../app/weight_sensor/WeightSensor/WeightSensor.hpp"

// Mock the pigpio functions if needed
// ...

BOOST_AUTO_TEST_CASE(test_weight_sensor_initialization)
{
    // 使用一个模拟或真实的GPIO引脚号来初始化WeightSensor对象
    WeightSensor ws(17, 18); // 假设17和18是用于测试的SCK和SDA引脚

    // 测试初始化是否成功，例如是否抛出异常等
    BOOST_CHECK_NO_THROW(ws);
}

BOOST_AUTO_TEST_CASE(test_weight_sensor_reading)
{
    WeightSensor ws(17, 18);

    // 这里你可以模拟GPIO读取的结果，然后调用readSensor方法
    int weight = ws.readSensor();
    
    // 假设你有一个预期的重量值，你可以用BOOST_CHECK_EQUAL来检查
    BOOST_CHECK_GE(weight, 0); // 这里的expected_weight应该为正值
}

