#include "flexability.h"
#include "Mouse.h"

// move the mouse cursor according to North South East West buttons
// debugging is provided over serial USB port
// I2C lcd display of sensed values is also provided

int range = 3;              // mouse pixel increment for  X and Y movement
int responseDelay = 20;     // response delay of the mouse, in ms


// adc values are scaled from 0 to 1000 
static void showValue(int adcvalue,  char *label)
{
   int v = 1000.0f *adcvalue/1023.0f;
    displayPrint(label, v);

   serialPrint(label, v);
}

static void showfaPairValue(faPairs c)
{
  if(c<=faPairLast)
    showValue(faAnalogReadPair(c, true), faConnectorPairlabels[c]);
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int oledreset = -1;
Adafruit_SSD1306 display(oledreset);

 
const boolean serialdebugging = false; // serial output

void setup() {


  if(serialdebugging) Serial.begin(serialdebugging?9600:57600);

   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
// Clear the buffer.
  display.clearDisplay();
 
}
const int delaytime=100;

void serialPrint(char *label, int v){
  if(serialdebugging) { Serial.print (label);Serial.print (" ");  Serial.print(v);  if(v<990) Serial.print("*"); Serial.println();}
}
void  displayPrint(char *label, int v)
{
  static int line = 0;
   display.print(label); display.print(" ");  display.print(v<1000?" ": "");display.print(v<100?" ": "");display.print(v<10?" ": ""); display.print(v);  display.print(v<990?"*": " "); 
   if(line %= 2) display.println(); else display.print("   ");

}

void loop()
{
  int movecount = 0;

  while(true)
  {

    int upState = faSwitchPressedPair(fa1A) ? 1: 0;
 
    int downState = faSwitchPressedPair(fa1B) ? 1: 0;
    int rightState = faSwitchPressedPair(fa2A) ? 1: 0;
    int leftState = faSwitchPressedPair(fa2B) ? 1: 0;
    // calculate the movement distance based on the button states:
    int  xDistance = (leftState - rightState) * range;
   int  yDistance = (upState - downState) * range;

  // if X or Y is non-zero, move:
    if ((xDistance != 0) || (yDistance != 0))
   {
    
       Mouse.move(xDistance, yDistance, 0);
       delay(movecount > 40? (responseDelay/2): responseDelay);   // speed up if you hold button down for while
       ++movecount;
   }
    else 
      break;
  }


  display.clearDisplay();

  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  // show all the pairs for this board
  for(int i=0;i<=faPairLast;++i)
      showfaPairValue((faPairs ) i);
  if(serialdebugging) Serial.println(boardName);

  display.println(boardName);
  display.display();

}




