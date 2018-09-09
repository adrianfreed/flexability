/*
 
 * Teensy 2.0
 * (remove led or ledresistor)
 * 3 grove connectors along edge
 * gives access to 12 ADC pins.

 */
 // API
// Grove FlexAbility  analog input connectors.
// Each connector has 4 wires usually configured as two pairs of sensors
// Connectors on the TEensy 2.0 are number 1, 2, 3
// Pairs are A or B
// For resistive sensings here is how to read an analog value with the built-in pullup
// resistor enabled: int faAnalogReadPullup(faConnection c)
// Choose the particular connection from the enumaration below, e.g. fa1A


 typedef enum { fa1A, fa1B, fa2A, fa2B, fa3A, fa3B} faConnection;
 static  char *faConnectorlabels[] = {"1A", "1B","2A", "2B", "3A", "3B"};

inline void gndOutput(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}
inline void pullupPin(int pin)
{
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

int faAnalogReadPullup(faConnection c)
{
  switch(c)
  {
   case fa1A:
      gndOutput(21);
      pullupPin(20);
      return analogRead(A1);
    break;
    
    case fa1B:
      gndOutput(19);
      pullupPin(18);
      return analogRead(A3);
    break;
    
    case fa2A:
      gndOutput(17);
      pullupPin(16);
      return analogRead(A5);
    break;
    
    case fa2B:
      gndOutput(15);
      pullupPin(14);
      return analogRead(A7);
     break;
     
    case fa3A:
      gndOutput(13);
      pullupPin(12);
      return analogRead(A9);
    break;
    
    case fa3B :
      gndOutput(11);
      pullupPin(22);
      return analogRead(A11);
    break;
    default:
      return -1;
  }
  return -1;
}

// adc values are scaled from 0 to 1000 
static void showValue(int adcvalue,  char *label)
{
   int v = 1000.0f *adcvalue/1023.0f;
    displayPrint(label, v);

   serialPrint(label, v);
}

static void showfaConnectionValue(faConnection c)
{
  showValue(faAnalogReadPullup(c), faConnectorlabels[c]);
}

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int oledreset = -1;
Adafruit_SSD1306 display(oledreset);

 
const boolean debugging = true; // serial output

void setup() {


  Serial.begin(debugging?9600:57600);



   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
// Clear the buffer.
  display.clearDisplay();
 
}
const int delaytime=300;

void serialPrint(char *label, int v){
  if(debugging) { Serial.print (label);Serial.print (" ");  Serial.print(v);  if(v<990) Serial.print("*"); Serial.println();}
}
 void  displayPrint(char *label, int v)
{
  static int line = 0;
   display.print(label); display.print(" ");  display.print(v<1000?" ": "");display.print(v<100?" ": "");display.print(v<10?" ": ""); display.print(v);  display.print(v<990?"*": " "); 
   if(line %= 2) display.println(); else display.print("   ");
}
void loop(){
  display.clearDisplay();
  if(delaytime!=0) delay(delaytime); // establish a settlement time before the read

  Serial.println("Port and value scaled from 0 to 1000");
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  showfaConnectionValue(fa1A);
  showfaConnectionValue(fa1B);
  showfaConnectionValue(fa2A);
  showfaConnectionValue(fa2B);
  showfaConnectionValue(fa3A);
  showfaConnectionValue(fa3B);
    
Serial.println();

display.println("FlexAbility");
display.display();

}




