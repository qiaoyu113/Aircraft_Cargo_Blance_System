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

#include<iostream>
#include <wiringPi.h>
#include<thread> 
#define led 7     //GPIO 0 to be the output LED 
#define button 0  // GPIO7 to be the input botton
int main (void) { 
	wiringPiSetup () ; 
	pinMode (led, OUTPUT); //Set led mode to be output
	digitalWrite (led, HIGH); //Set led initial state is power off(HIGH-HIGH)
	pinMode (button, INPUT); // Set button mode to be input
	pullUpDnControl (button, PUD_UP); // Set button have pull-up resistance,that insure the waiting state is HIGH,when push button will get a LOW signal
	while(1){ 

		if(digitalRead(button) == 0){ // if Pi check button from HIGH to LOW 
				delay(20); // Eliminate button mechanical jitter interference
				if(digitalRead(button) == 0){ // check if button change LOW
					std::cout <<"an1"<<std::endl;
					digitalWrite (led, HIGH); // Light the LED
				} 
		}
		else{ 
			    std::cout <<"an2"<<std::endl;
				digitalWrite (led, LOW); // if not just keep it to HIGH
			} 
		//std::this_thread::sleep_for(std::chrono::seconds(1));
	} 

	return 0; 
}