
// Tech specs : working voltage 5V; min dist. = 2 cm; max dist. = 200 cm; working current = 12mA

#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

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

int main() {

  printf("Program is starting...");

  wiringPiSetup();

  float distance = 0.0;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  while(1) {
    distance = getSonar();
    printf("The distance is : %.2f cm\n", distance);
    delay(100);
    if(distance <= 7.0) {
      printf("STOP!!!\n");
    }
    else if(distance > 7.1 && distance < 25) {
      printf("Slow-med speed\n");
    }else if(distance > 25.1 && distance < 75){
      printf("Med speed\n");
    }else {
      printf("full speed ahead!!\n");
    }





  }

  return 1;

}
