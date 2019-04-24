/*
  Zeke Thornburgh ethorn3
  Lab 9 - graph processing file 2 inputs
  This is the code to Get the input for the arduino and send it to the serial

  Joystick (or any 2 analog io devices) is hooked up to A1 and A0 with Y hooked up to A1 and X to A0

  Ref:
  https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
  http://arduino.cc/en/Tutorial/Graph

*/
int xpos;
int ypos;
int button;
String xPosString;
String yPosString;
String buttonString;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(8, INPUT);
}

void loop() {
  delay(50);
  // put your main code here, to run repeatedly:
  // xpos = analogRead(A0);
  ypos = analogRead(A1);
  // debounce here
   button = digitalRead(8);
  // xPosString = "x :";
  // xPosString.concat(xpos);
  yPosString = "y :";
  yPosString.concat(ypos);
  buttonString = "b :";
  buttonString.concat(button);
  //Serial.println(xPosString);
  Serial.println(yPosString);
  Serial.println(buttonString);

}



/*
 * /*
  Zeke Thornburgh ethorn3
  Lab 9 - graph processing file 2 inputs
  This is the code to display the Graph for analog inputs given over the serial
  

  Ref:
  https://learn.sparkfun.com/tutorials/connecting-arduino-to-processing#introduction
  http://arduino.cc/en/Tutorial/Graph







Processing file

import processing.serial.*;

  Serial myPort;        // The serial port
  int xPos = 1;         // horizontal position of the graph
  float inByte = 0.0;      //vertical Position of the x or y value from the joystick
  boolean currLine = false;  //valuefor which weather the current inByte value is x or y so the color is correct

  void setup () {
    // set the window size:
    size(400, 300);

    
    myPort = new Serial(this, Serial.list()[0], 9600);

    // don't generate a serialEvent() unless you get a newline character:
    myPort.bufferUntil('\n');

    // set initial background:
    background(0);
  }

  void draw () {
    // draw the line:
    
    if(currLine)
    {
    stroke(127, 34, 255);
    }
    else
    {
      stroke(0,255,0);
    }
        
    line(xPos, height, xPos, height - inByte);
    
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0);
    } else {
      // increment the horizontal position:
      xPos++;
    }
    
  }

  void serialEvent (Serial myPort) {
    // get the ASCII string:
    String inString = myPort.readStringUntil('\n');

    if (inString != null) {
      // trim off any whitespace:
      inString = trim(inString);
      // convert to an int and map to the screen height:
      inByte = float(inString);
      println(inByte);
      inByte = map(inByte, 0, 1023, 0, height);
    }
    currLine = !currLine;
     
  }
 */
