
// Tech specs : working voltage 5V; min dist. = 2 cm; max dist. = 200 cm; working current = 12mA

#include <softPwm.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

#define motorPin1 2  // sends high or low, basically polarity switch, if HIGH, positive, if low, negative and off to GND
#define motorPin2 0  // which determines the rotation side, clockwise or ccwise
#define enablePin 3 // for PWM wave
#define trigPin 4 // wiringPi numbers, physical pin = 16 or GPIO 23
#define echoPin 5 // wiringPi numbers, physical pin = 18 or GPIO 24
#define MAX_DISTANCE 220  // max measure distance
#define timeOut MAX_DISTANCE*60 // is not signal bounced back after a while (past 220 cm), times out

// get pulse time of pin for more reference https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/
// pulseIn doesn't work with rasb pi it seems, had to get that nice piece of code from joan here https://www.raspberrypi.org/forums/viewtopic.php?p=277768, thanks joan!
int pulseIn(int pin, int level, int timeout)
{
   struct timeval tn, t0, t1;

   long micros;

   gettimeofday(&t0, NULL);

   micros = 0;

   while (digitalRead(pin) != level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros += (tn.tv_usec - t0.tv_usec);

      if (micros > timeout) return 0;
   }

   gettimeofday(&t1, NULL);

   while (digitalRead(pin) == level)
   {
      gettimeofday(&tn, NULL);

      if (tn.tv_sec > t0.tv_sec) micros = 1000000L; else micros = 0;
      micros = micros + (tn.tv_usec - t0.tv_usec);

      if (micros > timeout) return 0;
   }

   if (tn.tv_sec > t1.tv_sec) micros = 1000000L; else micros = 0;
   micros = micros + (tn.tv_usec - t1.tv_usec);

   return micros;
}

float getSonar() { //get result of module in cm
  long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH); // sends high level to trig pin
  delayMicroseconds(10); // for 10-microsecond
  digitalWrite(trigPin, LOW); // turn off signal
  pingTime = pulseIn(echoPin, HIGH, timeOut);
  distance = (float)pingTime * 340.0/2.0/10000.0; // sound speed in air = 340m/s, distance = (echo time x sound velocity)/2
  return distance;
}

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

int main() {

  printf("Program is starting...");

  wiringPiSetup();

  float distance = 0.0;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enablePin, OUTPUT); //set mode
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  softPwmCreate(enablePin, 0, 100); // define PWM pin

  while(1) {
    distance = getSonar();
    printf("The distance is : %.2f cm\n", distance);
    delay(100);

    if(distance <= 7.0) {
      printf("STOP!!!\n");
      motor(0, 's');
    }
    else if(distance > 7.1 && distance < 25) {
      printf("Slow-med speed\n");
      motor(20, 'f');
    }
    else if(distance > 25.1 && distance < 75){
      printf("Med speed\n");
      motor(50, 'f');

    }
    else {
      printf("full speed ahead!!\n");
      motor(75, 'f');
    }

  }

  return 1;

}
