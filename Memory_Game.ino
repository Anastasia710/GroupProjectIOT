#include "PinChangeInterrupt.h"


void setup()
{
Serial.begin(9600);

randomSeed(analogRead(0)); // an unconnected input pin
int ledAmount = 4;
int ledPinNum[ledAmount] = {10, 11, 12, 13};
int buttonPinNum[ledAmount] = {2, 3, 4, 5};  
//volatile bool buttonState[ledAmmount] = //match up with buttonPin inputs


  for (int i = 0; i < ledAmount; ++i)
  {
   pinMode(ledPinNum[i], OUTPUT);   //LED's are on pins 10, 11, 12, 13
   pinMode(buttonPinNum[i], INPUT); //Buttons are on pins 2, 3, 4, 5; 2 and 3 are external interrupt pins
  }

 attachInterrupt(digitalPinToInterrupt(buttonPinNum[0]), firstLight, CHANGE);
 attachInterrupt(digitalPinToInterrupt(buttonPinNum[1]), secondLight, CHANGE);
}

void loop() 
{
 // for (int level = 1; gamePower == true && answer == true; ++level)
  for (int level = 1; level != -1; ++level)
  {
  
  noInterrupts();
  //order of lights
  int lightTime = 1000;
  volatile int switchOrder[level];
  for (int i = 0; i < level; ++i)
  {switchOrder[i] = random(1, 5);}  

  //display order (light up)
  for (int i = 0; i < level; ++i)
  {
    digitalWrite(switchOrder[i], HIGH);
    delay(lightTime);
    digitalWrite(switchOrder[i], LOW);
    delay(lightTime / 2);
  }
  interrupts();

  bool isSequenceCorrect = false;
    bool questionIsCorrect = false;
    for (int q = 0; q < level; ++q)
    { questionIsCorrect = false;
      //timer limit to end; only ++q in fistLight(),secondLight(),... 
      //if answer is right: questionIsCorrect=true; if answer is wrong level = -1;
    }
    if (questionIsCorrect == true)
    {isSequenceCorrect = true;
    //add to score}
    

  }
}

void firstLight()
{}
void secondLight()
{}
