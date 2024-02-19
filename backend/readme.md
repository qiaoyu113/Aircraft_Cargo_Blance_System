### running code in terminal for singal: 
1. g++ -std=c++11 server.cpp -o server
g++ -std=c++11 -I../packages/json-develop -o server server.cpp
2. ./server

### 安装boost和nlohmann
```
cd json
mkdir build
cd build/
cmake ..
make
make install
```
### nlohmann下载并编译后要将json-develop中include内的nlohmann移动到/json-develop/nlohmann ！！！！

### 编译项目
#### Navigate to the project root directory
cd backend
#### Create a build directory
mkdir build
cd build
#### Run CMake to generate the build system
cmake ..
#### Build the project
cmake --build . / make
#### Run the executable
./run

