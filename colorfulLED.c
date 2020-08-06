#include <stdio.h>
#include <softPwm.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <time.h>

#define ledPinRed 0
#define ledPinGreen 1
#define ledPinBlue 2

void setupLedPin(void); // func to create PWM pins
void setLedColor(int r, int g, int b); // func to assign intensity to each pins

int main(void) {
  int r,g,b;

  printf("Program is starting...\n");

  wiringPiSetup();

  setupLedPin();

  srand(time(NULL));

  while(1){


    r = rand() % 100;
    g = rand() % 100;
    b = rand() % 100;
    setLedColor(r,g,b);
    printf("r = %d, g = %d, b = %d\n", r,g,b);
    delay(300);
  }

return 0;

}

// func defenition

void setupLedPin(void) {
  softPwmCreate(ledPinRed, 0, 100);
  softPwmCreate(ledPinGreen, 0, 100);
  softPwmCreate(ledPinBlue, 0, 100);
}

void setLedColor(int r, int g, int b) {
  softPwmWrite(ledPinRed, r);
  softPwmWrite(ledPinGreen, g);
  softPwmWrite(ledPinBlue, b);
}
