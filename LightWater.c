#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ledCounts 10
int pins[ledCounts] = {0,1,2,3,4,5,6,8,9,10}; //no 7 because those are wiringPi pin number and pin 7 "GPIO.7" isn't used


void left_to_right(int leds, int *pins);
void right_to_left(int leds, int *pins);
void turn_on_even_prog(int leds, int *pins);
void turn_on_odd_regress(int leds, int *pins);
void mid_to_edge_and_back(int leds, int *pins);
void random_leds(int leds, int *pins);


void main (void) {

  int i;
  printf("Program is starting...");

  wiringPiSetup(); //Initialize wiringPi

  for(i=0; i <ledCounts; i++) { //set pinMode for all led pins output
      pinMode(pins[i], OUTPUT);
  }

  void (*func_list[6])(int, int);
  func_list[0] = left_to_right;
  func_list[1] = right_to_left;
  func_list[2] = turn_on_even_prog;
  func_list[3] = turn_on_odd_regress;
  func_list[4] = mid_to_edge_and_back;
  func_list[5] = random_leds;

  while(1){

    // add random selection of function

    for(int x = 0; x < 6; x++){
      func_list[x](ledCounts, *pins);
    }


/*
    left_to_right(ledCounts, pins);
    right_to_left(ledCounts, pins);
    turn_on_even_prog(ledCounts, pins);
    turn_on_odd_regress(ledCounts, pins);
    mid_to_edge_and_back(ledCounts, pins);
    random_leds(ledCounts, pins);
*/


}

void left_to_right(int leds, int *pins){
  for(i=0;i<leds;i++){       //move LED on from left to right
    digitalWrite(pins[i], LOW);
    delay(100);
    digitalWrite(pins[i], HIGH);
    printf("Left to right");
  }
}

void right_to_left(int leds, int *pins){
  for(i=leds-1;i >-1;i--){  //move LED on from right to left
    digitalWrite(pins[i], LOW);
    delay(100);
    digitalWrite(pins[i], HIGH);
    printf("Right to left");
  }
}

void turn_on_even_prog(int leds, int *pins){
  for(i=0;i<leds;i++){ //turn on even number pin indexes
    if(pins[i] % 2 == 0) {
      digitalWrite(pins[i], LOW);
      delay(300);
      digitalWrite(pins[i], HIGH);
      printf("Evens");
    }
}
}
void turn_on_odd_regress(int leds, int *pins){
  for(i=ledCounts-1;i >-1;i--){ //turn on odd number pin indexes
    if(pins[i] % 2 != 0) {
      digitalWrite(pins[i], LOW);
      delay(300);
      digitalWrite(pins[i], HIGH);
      printf("Odds");
    }
  }
}

void mid_to_edge_and_back(int leds, int *pins){

  int bob_left = (leds/2)-1; //left half
  int bob_right = leds/2; //right half

  for(i=0;i<bob_right;i++){ // turns on led from middle to edges
    digitalWrite(pins[bob_left], LOW);
    digitalWrite(pins[bob_right], LOW);
    delay(150);
    digitalWrite(pins[bob_left], HIGH);
    digitalWrite(pins[bob_right], HIGH);
    bob_left -= 1;
    bob_right += 1;
    printf("mid to edge");

    if(bob_left == (leds - leds) && bob_right == (leds -1)){ // turns on led from edges to middle
      while(bob_left != (leds/2) && bob_right != ((leds/2)-1)){
        bob_left += 1;
        bob_right -= 1;
        digitalWrite(pins[bob_left], LOW);
        digitalWrite(pins[bob_right], LOW);
        delay(150);
        digitalWrite(pins[bob_left], HIGH);
        digitalWrite(pins[bob_right], HIGH);
        printf("edge to mid");
        }
      }
    }

  bob_left = 0; //resets the bobs for the next loop
  bob_right = 0;

}

void random_leds(int leds, int *pins){
  srand(time(NULL));
  int jeb = 0;
  while(jeb < leds) {
    int r = rand() % 10;
    digitalWrite(pins[r], LOW);
    delay(100);
    digitalWrite(pins[r], HIGH);
    jeb++;
    printf("Random");
  }



}
