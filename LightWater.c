#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ledCounts 10
int pins[ledCounts] = {0,1,2,3,4,5,6,8,9,10}; //no 7 because those are wiringPi pin number and pin 7 "GPIO.7" isn't used

// declaration of functions
void left_to_right(int leds, int *pins);
void right_to_left(int leds, int *pins);
void turn_on_even_prog(int leds, int *pins);
void turn_on_odd_regress(int leds, int *pins);
void mid_to_edge_and_back(int leds, int *pins);
void random_leds(int leds, int *pins);

void master_selector(int leds, int *pins, *func f1, *func f2, *func f3, *func f4, *func f5, *func f6);


void main (void) {

  int i;
  printf("Program is starting...\n");

  wiringPiSetup(); //Initialize wiringPi

  for(i=0; i <ledCounts; i++) { //set pinMode for all led pins output
      pinMode(pins[i], OUTPUT);
  }


  //Start loop
  while(1){

    master_selector(ledCounts, pins, &left_to_right, &right_to_left, &turn_on_even_prog, &turn_on_odd_regress, &mid_to_edge_and_back, &random_leds);

  }



}

// initialization of functions
void left_to_right(int leds, int *pins){
  for(int i=0;i<leds;i++){       //move LED on from left to right
    digitalWrite(pins[i], LOW);
    delay(100);
    digitalWrite(pins[i], HIGH);
    printf("Left to right\n");
    printf("%d\n", i);
  }
}

void right_to_left(int leds, int *pins){
  for(int i=leds-1;i >-1;i--){  //move LED on from right to left
    digitalWrite(pins[i], LOW);
    delay(100);
    digitalWrite(pins[i], HIGH);
    printf("Right to left\n");
    printf("%d\n", i);
  }
}

void turn_on_even_prog(int leds, int *pins){
  for(int i=0;i<leds;i++){ //turn on even number pin indexes
    if(pins[i] % 2 == 0) {
      digitalWrite(pins[i], LOW);
      delay(300);
      digitalWrite(pins[i], HIGH);
      printf("Evens\n");
      printf("%d\n", i);
    }
}
}
void turn_on_odd_regress(int leds, int *pins){
  for(int i=ledCounts-1;i >-1;i--){ //turn on odd number pin indexes
    if(pins[i] % 2 != 0) {
      digitalWrite(pins[i], LOW);
      delay(300);
      digitalWrite(pins[i], HIGH);
      printf("Odds\n");
      printf("%d\n", i);
    }
  }
}

void mid_to_edge_and_back(int leds, int *pins){

  int bob_left = (leds/2)-1; //left half
  int bob_right = leds/2; //right half

  for(int i=0;i<bob_right;i++){ // turns on led from middle to edges
    digitalWrite(pins[bob_left], LOW);
    digitalWrite(pins[bob_right], LOW);
    delay(150);
    digitalWrite(pins[bob_left], HIGH);
    digitalWrite(pins[bob_right], HIGH);
    bob_left -= 1;
    bob_right += 1;
    printf("mid to edge\n");
    printf("%d %d\n", bob_left, bob_right);

    if(bob_left == (leds - leds) && bob_right == (leds -1)){ // turns on led from edges to middle
      while(bob_left != (leds/2) && bob_right != ((leds/2)-1)){
        digitalWrite(pins[bob_left], LOW);
        digitalWrite(pins[bob_right], LOW);
        delay(150);
        digitalWrite(pins[bob_left], HIGH);
        digitalWrite(pins[bob_right], HIGH);
        bob_left += 1;
        bob_right -= 1;
        printf("edge to mid\n");
        printf("%d %d\n", bob_left, bob_right);
        }
      }
    }
  //resets the bobs for the next loop
  bob_left = 0;
  bob_right = 0;

}

void random_leds(int leds, int *pins){
  srand(time(NULL));
  int jeb = 0;
  while(jeb < leds) {
    int r = rand() % leds;
    digitalWrite(pins[r], LOW);
    delay(100);
    digitalWrite(pins[r], HIGH);
    jeb += 1;
    printf("Random\n");
    printf("%d \n", r);
  }
}

void master_selector(int leds, int *pins, *func f1, *func f2, *func f3, *func f4, *func f5, *func f6){
  srand(time(NULL));
  int jeb = 0;
  func arr[6] = {f1, f2, f3, f4, f5, f6};

  while(jeb < 6) {
    int random = rand() % 6;
    arr[random](leds, pins);
    jeb++;
}


//end
