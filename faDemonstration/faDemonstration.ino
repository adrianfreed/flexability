/*
 * Teensy LC Flexability Board
 *          Grove connector closest to USB end has opamp buffers for Touch pad applications
 * Teensy 2.0  with 3 grove connectors soldered  down the row of analog inputs(remove led or ledresistor)
 *          3 grove connectors along edge
 *          gives access to 12 ADC pins.
 *
 */
 // API
// Grove FlexAbility  analog input connectors.
// Each connector has 4 wires often configured as two pairs of sensors
// Connectors are numbered (left to right or top to bottom) 1, 2, 3...
// Pairs are A or B


// The four wires can also be used independently in capacitive sensing or by establishing
// a ground with an additional wire.
//  These Quads are labeled in  WXYZ   

// For resistive sensing here is how to read an analog value with the built-in pullup
// resistor enabled: int faAnalogReadPair(faPair c, true)
// Choose the particular connection from the enumaration below, e.g. fa1A
// For Quads use faAnalogReadQuad(faQuad c, true)


 typedef enum { fa1A=0, fa1B, fa2A, fa2B, fa3A, fa3B} faPairs;
 typedef enum { fa1W=0, fa1X, fa1Y, fa1Z, fa2W, fa2X, fa2Y, fa2Z,fa3W, fa3X, fa3Y, fa3Z} faQuads;
 char *faConnectorPairlabels[] = {"1A", "1B","2A", "2B", "3A", "3B"};
char *faConnectorQuadlabels[] = {"1W", "1X","1Y", "1Z","2W", "2X","2Y", "2Z","3W", "3X","3Y", "3Z"};

// Teensy 2.0 has 3 connectors and no op-amp
#if defined(TEENSYDUINO) 
   #if defined(__AVR_ATmega32U4__)
const int faPairLast = fa3B; 
const int faQuadLast = fa3Z;
const char *boardName = "FlexAbility T2.0";
const int faDigitalPins[] = {21,20,19,18,17,16,15,14,13,12,11,22 };
const int faAnalogPins[] = {A0,A1,A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
   #elif defined(__MKL26Z64__)  
const int faPairLast = fa2B;      
const int faQuadLast = fa2Z;

const char *boardName ="FlexAbility LC";
const int faDigitalPins[] = {0,1,3,4,5,6,9,10 };
const int faAnalogPins[] = {A11,A10,A6, A7, A9, A8, A3, A2};


    #elif defined(__MK20DX256__)       
const char *boardName = "FlexAbility Teensy 3.2";
    #elif defined(__MK64FX512__)
 const char *boardName = "FlexAbility Teensy 3.5";
   #elif defined(__MK66FX1M0__)
 const char *boardName = "FlexAbility Teensy 3.6";
    #else
       #error "Unsupported board"
    #endif
#endif
inline void gndOutput(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}
inline void floatPin(int pin)
{
  pinMode(pin, INPUT);
}
inline void pullupPin(int pin)
{
  pinMode(pin, INPUT_PULLUP);
}

int faAnalogReadPair(faPairs c, bool pullup)
{
  int v = -1;
  if(c<=faPairLast)
  {
    
    gndOutput(faDigitalPins[c*2+ 0] );
    if(pullup)
      pullupPin(faDigitalPins[c*2+ 1] );
    else
      floatPin(faDigitalPins[c*2+ 1]);

    v = analogRead(faAnalogPins[c*2 + 1]);
    floatPin(faDigitalPins[c*2+ 0]);
    if(pullup)floatPin(faDigitalPins[c*2+ 1]);

  }
  return v;
 
}
int faAnalogReadQuad(faQuads c, bool pullup)
{
  int v = -1;
  if(c<=faQuadLast)
  {
   
    if(pullup)
      pullupPin(faDigitalPins[c] );
    else
          floatPin(faDigitalPins[c]);
    v = analogRead(faAnalogPins[c]);
    if(pullup) floatPin(faDigitalPins[c]);

  }
  return v;
 
}

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
static void showfaQuadValue(faQuads c)
{
  if(c<=faQuadLast)
    showValue(faAnalogReadQuad(c, true), faConnectorQuadlabels[c]);
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
const int delaytime=100;

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

#ifdef ALLPAIRS
  // show all the pairs for this board
  for(int i=0;i<=faPairLast;++i)
      showfaPairValue((faPairs ) i);
#endif

#ifdef ALLQUADS
  // show all the quads for this board
 for(int i=0;i<=faQuadLast;++i)
      showfaQuadValue((faQuads ) i);
#endif

 for(int i=0;i<2;++i)
      showfaPairValue((faPairs ) i);
for(int i = fa2W;i<= faQuadLast;++i)
      showfaQuadValue((faQuads ) i);

// for(int i=0;i<8;++i)
 //     { Serial.print(i);Serial.print(" "), Serial.println(analogRead(faAnalogPins[i]  )); }
Serial.println(boardName);

display.println(boardName);
display.display();

}




