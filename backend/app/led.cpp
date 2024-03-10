// #include <wiringPi.h>
// #define Pin 7
// int main()
// {
// 	if(wiringPiSetup() <0)
// 	return 1;
// 	pinMode(Pin,OUTPUT);
// 	for(int i=0;i<10;i++)
// 	{
// 		digitalWrite(Pin,1);
// 		delay (200);
// 		digitalWrite(Pin,0);
// 		delay (200);
// 	}
// return 0;
// }

// #include<iostream>
// #include <wiringPi.h>
// #include<thread> 
// #define led 7     //GPIO 0 to be the output LED 
// #define button 0  // GPIO7 to be the input botton
// int main (void) { 
// 	wiringPiSetup () ; 
// 	pinMode (led, OUTPUT); //Set led mode to be output
// 	digitalWrite (led, HIGH); //Set led initial state is power off(HIGH-HIGH)
// 	pinMode (button, INPUT); // Set button mode to be input
// 	pullUpDnControl (button, PUD_UP); // Set button have pull-up resistance,that insure the waiting state is HIGH,when push button will get a LOW signal
// 	while(1){ 

// 		if(digitalRead(button) == 0){ // if Pi check button from HIGH to LOW 
// 				delay(20); // Eliminate button mechanical jitter interference
// 				if(digitalRead(button) == 0){ // check if button change LOW
// 					std::cout <<"an1"<<std::endl;
// 					digitalWrite (led, HIGH); // Light the LED
// 				} 
// 		}
// 		else{ 
// 			    std::cout <<"an2"<<std::endl;
// 				digitalWrite (led, LOW); // if not just keep it to HIGH
// 			} 
// 		//std::this_thread::sleep_for(std::chrono::seconds(1));
// 	} 

// 	return 0; 
// }

#include <iostream>
#include <pigpio.h>
#include <thread>
#include <chrono>

#define led 7     // 使用BCM编号，比如GPIO 4作为输出LED
#define button 23  // 使用BCM编号，比如GPIO 7作为输入按钮

int main() {
    if (gpioInitialise() < 0) {
        throw std::runtime_error("pigpio initialization failed");
    }

    gpioSetMode(led, PI_OUTPUT); // 设置LED引脚为输出
    gpioWrite(led, 1); // 设置LED初始状态为关闭（逻辑高电平）
    gpioSetMode(button, PI_INPUT); // 设置按钮引脚为输入
    gpioSetPullUpDown(button, PI_PUD_DOWN); // 为按钮设置上拉电阻

    while (true) {
        if (gpioRead(button) == PI_HIGH) { // 如果检测到按钮被按下（逻辑低电平）
            // std::this_thread::sleep_for(std::chrono::milliseconds(20)); // 消除按钮的机械抖动干扰
            // if (gpioRead(button) == 0) { // 再次检测确认按钮确实被按下
            //     std::cout << "Button Pressed" << std::endl;
            //     gpioWrite(led, 1); // 点亮LED（逻辑高电平）
            // }
			std::cout << "Button Pressed" << std::endl;
        } else {
            // gpioWrite(led, 0); // 没有检测到按钮按下，关闭LED（逻辑低电平）
			// std::cout << "Button no Pressed" << std::endl;
        }
        // 可以根据需要添加延时，但因为已经使用了消抖逻辑，这里可能不需要
    }

    // gpioTerminate(); // 清理并终止pigpio库的使用
    return 0;
}
