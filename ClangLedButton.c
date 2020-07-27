#include <wiringPi.h>
#include <stdio.h>

#define ledPin    0 //define the ledPin
#define buttonPin 1 //define the buttonPin

int jeb;
int bob;

void  main(void)
{

	jeb = 0;
	bob = 0;

	printf("Program is starting ... \n");

	//setting the things up

	wiringPiSetup(); //Initialize wiringPi.
	pinMode(ledPin, OUTPUT); //Set ledPin to output
	pinMode(buttonPin, INPUT); //Set buttonPin to input
	pullUpDnControl(buttonPin, PUD_UP); //pull up to HIGH level

	//loop
	while(1){



		if(digitalRead(buttonPin) == LOW){         //button is pressed
			digitalWrite(ledPin, HIGH);           //Make GPIO output HIGH level
			if(jeb == 0){
				printf("Button is pressed, led turned on >>>\n"); //Output information on terminal
				jeb += 1; //message won't show repeatedly on the screen
			}

			bob = 0;          //reset the block on "turned off" message



			}
			else {	                       //button is released
				digitalWrite(ledPin, LOW); //Make GPIO output LOW level
				if(bob == 0){
					printf("Button is released, led turned off <<<\n"); //Output information on terminal
					bob += 1;           //message won't show repeatedly on the screen
					}

				jeb = 0;          //reset the block on "turned on" message


	}
}
}
