#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];

UTFT myGLCD(CTE32HR,38,39,40,41);

int xPos = 1;         // horizontal position of the graph
  float inByte = 0.0;      //vertical Position of the x or y value from the joystick
  boolean currLine = false;  //valuefor which weather the current inByte value is x or y so the color is correct
  const int height = 320;
  const int width = 480;


void setup() {
  // Setup LCD
  Serial.begin(9600);
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
  myGLCD.setBackColor(255,255,255);
}

void loop() {
  // put your main code here, to run repeatedly:
  
      

    if(Serial.available())
    {
      String inString = Serial.readStringUntil('\n');

    if (inString != NULL) {
      // trim off any whitespace:
      if(inString.startsWith("x :"))
      {
        inString.trim();
        inString = inString.substring(3);
        // convert to an int and map to the screen height:
        inByte = inString.toFloat();
        //println(inByte);
        inByte = map(inByte, 0, 1023, 0, height);
        myGLCD.setColor(127, 34, 255);
        myGLCD.drawLine(xPos, height, xPos, height - inByte);
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      myGLCD.clrScr();
      myGLCD.setBackColor(255,255,255);
    } else {
      // increment the horizontal position:
      xPos++;
    }
      }
      else if(inString.startsWith("y :"))
      {
        inString.trim();
        inString = inString.substring(3);
        // convert to an int and map to the screen height:
        inByte = inString.toFloat();
        //println(inByte);
        inByte = map(inByte, 0, 1023, 0, height);
        myGLCD.setColor(0,255,0);
        myGLCD.drawLine(xPos, height, xPos, height - inByte);
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      myGLCD.clrScr();
      myGLCD.setBackColor(255,255,255);
    } else {
      // increment the horizontal position:
      xPos++;
    }
        
      }
        
    
    

    }
    
    }

}
