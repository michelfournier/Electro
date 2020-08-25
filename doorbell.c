#include <wiringPi.h>
#include <stdio.h>

#define buzzerPin 0
#define buttonPin 1

void main(void) {

  printf("Program is starting....");

  wiringPiSetup();

  pinMode(buzzerPin, OUTPUT); // set to output so it receives a signal and acts on it
  pinMode(buttonPin, INPUT); // if it does something, it provides input for program to do something

  pullUpDnControl(buttonPin, PUD_UP); // set to up position, so 'not pressed'

  int status_showed = 0; // exit mechanics so the message doesn't show repeatedly

  while(1){

    if(digitalRead(buttonPin) == LOW) {  // if button pressed
      digitalWrite(buzzerPin, HIGH); // sends juice to buzzer to make it buzz
      status_showed = 0;
      printf("buzzin..");

    }
    else {
      digitalWrite(buzzerPin, LOW);
      if(status_showed == 0) {
        status_showed = 1;
        printf("not buzzin...");
      }
    }

  }

}
