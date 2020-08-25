
// Tech specs : working voltage 5V; min dist. = 2 cm; max dist. = 200 cm; working current = 12mA

#include <stdio.h>
#include <wiringPi.h>
#include <sys/time.h>

#define ledPin 2 // wiringPi numbers, physical pin = 13 or GPIO 27
#define trigPin 4 // wiringPi numbers, physical pin = 16 or GPIO 23
#define echoPin 5 // wiringPi numbers, physical pin = 18 or GPIO 24
#define MAX_DISTANCE 220  // max measure distance
#define timeOut MAX_DISTANCE*60 // is not signal bounced back after a while (past 220 cm), times out

// get pulse time of pin for more reference https://www.arduino.cc/reference/en/language/functions/advanced-io/pulsein/
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
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4); // make sure it is resetted
  digitalWrite(trigPin, HIGH); // sends high level to trig pin
  delayMicroseconds(10); // for 10-microsecond
  digitalWrite(trigPin, LOW); // turn off signal
  pingTime = pulseIn(echoPin, HIGH, timeOut);
  distance = (float)pingTime * 340.0/2.0/10000.0; // sound speed in air = 340m/s, distance = (echo time x sound velocity)/2
  return distance;
}

void short_distance_led(){
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
}

int main() {

  printf("Program is starting...");

  wiringPiSetup();

  float distance = 0.0;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW); // starts the program with led turned off

  while(1) {

    int med_count; // going with counters so the flashing doesn't cause delay in the data transfer
    int far_count; // going with counters so the flashing doesn't cause delay in the data transfer

    distance = getSonar();
    printf("The distance is : %2.f cm\n", distance);
    delay(100);
    if(distance <= 7.0) {
      printf("STOP!!!\n");
      digitalWrite(ledPin, HIGH);
    }
    else if(distance > 7.1 && distance < 25) {
      printf("Slow-med speed\n");
      short_distance_led();
    }
    else if(distance > 25.1 && distance < 75){
      digitalWrite(ledPin, LOW);
      printf("Med speed\n");
      med_count += 1;
      if(med_count == 3){
        digitalWrite(ledPin, HIGH);
        delay(100);
        med_count = 0;
      }

    }
    else {
      digitalWrite(ledPin, LOW);
      printf("full speed ahead!!\n");
      far_count += 1;
      if(far_count == 8){
        digitalWrite(ledPin, HIGH);
        delay(100);
        far_count = 0;
      }
    }
  }

  return 1;

}
