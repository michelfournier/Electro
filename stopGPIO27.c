
//pin stay often on after execution of ultrasonicWithLEDalert Program, so this will turn off
#include <stdio.h>
#include <wiringPi.h>

#define ledPin 2

int main() {


  wiringPiSetup();

  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  return 0;
}
