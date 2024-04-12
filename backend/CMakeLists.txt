# @file   CMakeLists.txt
# @brief  The config file of CMake
# 
# @author Yu Qiao
# @date   2024-01-22
#
# Additional notes:
# - ...
#
 
cmake_minimum_required(VERSION 3.12)
project(Backend)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Find association pack
find_package(Boost REQUIRED COMPONENTS system)

link_directories(/usr/lib)

# start testing
enable_testing()

# find Boost，includ unit_test_framework
find_package(Boost REQUIRED COMPONENTS system unit_test_framework)

# Add an executable file for the application run
add_executable(run 
    socket/main.cpp 
    socket/websocket_session_main.cpp ## Communication Layer
    app/controller/controller.cpp  # Control layer file
    app/conveyor_status/conveyor_status.cpp  # Stepper motor status
    socket/send_message.cpp  # message queue
    # app/stepping_motor/left/left.cpp  # Stepper motor moves left (abandon)
    # app/stepping_motor/pause/pause.cpp  # Stepper motor stops moving (abandon)
    # app/stepping_motor/right/right.cpp  # Stepper motor move right (abandon)
    # app/weight_sensor/WeightSensor/WeightSensor.cpp  # Weight sensor  (abandon)
    app/weight_sensor/hx711_sensor/hx711_sensor.cpp  # Weight sensor
    app/motor_driver/motor_driver.cpp  # stepping motor
)    

# Add a test executable
add_executable(all_tests 
    tests/weight_sensor_test.cpp ## Weight sensor test file
    app/weight_sensor/WeightSensor/WeightSensor.cpp  # Weight sensor
    # app/weight_sensor/hx711_sensor/hx711_sensor.cpp  # Weight sensor
    tests/motor_driver_test.cpp ## stepping motor test file
    app/motor_driver/motor_driver.cpp  # stepping motor
)

# The contain directory of the application run
target_include_directories(run PRIVATE 
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # Contains the project root directory
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/json-develop  # Contains the nlohmann_json header file directory
    ${CMAKE_CURRENT_SOURCE_DIR}/led_control  # Contains the led_control header file directory
)

# Link library for the application run
target_link_libraries(run PRIVATE 
    ${Boost_LIBRARIES}
    pthread
    pigpio
    hx711
)

# The included directory for the test
target_include_directories(all_tests PRIVATE 
    ${Boost_INCLUDE_DIRS}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${CMAKE_CURRENT_SOURCE_DIR}  # Contains the project root directory
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/json-develop  # Contains the nlohmann_json header file directory
    ${CMAKE_CURRENT_SOURCE_DIR}/led_control  # Contains the led_control header file directory
)

# The included directory for the test
target_link_libraries(all_tests PRIVATE 
    ${Boost_LIBRARIES}
    pthread
    pigpio
)

# Add tests to CTest
add_test(NAME AllTests COMMAND all_tests)
