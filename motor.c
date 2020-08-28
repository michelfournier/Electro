// g++ motor.c -o motor -lwiringPi -lADCDevice to compile this one
// instead of gcc motor.c -o motor -lwiringPi

// this is using a potentionmeter to control the PWM wave. could be replace with software only and forgo the ADV Device
// since in most cases, I'm not gonna turn a knob to control the motor(s)

#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <ADCDevice.hpp>
#include <softPwm.h>
#include <math.h>
#include <stdlib.h>

#define motorPin1 2  // sends high or low, basically polarity switch, if HIGH, positive, if low, negative and off to GND
#define motorPin2 0  // which determiens the rotation side, clockwise or ccwise 
#define enablePin 3 // for PWM wave

ADCDevice *adc; // define an ADC Device class object

// Map function: map the value from a range to another range
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh) {
  return (toHigh-toLow)*(value-fromLow)/(fromHigh-fromLow) + toLow;
}

// motor function : determine the direction and speed of the motor according to ADC

void motor(int ADC) {
  int value = ADC -128; //porque pwm is 256, so full clockwise would be 128 and full cc-wise -128
  if(value>0){
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    printf("going forward...\n");
  }
  else if(value<0){
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    printf("going reverse...\n");
  }
  else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    printf("Stop\n");
  }
  softPwmWrite(enablePin, map(abs(value), 0, 128, 0, 100));
  printf("The PWM duty cycle is %d%%\n", abs(value)*100/127); // print the PWM duty cycle
}

int main(void){
  adc = new ADCDevice();
  printf("Program is starting...");

  if(adc->detectI2C(0x48)){
    delete adc;
    adc = new PCF8591(); // if detected, create instance of PCF8591
  }
  else if(adc->detectI2C(0x4b)) {
    delete adc;
    adc = new ADS7830();
  }
  else {
    printf("No correct I2C found\n");
    return -1;
  }

  wiringPiSetup();
  pinMode(enablePin, OUTPUT); //set mode
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  softPwmCreate(enablePin, 0, 100); // define PWM pin

  while(1) {
    int value = adc->analogRead(0); // read analog value of A0
    printf("ADC value : %d \n", value);
    motor(value); // make the motor rotate with speed (analog value of A0)
    delay(100);
  }

return 0;

}
