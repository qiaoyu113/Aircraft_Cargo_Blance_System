cmake_minimum_required(VERSION 3.12)
project(Backend)

set(CMAKE_CXX_STANDARD 14)

# 查找关联包
find_package(Boost REQUIRED COMPONENTS system)

# 添加可执行文件
add_executable(run 
    socket/main.cpp 
    # socket/websocket_session.cpp ## 模拟电灯
    socket/websocket_session_button.cpp ## 真实按钮电灯
    # app/conveyor_status/conveyor_status.cpp # 添加 conveyor_status 的源文件
    app/led_control/led.cpp  # 添加 led_control 的源文件
    app/led_control/button.cpp  # 添加 led_control 的源文件
)
# 包含目录
target_include_directories(run PRIVATE 
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # 包含项目根目录
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/json-develop  # 包含 nlohmann_json 头文件目录
    ${CMAKE_CURRENT_SOURCE_DIR}/led_control  # 包含 led_control 头文件目录
)

# 链接库
target_link_libraries(run PRIVATE 
    ${Boost_LIBRARIES}
)
