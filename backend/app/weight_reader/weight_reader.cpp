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

/*-----------------constructure-----------------*/
#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <iostream>

struct hx711_pin {
    int SCK;
    int SDA;
    int EN;
    int calibration;
    int coefficient;
    int weight;
    unsigned long value;
};

void set_pin(struct hx711_pin *value) {
    value->SCK = 16;
    value->SDA = 12;
    value->EN = 1;
    value->coefficient = 415;
}

void init_pin(struct hx711_pin *value) {
    gpioSetMode(value->SCK, PI_OUTPUT);
    gpioSetMode(value->SDA, PI_INPUT);
    gpioSetPullUpDown(value->SDA, PI_PUD_UP);
}

void start(struct hx711_pin *value) {
    int i;
    gpioWrite(value->SCK, PI_LOW);
    while(gpioRead(value->SCK));
    value->value = 0;
    while(gpioRead(value->SDA));
    time_sleep(0.1);
    for(i=0; i<24; i++) {
        gpioWrite(value->SCK, PI_HIGH);
        while(gpioRead(value->SCK) == 0) gpioDelay(1000);
        value->value = value->value << 1;
        gpioWrite(value->SCK, PI_LOW);
        while(gpioRead(value->SCK));
        if(gpioRead(value->SDA)) {
            value->value++;
        }
        gpioWrite(value->SCK, PI_LOW);
    }
    gpioWrite(value->SCK, PI_HIGH);
    
    std::cerr << "value->EN:" << value->EN << std::endl;
    std::cerr << "value->value:" << value->value << std::endl;

    if((value->EN == 1) && (value->value > 2500)) {
        printf("EN == 1");
        value->EN = 0;
        value->calibration = value->value;
    } else {
        // printf("value:", value->value);
        // printf("calibration:", value->calibration);
        // printf("coefficient:", value->coefficient);
        i = (value->value - value->calibration + 50) / value->coefficient;
    }
    if(i < 5000) value->weight = i;
    // value->weight = i;
    printf("重量为：%d g\n", value->weight);
}

int setup(struct hx711_pin *value) {
    if(gpioInitialise() < 0) return 1;
    set_pin(value);
    init_pin(value);
    return 0;
}

void loop(struct hx711_pin *value) {
    while(1) {
        start(value);
        time_sleep(0.2);
    }
}

int main(void) {
    struct hx711_pin value;
    if(0 == setup(&value)) {
        loop(&value);
    }
    gpioTerminate();
    return 0;
}