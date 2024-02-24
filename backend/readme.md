### running code in terminal: 
1. g++ -std=c++11 server.cpp -o server
g++ -std=c++11 -I../packages/json-develop -o server server.cpp
2. ./server

### 安装boost
```
cd boost_1_82_0
./bootstrap.sh --prefix=/usr/local
./b2
sudo ./b2 install
// until up not keep going...
cat /usr/include/boost/version.hpp | grep "BOOST_LIB_VERSION"
// if find the error 
sudo apt-get install libboost-all-dev
```

### nlohmann
```
cd json-develop
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
cmake --build . or make
#### Run the executable
./run

