/**
 * @file   WeightSensor.cpp
 * @brief  Gravity sensor code file
 *
 * @author Yuhan Liu
 * @date   2024-02-21
 *
 * Additional notes:
 * - ...
 */

#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <iostream>

/*-----------------结构体-----------------*/
struct hx711_pin{
    int SCK;
    int SDA;
    int EN;                      // 校准使能
    int calibration;             // 校准
    int coefficient;             // 比例系数
    int weight;                  // 重量
    unsigned long value;         // 记录数值
};

void set_pin(struct hx711_pin *value){
    value->SCK = 27;             // 根据实际连接修改
    value->SDA = 22;             // 根据实际连接修改
    value->EN = 1;
    value->coefficient = 415;
}

void init_pin(struct hx711_pin *value){
    gpioSetMode(value->SCK, PI_OUTPUT);
    gpioSetMode(value->SDA, PI_INPUT);
    gpioSetPullUpDown(value->SDA, PI_PUD_UP);
}

void start(struct hx711_pin *value){
    int i;
    gpioWrite(value->SCK, PI_LOW);
    while(gpioRead(value->SCK));
    value->value = 0;
    while(gpioRead(value->SDA));
    time_sleep(0.1);           // 延时100ms
    for(i=0; i<24; i++){
        gpioWrite(value->SCK, PI_HIGH);
        while(gpioRead(value->SCK) == 0) gpioDelay(1000);
        value->value = value->value << 1;
        gpioWrite(value->SCK, PI_LOW);
        while(gpioRead(value->SCK));
        if(gpioRead(value->SDA)){
            value->value++;
        }
        gpioWrite(value->SCK, PI_LOW);
    }
    gpioWrite(value->SCK, PI_HIGH);
    // value->value = value->value ^ 0x800000;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           gpioWrite(value->SCK, PI_LOW);
    std::cerr << "value->EN:" << value->EN << std::endl;
    std::cerr << "value->value:" << value->value << std::endl;

    // if((value->EN == 1) && (value->value < 25000)){
    if((value->EN == 1) && (value->value > 2500)){
        value->EN = 0;
        value->calibration = value->value;
    } else {
        i = (value->value - value->calibration + 50) / value->coefficient;
    }
    if(i < 5000) value->weight = i;
    printf("重量为：%d g\n", value->weight);
}

int setup(struct hx711_pin *value){
    if(gpioInitialise() < 0) return 1;
    set_pin(value);
    init_pin(value);
    return 0;
}

void loop(struct hx711_pin *value){
    while(1){
        start(value);
        time_sleep(0.2); // 延时1秒
    }
}

int main(void){
    struct hx711_pin value;
    if(0 == setup(&value)){
        loop(&value);
    }
    gpioTerminate();
    return 0;
}





// #include <iostream>
// #include <pigpio.h>
// #include <unistd.h>

// // 定义HX711连接的GPIO引脚
// #define DATA_PIN 22  // 替换为你的数据引脚号
// #define CLOCK_PIN 27 // 替换为你的时钟引脚号

// // 初始化HX711
// void setup() {
//     gpioInitialise();
//     gpioSetMode(DATA_PIN, PI_INPUT);
//     gpioSetMode(CLOCK_PIN, PI_OUTPUT);
// }

// // 读取HX711的值
// long readHX711() {
//     long count = 0;
//     while (gpioRead(DATA_PIN)) {
//         // 等待数据准备就绪
//     }

//     for (int i = 0; i < 24; i++) {
//         gpioWrite(CLOCK_PIN, 1);
//         count = count << 1;
//         usleep(1);
//         gpioWrite(CLOCK_PIN, 0);
//         if (gpioRead(DATA_PIN)) {
//             count++;
//         }
//     }

//     gpioWrite(CLOCK_PIN, 1);
//     count = count ^ 0x800000;
//     usleep(1);
//     gpioWrite(CLOCK_PIN, 0);

//     return count;
// }

// int main() {
//     setup();
//     while (true) {
//         long weight = readHX711();
//         std::cout << "Weight: " << weight << std::endl;
//         usleep(1000000); // 等待1秒
//     }
//     gpioTerminate();
//     return 0;
// }