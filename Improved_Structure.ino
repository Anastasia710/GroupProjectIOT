#include <PinChangeInt.h>

void setup()
{
Serial.begin(9600);
randomSeed(analogRead(0)); // an unconnected input pin
// move time variable to GetAnswers ?
unsigned long totalTime;
unsigned long previousTime = 0;
unsigned long currentTime;  //since last action

//set up Arduino pins
int ledAmount = 4;
int ledPinNum[ledAmount] = {10, 11, 12, 13};
int buttonPinNum[ledAmount] = {2, 3, 4, 5};  
//volatile bool buttonState[ledAmount] = //match up with buttonPin inputs; put in different function?
 for (int i = 0; i < ledAmount; ++i)
  {
   pinMode(ledPinNum[i], OUTPUT);   //LED's are on pins 10, 11, 12, 13
   pinMode(buttonPinNum[i], INPUT); //Buttons are on pins 2, 3, 4, 5; 2 and 3 are external interrupt pins
  }

//set up interrupts
 attachInterrupt(digitalPinToInterrupt(buttonPinNum[0]), firstLight, CHANGE);
 attachInterrupt(digitalPinToInterrupt(buttonPinNum[1]), secondLight, CHANGE);
 //TODO interrupt on pin 4
 //TODO interrupt on pin 5
   //TODO create functions for each interrupt
}

void GetInactionTime() // move below GetAnswers()
{
  totalTime = millis();
  currentTime = totalTime - previousTime;
  previousTime = totalTime;

  if(currentTime >= 300000)
  {
    questionIsCorrect = false;
    level = -1;
    isSequenceCorrect = false;
    gameMode = false;
  }
}

void SetLightOrder()
{
  int lightTime = 1000; // adjust with level increase
  for (int i = 0; i < level; ++i)
  {
    switchOrder[i] = random(0,4); //the array size of LEDPinNum
  }
  for (int i = 0; i < level; ++i)
  {
    digitalWrite(LEDPinNum(switchOrder[i]), HIGH);
    delay(lightTime);
    digitalWrite(LEDPinNum(switchOrder[i], LOW);
    delay(lightTime/2);
  }
}

void GetAnswers()
{
  isSequenceCorrect = false; // move to loop() under call for SetLightOrder
  bool questionIsCorrect = false;
  for (int i = 0; i < level;)
  {
    questionIsCorrect = false;
    GetInactionTime();
    delay(500); //250, 1000
  }
  if (questionIsCorrect == true)
  {
    isSequenceCorrect = true;
    ++score;
  }
}

void PlayAgain()
{
  //check an input, if true then gameMode = true; else gameMode = false;
}

void loop()
{
  bool gameMode = true;
  while (gameMode == true)
  {
          //noInterrupts();
  int score = 0;
  bool isSequenceCorrect = true; // can you keep going?
  for (int level = 1; level != -1; ++level) //level != -1 && isSequenceCorrect == true;
  {
          noInterrupts();
    SetLightOrder();
          interrupts();
    GetAnswers();
  }
  Serial.print("Score: ");
  //PlayAgain();
  }
}
