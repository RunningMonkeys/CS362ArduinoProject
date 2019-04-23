
#include <UTFT.h>

#include <LiquidCrystal.h>
#include <EEPROM.h>

#include "bitmaps.h"


// Declare which fonts we will be using
extern uint8_t SmallFont[];

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//rs 8 en 9 dx x

//joystick input
int xpos = 550;
int ypos = 550;
int button = 0;



//Lots of this has to change.

const unsigned long PADDLE_RATE = 50; //og 33
const unsigned long BALL_RATE = 55; //og 16
const int PADDLE_HEIGHT = 50; //og 14

void drawCourt();

int ball_x = 64, ball_y = 16;
int ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update;

unsigned long paddle_update;
const int CPU_X = 50;
int cpu_y = 16;

const int PLAYER_X = 430;
int player_y = 16;

const int VERT_WALL = 479;

const int HORIZ_WALL = 319;

int adc_key_in  = 0;
const int SW_pin = 12; // digital pin connected to switch output

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5 

byte runnerArea[16] {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
byte jump = 32;

//void printString();
int score = 0;
bool freeze_score = 0;

byte correct_code = 123;

unsigned long previousMillis = 0;
unsigned long previousMillisLED = 0;
unsigned long jumpTime = 0;
const int jumpLength = 500;

#define checkSafe runnerArea[1] == 32 || runnerArea[1] == 0

const byte chance_of_ob = 15; // might need to be 19
int speedOfScroller = 300;









UTFT myGLCD(CTE32HR,38,39,40,41);


void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
   myGLCD.InitLCD();
   myGLCD.clrScr();
   myGLCD.setFont(SmallFont);
   myGLCD.setBackColor(255,255,255);
   lcd.begin(16, 2); //Larger sized Screen
  Serial.begin(9600);
  lcd.createChar(0, dino);
  lcd.createChar(1, cacti);
  lcd.createChar(2, bird);
  lcd.createChar(3, block);
  pinMode(13, OUTPUT);
  randomSeed(A1);
  lcd.clear();
 myGLCD.setColor(0,0,255);
   printString("Push up for Pong or down for Dino Game");
   
  
}


void serialInput()
{
  String inString = Serial.readStringUntil('\n');

    if (inString != NULL) {
      inString.trim();
      if(inString.startsWith("y :"))
      {
        inString = inString.substring(3);
        // convert to an int 
        ypos = inString.toFloat();
      }
      if(inString.startsWith("b :"))
      {
        inString = inString.substring(3);
        // convert to an int 
        button = inString.toInt();
      }
      if(inString.startsWith("x :"))
      {
        inString = inString.substring(3);
        xpos = inString.toFloat();
      }
    }
}

void printString(String a)
{
  myGLCD.print(a,CENTER, 0);
}

void drawCourt() {
    myGLCD.setColor(255,255,255);
    myGLCD.drawRect(0, 0, VERT_WALL, HORIZ_WALL);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available())
{
  serialInput();
}
  if(ypos<300)
  {
    lcd.print("Playing Pong");
    myGLCD.clrScr();
    ypos = 550;
    xpos = 550;
      unsigned long start = millis();
    drawCourt();
    while(millis() - start < 2000);
    ball_update = millis();
    paddle_update = ball_update;
     while(true)
    {
    pong();
    }
  }
  else if(ypos > 600)
  {
    ypos = 550;
    xpos = 550;
    myGLCD.clrScr();
    myGLCD.setColor(0,0,255);
    printString("Playing dino game on other Screen");
     showSplashScreen(1000, true);
     
      while(true)
    {
       if(Serial.available())
    {
      serialInput();
    }
     dinoGame();
    }
  }

  
  
}
