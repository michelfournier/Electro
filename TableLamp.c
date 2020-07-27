#include <wiringPi.h>
#include <stdio.h>

#define ledPin 0 //define LED pin number
#define buttonPin 1 //define button pin

int ledState = LOW;  // store the state of the LED
int buttonState = HIGH;  // store the state of the button position
int lastButtonState = HIGH;  // store the last position of the button
long lastChangeTime;  // store the change time of button state
long captureTime = 50; // set the stable time for button state
int reading;

int main(void) {

  printf("Program is starting... \n");

  wiringPiSetup(); // Initialize wiringPi

  pinMode(ledPin, OUTPUT);  //set led pin to OUTPUT
  pinMode(buttonPin, INPUT); // set button to INPUT

  pullUpDnControl(buttonPin, PUD_UP);  // pull up to high level

  while(1) {

    reading = digitalRead(buttonPin); // read the current state of button
    if(reading != lastButtonState) { //if button state has changed, record time point
      lastChangeTime = millis();
    }
    //if changing-state of the button last beyond the time we set, we consider that
    //the current button state is an effective change rather than a buffeting
    if(millis() - lastChangeTime > captureTime) { //if button state is changed, update data
      if(reading != buttonState) {
        buttonState = reading;
        //if the state is low, it means the action is pressing
        if(buttonState == LOW){
          printf("Button is pressed!\n");
          ledState = !ledState; //reverse the led state
          if(ledState){
            printf("turn on LED...\n");
          }
          else {
            printf("turn off LED... \n");
          }
        }
        //if the state is high, it means the action is releasing
        else {
          printf("Button is released!\n");
        }
      }
    }

    digitalWrite(ledPin, ledState);
    lastButtonState = reading;


  }

return 0;




}
