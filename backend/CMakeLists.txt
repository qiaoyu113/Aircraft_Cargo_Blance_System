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

# 查找关联包
find_package(Boost REQUIRED COMPONENTS system)

link_directories(/usr/lib)

# 添加可执行文件
# add_executable(run 
#     socket/main.cpp 
#     socket/websocket_session.cpp ## 模拟电灯
#     # socket/websocket_session_button.cpp ## 真实按钮电灯
#     app/conveyor_status/conveyor_status.cpp # 添加 conveyor_status 的源文件
#     # app/led_control/led.cpp  # 添加 led_control 的源文件
#     # app/led_control/button.cpp  # 添加 led_control 的源文件
# )

# # 添加可执行文件
# add_executable(run 
#     socket/main.cpp 
#     socket/websocket_session_button.cpp ## 真实按钮电灯
#     app/led_control/led.cpp  # 添加 led_control 的源文件
#     app/led_control/button.cpp  # 添加 led_control 的源文件
# )

# 启用测试
enable_testing()

# 查找Boost，确保包括unit_test_framework
find_package(Boost REQUIRED COMPONENTS system unit_test_framework)

# 添加应用程序run的可执行文件
add_executable(run 
    socket/main.cpp 
    socket/websocket_session_main.cpp ## 通信层
    app/controller/controller.cpp  # 控制层文件
    app/conveyor_status/conveyor_status.cpp  # 步进电机状态
    socket/send_message.cpp  # 消息队列
    # app/stepping_motor/left/left.cpp  # 步进电机左移动
    # app/stepping_motor/pause/pause.cpp  # 步进电机停止移动
    # app/stepping_motor/right/right.cpp  # 步进电机右移动
    # app/weight_sensor/w1/w1.cpp  # 1号测重传感器
    # app/weight_sensor/w2/w2.cpp  # 2号测重传感器
    # app/weight_sensor/w3/w3.cpp  # 3号测重传感器
    # app/weight_sensor/w4/w4.cpp  # 4号测重传感器
    # app/weight_sensor/w5/w5.cpp  # 5号测重传感器
    # app/weight_sensor/w5/w5.cpp  # 5号测重传感器
    app/weight_sensor/WeightSensor/WeightSensor.cpp  # 测重传感器
    app/motor_driver/motor_driver.cpp  # 步进电机
)    

# 添加测试可执行文件
add_executable(all_tests 
    tests/weight_sensor_test.cpp ## 测重传感器测试文件
    app/weight_sensor/WeightSensor/WeightSensor.cpp  # 测重传感器
    tests/motor_driver_test.cpp ## 步进电机测试文件
    app/motor_driver/motor_driver.cpp  # 步进电机
)

# 应用程序run的包含目录
target_include_directories(run PRIVATE 
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # 包含项目根目录
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/json-develop  # 包含 nlohmann_json 头文件目录
    ${CMAKE_CURRENT_SOURCE_DIR}/led_control  # 包含 led_control 头文件目录
)

# 应用程序run的链接库
target_link_libraries(run PRIVATE 
    ${Boost_LIBRARIES}
    pthread
    pigpio
)

# 测试的包含目录
target_include_directories(all_tests PRIVATE 
    ${Boost_INCLUDE_DIRS}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    ${CMAKE_CURRENT_SOURCE_DIR}  # 包含项目根目录
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/json-develop  # 包含 nlohmann_json 头文件目录
    ${CMAKE_CURRENT_SOURCE_DIR}/led_control  # 包含 led_control 头文件目录
)

# 测试的包含目录
target_link_libraries(all_tests PRIVATE 
    ${Boost_LIBRARIES}
    pthread
    pigpio
)

# 添加测试到CTest
add_test(NAME AllTests COMMAND all_tests)


# target_link_libraries(run PRIVATE 
#     ${Boost_LIBRARIES}
#     pthread
#     wiringPi
#     -lwiringPi
# )

# target_link_libraries(button 
#     ${Boost_LIBRARIES}
#     pthread
#     wiringPi
# )

