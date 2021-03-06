#include "LedControl.h"
#include <math.h>
#include <stdlib.h>
#include <LiquidCrystal.h>

LedControl lc=LedControl(12,11,10,1);
LiquidCrystal lcd(8,9,5,4,3,2);

int n[10][8][8] = {
  {
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
  {0,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,0,1,0,0,0,0},
  {1,0,1,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
  {0,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,1,0,0,0,0,0},
  {1,1,0,0,0,0,0,0},
  {1,0,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
  {0,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
  {0,0,0,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,1,0,0,0,0,0,0},
  {1,1,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },
  {
 
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,0,1,0,0,0,0,0},
  {0,0,0,1,0,0,0,0},
  {1,0,0,1,0,0,0,0},
  {0,1,1,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
 
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,0,0,0,0,0}
  },

  {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0},
  {0,0,1,1,1,1,0,0},
  {0,1,0,0,0,0,1,0},
  {0,1,0,0,0,0,1,0},
  {0,0,0,0,0,0,0,0}
  }
  };

const int LRin = A0; //left / right
const int UDin = A1; //up / down.
 
bool blinkCandy;
int moveDir; 
int currMoveDir = 0;
int length;  
int last[64][2]; 
int x; 
int y; 
bool collision; 
bool incLength;
int candyPos[2];  
bool candyOnScreen;
bool printIntro=true;
int score;
int highscore=0;
bool newHighscore;
int speed;
int looper=0;
 
void setup() 
{ 
  lc.shutdown(0,false);
  lc.setIntensity(0,4);
  lc.clearDisplay(0);
  lcd.begin(16,2);
  
}


void loop()                          //loop-ul are 2 sectiuni
{
  if (printIntro == true)
  {
   
    initVar();
    initialLcdMsg();                //una pentru cazul in care
    intro();                        //este afisat introul jocului
    initScore();
    countdown();
   
  }
  else
  {

    checkScore();                  //cealalta pentru cazul in care jocul se desfasoara
    looper++;
  
    checkMove();
    if (looper % speed == 0)      //sarpele se muta corespunazator vitezei 
      doMove();
   
    if (looper % speed == 0) 
      checkCollision();
      
    if (collision)  
      gameOver();
  
    candyCollision();
  
    while (!candyOnScreen) 
      createCandy(); 
      
    if (looper % 500 == 0) 
      candyBlink();
  
  }
}

void initVar(void)
{
  newHighscore = false;                 //de fiecare data cand un joc nou incepe, intializez toate variabilere (ex viteza, scor etc)
  score = 0;
  printIntro = true;
  moveDir = rand() % 4;
  currMoveDir = rand() % 4;
  length = 1;
  x = rand() % 8;  //x si y reprezinta coordonatele "capului" sarpelui
  y = rand() % 8;  //generez random pozitia capului initial
  
  last[0][0] = x;
  last[0][1] = y;
  lc.setLed(0, last[0][0], last[0][1], true); 
  for(int i = 1; i < 64; i++)
  { 
    last[i][0] = -1;       //last este un vector care retine pozitiile tuturor ledurilor care intra in componenta sarpelui
    last[i][1] = -1; 
  }
  collision = false;
  incLength = false;
  candyOnScreen = false;
  blinkCandy = true;
  speed = 1000;
  
}

void initialLcdMsg(void)   //da jucatorului un tips despre cum se poate incepe jocul
{
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("MAKE ANY MOVE ");      
    lcd.setCursor(4, 1);
    lcd.print("TO PLAY");
}
void intro(void)    //afiseaza S N A K E pe matrice pana cand este detectata orice miscare a joystickului
{
  int current = 0;
  while (1)
  {
    lc.clearDisplay(0);
    
    if (detectJoystickMove() == 1) 
    {
      printIntro=false;
      return;
    }

    for (int x1 = 0; x1 < 8; x1++)
      for (int y1 = 0; y1 < 8; y1++)
        if (n[current][x1][y1] == 1) 
          lc.setLed(0,y1+2,7-x1,true); 
          
    current++;
    if (current == 5)
      current=0;
      
    unsigned long prevMil = millis();
    unsigned long currMil = millis();
    while (currMil - prevMil < 600)
        currMil = millis();
  } 
}

int detectJoystickMove(void) //returneaza 1 in cazul este detectata o miscare o joystickului
{
  int LR = analogRead(LRin);
  int UD = analogRead(UDin);
 
  if(LR > 600 || LR < 400 || UD > 600 || UD < 400)
    return 1;

  return 0;
 
}

void initScore(void) //este initializat lcd-ul ca sa afiseze scorul curent = 0 si highscorul 
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCORE  HIGHSCORE");
  lcd.setCursor(2, 1);
  lcd.print('0');
  lcd.setCursor(11,1);
  lcd.print(highscore);
}
void countdown(void)       //dupa detectarea unei miscari a joystickului, pe matrice se afiseaza o numerotare inversa, dupa care jocul propriu zis incepe
{
  int current = 7;

  while (1)
  {
   lc.clearDisplay(0);
   if (current == 4)
     {
      return;
     }
 
  for (int x1 = 0; x1 < 8; x1++)
    for (int y1 = 0; y1 < 8; y1++)
       if (n[current][x1][y1] == 1) 
         lc.setLed(0, y1+2, 7-x1, true); 
          
  current--;
      
  unsigned long prevMil = millis();
  unsigned long currMil = millis();
  while (currMil - prevMil < 500)
    currMil=millis();
   }
}

void checkScore(void)   // verifica daca trebuie modificat scorul afisat de lcd
{
    if (length - 1 != score)
    {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SCORE  HIGHSCORE");
    lcd.setCursor(2, 1);
    lcd.print(length-1);
    score = length-1;
    if (highscore < score)     //verifica daca score-ul curent depasste highscorul, caz in care highscoreul trebuie actualizat
     { 
      highscore = score;
      newHighscore = true;    //variabila care retine daca jucatorul a ajuns la un nou highscore pentru a afisa un mesaj corespunzator la sfarsitul jocului
     }
    lcd.setCursor(11,1);
    lcd.print(highscore);
    
    }

    return;
}

void gameOver(void)        //daca jocul s-a terminat
{
    lc.clearDisplay(0);
    lcd.clear();
    if (newHighscore == true)      //si jucatorul a obtinut un nou hishscore, pe lcd se afiseaza un mesaj corespunzator si pe matrice un smiley face
    {
      lcd.setCursor(1, 0);
      lcd.print("NEW HIGHSCORE!");
      lcd.setCursor(7,1);
      lcd.print(highscore);
     
      for (int x1 = 0; x1 < 8; x1++)
        for (int y1 = 0; y1 < 8; y1++)
          if (n[8][x1][y1] == 1) 
            lc.setLed(0, y1, 7-x1, true); 
    }
    else                         //daca nu s-a obtinut un nou highscore, pe lcd se afiseaza un mesaj si pe matrice un sadface
    {
      lcd.setCursor(4, 0);
      lcd.print("NICE TRY!");  
      lcd.setCursor(7,1);
      lcd.print(score);
  
      for (int x1 = 0; x1 < 8; x1++)
        for (int y1 = 0; y1 < 8; y1++)
          if (n[9][x1][y1] == 1) 
            lc.setLed(0, y1, 7-x1, true); 
    }
    
    unsigned long prevMil = millis();      //mesajele stagneaza pentru 2,5 secunde, dupa care se marcheaza ca trebuie afisat intr-ul din nou
    unsigned long currMil = millis();
    while (currMil - prevMil < 2500)
        currMil = millis();
    
    printIntro = true;
    return;
}
 

void candyBlink(void)                    //schimba starea "candy"-ului din ON in OFF si viceversa pentru a obtine blink-ul ledului
{
  if (blinkCandy) 
    lc.setLed(0, candyPos[0], candyPos[1], true);
  else 
    lc.setLed(0, candyPos[0], candyPos[1], false);
    
  blinkCandy = !blinkCandy;
}

void led(int x, int y)                  //realizeaza glisarea sarpelui; are ca parametri x si y care reprezinta pozitia noului cap al sarpelui
{
  if(!incLength)
  {

    lc.setLed(0, last[0][0], last[0][1], false);  //daca lungimea nu s-a modificat, stingem ledul de pe pozitia 0,0 (reprezinta coada sarpelui)
    for (int i = 0; i < length - 1; i++)
    {
      last[i][0] = last[i+1][0];                  //iar pe celelalte le glisam la stanga
      last[i][1] = last[i+1][1];
    }
 
  }
  else
  {                             
    length++;
    if (length == 64) 
      {
        gameOver();             //daca lungimea este 64 incheiem jocul
        return;
      }
      
    if (length % 5 == 0)        //o data la 5 cresteri in lungime, micsoram valoare variabilei speed care va rezulta intr-o viteza mai mare
      speed = speed-200;
      
    incLength = false;
  }
 
  last[length-1][0] = x;         //la final aprindem ledul corespunzator noului cap
  last[length-1][1] = y;
 
  lc.setLed(0, last[length-1][0], last[length-1][1], true);
 
}

void checkMove(void)            //calculeaza noua miscare si actualizeaza directia de miscare daca nu exista conflicte
{
  int LR = analogRead(LRin);
  int UD = analogRead(UDin);
 
  if(LR > 600 && currMoveDir != 2) moveDir = 0; 
  if(LR < 400 && currMoveDir != 0) moveDir = 2; 
  if(UD > 600 && currMoveDir != 3) moveDir = 1; 
  if(UD < 400 && currMoveDir != 1) moveDir = 3; 
}

void doMove(void)              
{
  currMoveDir = moveDir;
  if(moveDir == 0) moveRight();
  if(moveDir == 1) moveUp();
  if(moveDir == 2) moveLeft();
  if(moveDir == 3) moveDown();
  led(x,y); 
}

void incrementLength(void)
{
  incLength = true; 
}
 
void moveRight(void)
{
  x++;
  while (x >= 8)
    x = x - 8;
}
void moveLeft(void)
{
  x--;
  while (x < 0)
    x = x + 8;
}
void moveUp(void)
{
  y--;
  while (y < 0)
    y = y + 8;
}
void moveDown(void)
{
  y++;
  while (y >= 8)
    y = y - 8;
}

void createCandy(void)   //creeaza o pozitie noua pentru "candy" verificand dac pozitia generata nu se suprapune cu vreun led al sarpelui
{
 
  int xR = rand() % 8;
  int yR = rand() % 8;
 
  for (int i = 0; i <= length; i++)
    if (xR == last[i][0] && yR == last[i][1])
    {
      candyOnScreen = false; 
      return;
    }
    
  candyPos[0] = xR;
  candyPos[1] = yR;
  candyOnScreen = true;
  lc.setLed(0, xR, yR, true);
}

void candyCollision()           //detecteaza daca [,] capul sarpelui se suprapune cu pozitia candyului
{
  if (last[length-1][0] == candyPos[0] && last[length-1][1] == candyPos[1])
  {
    candyOnScreen = false; 
    incrementLength();
  }
}

void checkCollision()          //verifica daca [,] capul sarpelui se suprapune cu vreun led al sarpelui diferit de el
{
  int xP = last[length-1][0];
  int yP = last[length-1][1];
 
 
  for (int i = 0; i < length - 1; i++)
    if (last[i][0] == xP && last[i][1] == yP)
      collision = true;
  
  return;
 
}


