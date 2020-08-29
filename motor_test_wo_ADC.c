
#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <stdlib.h>

#define motorPin1 2  // sends high or low, basically polarity switch, if HIGH, positive, if low, negative and off to GND
#define motorPin2 0  // which determines the rotation side, clockwise or ccwise
#define enablePin 3 // for PWM wave



// motor function : determine the direction and speed of the motor

void motor(int value, char direction) {

  // boolean block to determine direction of rotation, stops at 50
  if(direction == 'f'){
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
  else if(direction == 'r'){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
  else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }

  softPwmWrite(enablePin, value); // sends PWM wave data to enablePin aka speed of rotation

  // boolean block to print appropriate message
  if(direction == 'f'){
    printf("Forward at %d%% speed\n", value); // print the speed of rotation in % value*2-100
  }
  else if(direction == 'r') {
    printf("Reverse at %d%% speed\n", value);
  }
  else {
    printf("Not going anywhere\n");
  }

}

int main(void){

  wiringPiSetup();
  pinMode(enablePin, OUTPUT); //set mode
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  softPwmCreate(enablePin, 0, 100); // define PWM pin

  while(1) { // basic while loop for test

    motor(0, 's'); // starts program with motor stopped for 2 sec
    delay(2000);

    for(int i=1;i<100;i++){ // rotate forward increasingly fast
      motor(i, 'f');
      delay(100);
    }

    for(int i=100;i>0;i--){ // rotate forward increasingly slow
      motor(i, 'f');
      delay(100);
    }

    motor(0, 's');
    delay(2000);

    for(int i=1;i<100;i++){ // rotate backward increasingly fast
      motor(i, 'r');
      delay(100);
    }

    for(int i=100;i>0;i--){ // rotate backward increasingly slow
      motor(i, 'r');
      delay(100);
    }


  }
return 0;
}
