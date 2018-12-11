  const int ledAmount = 4;
  const int buttonPinNum[ledAmount] = {4, 5, 6, 7};
  const int ledPinNum[ledAmount] = {10, 11, 12, 13};
  const int interruptPinNum = 2;

  int* lightOrder = NULL;
  unsigned long totalTime;
  unsigned long currentTime;
  unsigned long previousTime = 0;
  bool asked = true;
  bool gameMode = false;
  

  //  score,lives, levels, stagecorrect, worldcorrect, lighttime
  
void setup()
{
  Serial.begin(9600);
  
    for (int i = 0; i < ledAmount; ++i)
  {
    pinMode(buttonPinNum[i], INPUT_PULLUP);
    pinMode(ledPinNum[i], OUTPUT);
  }
  pinMode(interruptPinNum, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPinNum), findButtonPin, CHANGE);

  pinMode(ledPinNum[3], OUTPUT);
}

void loop() 
{
      int testb2 = digitalRead(buttonPinNum[1]);
    if (testb2 == HIGH)
    {
      digitalWrite(ledPinNum[1], HIGH);
    }
    else
    {
      digitalWrite(ledPinNum[1], LOW);
    }
        int testb1 = digitalRead(buttonPinNum[0]);
    if (testb1 == HIGH)
    {
      digitalWrite(ledPinNum[0], HIGH);
    }
    else
    {
      digitalWrite(ledPinNum[0], LOW);
    }
    delay(1000);
    digitalWrite(ledPinNum[3], LOW);
}

void findButtonPin()
{
  buttonOneTriggered();
  buttonTwoTriggered();
  buttonThreeTriggered();
  buttonFourTriggered();
}

void buttonOneTriggered()
{
  digitalWrite(ledPinNum[3], HIGH);
}

void buttonTwoTriggered()
{
  digitalWrite(ledPinNum[3], HIGH);
}

void buttonThreeTriggered()
{
  digitalWrite(13, HIGH);
}

void buttonFourTriggered()
{
  digitalWrite(13, HIGH);
}

void playAgain()
{

}

void startupGame()
{

}

void setLightOrder()
{

}

void getAnswers()
{

}

void getInactionTime()
{

}

void loseLife()
{

}

void gameOver()
{

}