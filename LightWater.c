#include <wiringPi.h>
#include <stdio.h>

#define ledCounts 10
int pins[ledCounts] = {0,1,2,3,4,5,6,8,9,10}; //no 7 because those are wiringPi pin number and pin 7 "GPIO.7" isn't used

void main (void) {

  int i;
  printf("Program is starting...");

  wiringPiSetup(); //Initialize wiringPi

  for(i=0; i <ledCounts; i++) { //set pinMode for all led pins output
      pinMode(pins[i], OUTPUT);
  }

  while(1){

    for(i=0;i<ledCounts;i++){       //move LED on from left to right
      digitalWrite(pins[i], LOW);
      delay(100);
      digitalWrite(pins[i], HIGH);
    }

    for(i=ledCounts-1;i >-1;i--){  //move LED on from right to left
      digitalWrite(pins[i], LOW);
      delay(100);
      digitalWrite(pins[i], HIGH);
    }

    for(i=0;i<ledCounts;i++){ //turn on even number pin indexes
      if(pins[i] % 2 == 0) {
        digitalWrite(pins[i], LOW);
        delay(300);
        digitalWrite(pins[i], HIGH);
      }
    }
    for(i=ledCounts-1;i >-1;i--){ //turn on odd number pin indexes
      if(pins[i] % 2 != 0) {
        digitalWrite(pins[i], LOW);
        delay(300);
        digitalWrite(pins[i], HIGH);
      }
    }

    int bob_left = (ledCounts/2)-1; //left half
    int bob_right = ledCounts/2; //right half

    for(i=0;i<5;i++){ // turns on led from middle to edges
      digitalWrite(pins[bob_left], LOW);
      digitalWrite(pins[bob_right], LOW);
      delay(150);
      digitalWrite(pins[bob_left], HIGH);
      digitalWrite(pins[bob_right], HIGH);
      bob_left -= 1;
      bob_right += 1;

      if(bob_left == 0 && bob_right == 9){ // turns on led from edges to middle
        while(bob_left != 5 && bob_right != 4){
          bob_left += 1;
          bob_right -= 1;
          digitalWrite(pins[bob_left], LOW);
          digitalWrite(pins[bob_right], LOW);
          delay(150);
          digitalWrite(pins[bob_left], HIGH);
          digitalWrite(pins[bob_right], HIGH);
          }
        }
      }

    bob_left = 0; //resets the bobs for the next loop
    bob_right = 0;

  }





}
