// g++ ADCwithLED.c -o ADCwithLED -lwiringPi -lADCDevice to compile this one
// instead of gcc ADCwithLED.c -o ADCwithLED -lwiringPi


#include <wiringPi.h>
#include <stdio.h>
#include <wiringPiI2C.h>
#include <ADCDevice.hpp>
#include <softPwm.h>

#define ledPin 0


ADCDevice *adc; // define an ADC Device class object

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
  softPwmCreate(ledPin,0,100);

  while(1){
    int adcValue = adc->analogRead(0); // read analog value of A0 pin
    softPwmWrite(ledPin, adcValue*100/255);
    float voltage = (float)adcValue / 255.0 * 3.3; // calculate voltage
    printf("ADC Value : %d, \tVoltage : %.2f\n", adcValue, voltage);
    delay(30);
  }
  return 0;
}
