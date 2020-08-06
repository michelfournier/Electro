#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define ledPin 1

void main(void){

  int i;

  printf("Program is starting...\n");

  wiringPiSetup();

  softPwmCreate(ledPin, 0, 100); //create softPWM pin

  while(1) {

    for(i=0;i<100;i++){
      softPwmWrite(ledPin, i);
      printf("%d\n", i);
      delay(10);

    }

    delay(100);

    for(i=0;i<5;i++){
      digitalWrite(ledPin, LOW);
      delay(800);
      digitalWrite(ledPin, HIGH);
      printf("%s\n", "Bob");
}



    for(i=100;i>=0;i--){
      softPwmWrite(ledPin,i);
      printf("%d\n", i);
      delay(10);

    }



  }


}
