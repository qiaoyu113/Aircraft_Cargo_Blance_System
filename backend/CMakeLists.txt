cmake_minimum_required(VERSION 3.12)
project(Backend)

set(CMAKE_CXX_STANDARD 14)

# 查找关联包
find_package(Boost REQUIRED COMPONENTS system)

# 添加可执行文件
add_executable(run socket/main.cpp socket/websocket_session.cpp app/conveyor_status.cpp)

# 包含目录
target_include_directories(run PRIVATE 
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # 包含项目根目录
    ${CMAKE_CURRENT_SOURCE_DIR}/packages/json-develop  # 包含 nlohmann_json 头文件目录
)

# 链接库
target_link_libraries(run PRIVATE 
    ${Boost_LIBRARIES}
)
