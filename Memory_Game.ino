

const int ledAmount = 4;
const int ledPinNum[ledAmount] = {10, 11, 12, 13};
const int buttonPinNum[ledAmount] = {4, 5, 6, 7};
const int interruptPinNum = 2;

bool asked = true;
bool start = false;
bool gameMode = false;
int* lightOrder = NULL;
volatile bool stageCorrect = false;
volatile int stage;
unsigned long totalTime = 0;
volatile unsigned long previousTime = 0;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));

  for (int i = 0; i < ledAmount; ++i)
  {
    pinMode(ledPinNum[i],OUTPUT);
    pinMode(buttonPinNum[i], INPUT_PULLUP);
  }
  pinMode(interruptPinNum, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(interruptPinNum), findButtonPin, FALLING);
}
void loop()
{

  while (start == false)
  {
    playAgain();
    delay(1000);
  }
  
  if (start == true)
  {
    startUpGame();
    int score = 0;
    int lives = 3;
    for (int i = 0; i < ledAmount; ++i)
    {digitalWrite(ledPinNum[i],LOW);}
    delay(500);
    
    Serial.print("Score: ");
    Serial.print(score);
    Serial.print("          Lives: ");
    Serial.println(lives);
    Serial.println("");
    
    for (int level = 1; lives > 0; ++level)
    {
      Serial.print("level: ");
      Serial.println(level);
      delay(1000);
      
      gameMode = false;
      setLightOrder(level);
      gameMode = true;
      
      bool worldCorrect = false;
      stage = 0;
      getAnswers(worldCorrect, lives, level, score);
      
      Serial.print("Score: ");
      Serial.println(score);
      
      if (worldCorrect == false && lives > 0)
      {loseLife(lives, score, level);}
      
      if (lightOrder != NULL)
      {
        delete[] lightOrder; 
        lightOrder = NULL;
      }
    }
    
    gameMode = false; //extra?
    gameOver();
    start = false;
  }

  

}

void playAgain()
{
  if (asked == false)
  {
    Serial.println("Press any button to play again");
    delay(1000);
    asked = true;
  }
  for (int i = 0; i < ledAmount; ++i)
  {
    if (digitalRead(buttonPinNum[i]) == LOW)
    {
      start = true;
      asked = false;
    }
  }
}
void startUpGame()
{
  Serial.println("Game Start!");
  for (int i = 0; i < ledAmount; ++i)
  {
    digitalWrite(ledPinNum[i], HIGH);
    delay(300);
  }
  
  for (int i = 0; i < ledAmount; ++i)
  {digitalWrite(ledPinNum[i], LOW);}
  
  for (int i = 1; i <= ledAmount; ++i)
  {
    digitalWrite(ledPinNum[ledAmount - i], HIGH);
    delay(300);
  }
  
  for (int i = 0; i < ledAmount; ++i)
  {digitalWrite(ledPinNum[i], HIGH);}
  
  gameMode = true;
}
void setLightOrder(int level)
{
  int lightTime = 1000;
  if (level % 5 == 0)
  {
    for (int i = level; i > 0 && lightTime >= 400; --i)
    {lightTime -= 25;}
  }

  if (lightOrder != NULL)
  {
    delete [] lightOrder;
  }
  lightOrder = new int[level];
  for (int i = 0; i < level; ++i)
  {lightOrder[i] = random(0, 4);}
  
  for (int i = 0; i < level; ++i)
  {
    digitalWrite(ledPinNum[lightOrder[i]], HIGH);
    delay(lightTime);
    digitalWrite(ledPinNum[lightOrder[i]], LOW);
    delay(400);
  }
}
void getAnswers(bool &worldCorrect, int &lives, int &level, int &score)
{

  for (int i = 0; i < level; ++i)
  {
    if (stage != level -1)
    {stageCorrect = false;}
    while (stage <= i)
    {
      getInactionTime(worldCorrect, lives, level);
      delay(1000);
      for (int j = 0; j < ledAmount; ++j)
      {
        if (digitalRead(buttonPinNum[j] == LOW))
          {
            digitalWrite(ledPinNum[j], LOW);
            gameMode = true;
          }
      }
    }
  }
 
  if (stageCorrect == true)
  {
    worldCorrect = true;
    ++score;
  }
  else if (stageCorrect != true)
  {
    for (int i = 0; i < ledAmount; ++i)
    {
      digitalWrite(ledPinNum[i], HIGH);   
    }
    delay(150);
     for (int i = 0; i < ledAmount; ++i)
    {
      digitalWrite(ledPinNum[i], LOW);   
    }
  }
}
void getInactionTime(bool &worldCorrect, int &lives, int &level)
{
  totalTime = millis();
  unsigned long currentTime = totalTime - previousTime;
  if (currentTime >= 300000)
  {
    stageCorrect = false;
    worldCorrect = false;
    lives = 0;
    level = -1;
    gameMode = false;
  }
}
void loseLife(int &lives, int &score, int &level)
{
  --lives;
  level = level - (3 - lives);
  if (level < 0)
  {level = 0;}
  score -= 3;
  if (score < 0)
  {score = 0;}
  Serial.print("                  Lives: ");
  Serial.println(lives);
}
void gameOver()
{
  Serial.println("Game Over");
  for (int k = 0; k < 3; ++k)
  {
    for (int i = 0; i < ledAmount; ++i)
    {digitalWrite(ledPinNum[i], HIGH);}
    delay(200);
    for (int i = 0; i < ledAmount; ++i)
    {digitalWrite(ledPinNum[i], LOW);}
    delay(200);
  }
  if (lightOrder != NULL)
  {
    delete [] lightOrder;
    lightOrder = NULL;
  }
}
void findButtonPin()
{
  if (gameMode == true && lightOrder != NULL)
  {
  gameMode = false;
  int one = digitalRead(buttonPinNum[0]);
  int two = digitalRead(buttonPinNum[1]);
  int three = digitalRead(buttonPinNum[2]);
  int four = digitalRead(buttonPinNum[3]);
  if (one == LOW && two == HIGH && three == HIGH && four == HIGH)
  {
    buttonOneTriggered(); 
  }
  else if (one == HIGH && two == LOW && three == HIGH && four == HIGH)
  {
    buttonTwoTriggered();
  }
  else if (one == HIGH && two == HIGH && three == LOW && four == HIGH)
  {
   buttonThreeTriggered();
  }
  else if (one == HIGH && two == HIGH && three == HIGH && four == LOW)
  {
    buttonFourTriggered();
  }
  }
}
void buttonOneTriggered()
{
  digitalWrite(ledPinNum[0],HIGH);
  if (buttonPinNum[0] == buttonPinNum[lightOrder[stage]])
  {
    stageCorrect = true;
    ++stage;
    previousTime = totalTime;
  }
  else
  {
    stage = 1000;
  }
}
void buttonTwoTriggered()
{
  digitalWrite(ledPinNum[1],HIGH);
  if (buttonPinNum[1] == buttonPinNum[lightOrder[stage]])
  {
    stageCorrect = true;
    ++stage;
    previousTime = totalTime;
  }
  else
  {
    stage = 1000;
  }
}
void buttonThreeTriggered()
{
  digitalWrite(ledPinNum[2],HIGH);
  if (buttonPinNum[2] == buttonPinNum[lightOrder[stage]])
  {
    stageCorrect = true;
    ++stage;
    previousTime = totalTime;
  }
  else
  {
    stage = 1000;
  }
}
void buttonFourTriggered()
{
  digitalWrite(ledPinNum[3],HIGH);
  if (buttonPinNum[3] == buttonPinNum[lightOrder[stage]])
  {
    stageCorrect = true;
    ++stage;
    previousTime = totalTime;
  }
  else
  {
    stage = 1000;
  }
}
