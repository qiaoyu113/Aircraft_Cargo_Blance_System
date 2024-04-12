# Hardware Part Of Aircraft Cargo auto Blance System

### Author：Yu Qiao & Yuhan Liu

### Developer 👨‍💻
| Author | E-mail |
| ------ | ----- |
| [🤔️ Yu Qiao(Joey)](http://github.com/qiaoyu113) | 527324363@qq.com |
| [Yuhan Liu](yuhanliu123@outlook.com) | yuhanliu123@outlook.com |
# 

### Project architecture version
| boost | nlohmann |
| ------ | ------ |
| v1.82.0 | v3.10.2 |

### boost download link: 
https://www.boost.org/doc/libs/1_84_0/more/getting_started/unix-variants.html
### nlohmann download link: 
https://github.com/nlohmann/json.git
### install wiringpi
```
sudo apt-get update
sudo apt-get install wiringpi
```

### install boost
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

### install nlohmann
```
cd json-develop
mkdir build
cd build/
cmake ..
make
make install
```
### nlohmann下载并编译后要将json-develop中include内的nlohmann移动到/json-develop/nlohmann ！！！！
### After nlohmann is downloaded and compiled, move the nlohmann included in json-develop to /json-develop/nlohmann ！！！！

### Compile Project （CMAKE）
#### Navigate to the project root directory
```
cd backend
```
#### Create a build directory
```
mkdir build
cd build
```
#### Run CMake to generate the build system
```
cmake ..
```
#### Build the project
```
cmake --build .
```
Or
```
make
```
#### Run the executable
```
./run
```

#### Close the tcp
```
sudo lsof -i :22
sudo kill -9 ID
```

##### (The packaged build file has been quarantined and will not be uploaded to github ！)
##### (The packaged Packages include boost and nlohmann file has been quarantined and will not be uploaded to github ！)

### if running code in terminal for single file: 
```
1. g++ -std=c++11 server.cpp -o server
g++ -std=c++11 -I../packages/json-develop -o server server.cpp
2. ./server
```
or
```
g++ led.cpp -o led -lpigpio -lrt -lpthread
sudo ./led
```

## Project Framework and Structure
```
Backend/                  
|-- app/     
|   |-- controller/      
|   |   |-- controller.cpp          # The implementation of the primary controller logic.
|   |   |-- controller.hpp          # The header file defining the controller interface.
|   |-- conveyor_status/
|   |   |-- conveyor_status.cpp     # Implementation of conveyor status checks.
|   |   |-- conveyor_status.hpp     # Header file for conveyor status declarations.
|   |-- led_control/
|   |   |-- button.cpp              # Manages button interactions for LEDs.
|   |   |-- button.hpp              # Header file for button control definitions.
|   |   |-- led.cpp                 # Contains the logic for LED behavior.
|   |   |-- led.hpp                 # Header file for LED operations.
|   |   |-- main.cpp                # The main entry point for the LED control module.
|   |-- stepping_motor/
|       |-- left/
|       |   |-- left.cpp            # Controls the left movement of the stepper motor.
|       |   |-- left.hpp            # Header file for left movement definitions.
|       |-- pause/
|       |   |-- pause.cpp           # Manages the pause functionality of the stepper motor.
|       |   |-- pause.hpp           # Header file for pause control definitions.
|       |-- right/
|           |-- right.cpp           # Manages the right movement of the stepper motor.
|           |-- right.hpp           # Header file for right movement definitions.
|   |-- weight_sensor/
|       |-- w1.cpp                  # Manages weight sensor w1's data processing.
|       |-- w1.hpp                  # Header for weight sensor w1's interface.
|       |-- w2.cpp                  # Implementation for weight sensor w2.
|       |-- w2.hpp                  # Header file for weight sensor w2.
|       |-- w3.cpp                  # Code for weight sensor w3's operations.
|       |-- w3.hpp                  # Header file for weight sensor w3.
|       |-- w4.cpp                  # Handles the logic for weight sensor w4.
|       |-- w4.hpp                  # Header file for weight sensor w4.
|       |-- w5.cpp                  # Manages operations for weight sensor w5.
|       |-- w5.hpp                  # Header file for weight sensor w5's definitions.
|-- LED/
|   |-- led.cpp                     # Standalone LED control logic.
|-- Build/                          # Contains build-related files.
|-- Config/
|   |-- config.cpp                  # Contains configuration settings for the application.
|-- Models/
|   |-- __init__.cpp                # Initialization for model modules.
|-- Packages/                       # Third-party libraries and dependencies.
|-- Socket/
|   |-- main.cpp                    # Main implementation for socket communication.
|   |-- server/
|   |   |-- server.cpp              # Server-side socket communication handling.
|   |-- websocket_session/
|       |-- websocket_session_button.cpp  # Manages button-related websocket sessions.
|       |-- websocket_session_button.hpp  # Header file for button websocket sessions.
|       |-- websocket_session_main.cpp   # Main logic for websocket sessions.
|       |-- websocket_session_main.hpp   # Header file for main websocket session logic.
|       |-- websocket_session.cpp        # Generic websocket session management.
|       |-- websocket_session.hpp        # Header file for websocket session definitions.
|-- Utils/
|   |-- __init__.cpp                # Initializes the utility module.
|   |-- calculations.cpp            # Includes various calculation functions.
|-- CMakeLists.txt                  # CMake configuration file for build settings.
|-- readme.md                       # The README file for the project with documentation.

```