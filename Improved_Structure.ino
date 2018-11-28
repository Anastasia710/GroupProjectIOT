int buttonState[];  //make volatile int ?

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
 for (int i = 0; i < ledAmount; ++i)
  {
   pinMode(ledPinNum[i], OUTPUT);   //LED's are on pins 10, 11, 12, 13
   pinMode(buttonPinNum[i], INPUT); //Buttons are on pins 2, 3, 4, 5; 2 and 3 are external interrupt pins
  }

//set up interrupt
 attachInterrupt(digitalPinToInterrupt(buttonPinNum[0]), findButtonPin, Rising); //high
   //TODO create functions for each interrupt
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
   isSequenceCorrect = false;
          interrupts();
    GetAnswers();
  }
  Serial.print("Score: ");
  //PlayAgain();
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
                 
void getButtonPin()
{
  buttonState[0] = digitalRead(buttonPinNum[0]);
  buttonState[1] = digitalRead(buttonPinNum[1]);
  buttonState[2] = digitalRead(buttonPinNum[2]);
  buttonState[3] = digitalRead(buttinPinNum[3]);
 if (buttonState[0]==false && //other are true)
}

void PlayAgain()
{
  //check an input, if true then gameMode = true; else gameMode = false;
}
                 
void firstLight() //interrupt 0 = pin 2 match up with led pin 10
{
 LedPinNum[switchOrder[i]]
 {
  questionIsCorrect = true;
  ++i;
}
}
                 

