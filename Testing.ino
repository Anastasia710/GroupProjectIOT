  const int ledAmount = 2;
  const int buttonPinNum[ledAmount] = {4, 5};
  const int ledPinNum[ledAmount] = {10, 11};
  const int buttonInterruptPinNum = 2;
  
void setup()
{
  Serial.begin(9600);
  
    for (int i = 0; i < ledAmount; ++i)
  {
    pinMode(buttonPinNum[i], INPUT_PULLUP);
    pinMode(ledPinNum[i], OUTPUT);
  }
  pinMode(buttonInterruptPinNum, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonInterruptPinNum), findButtonPin, CHANGE);

  pinMode(13, OUTPUT);
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
    digitalWrite(13, LOW);
}

void findButtonPin()
{
  buttonOneTriggered();
}

void buttonOneTriggered()
{
  digitalWrite(13, HIGH);
}
