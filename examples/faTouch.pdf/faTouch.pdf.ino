#include "flexability.h"


// adc values are scaled from 0 to 1000 
static void showValue(int adcvalue,   char *label)
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
static void showfaQuadcapValue(faQuads c)
{
  int v;
  if(c<=faQuadLast)
   { 
      v =faTouchRead(c);
      displayPrint(faConnectorQuadlabels[c], v);

   serialPrint(faConnectorQuadlabels[c], v);
   }
}
static void showfaQuadresistanceValue(faQuads c)
{
  int v;
  if(c<=faQuadLast)
   { 
      v =faAnalogReadQuad(c, true);
      displayResistancePrint(faConnectorQuadlabels[c], faAdcToResistance(v, 1023,faPowerSupply, faPullupResistance ));

   serialPrint(faConnectorQuadlabels[c], v);
  }
  
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
void  displayPrint( char *label, int v)
{
  static int line = 0;
   display.print(label); display.print(" ");  display.print(v<1000?" ": "");display.print(v<100?" ": "");display.print(v<10?" ": ""); display.print(v);  display.print(v<990?"*": " "); 
   if(line %= 2) display.println(); else display.print("   ");
}
void  displayResistancePrint( char *label, int32_t v)
{
  static int line = 0;
  char *unit = "o";
  if(v>=1000)
  {  v /= 1000;
     unit = "K";
  }else if (v>=1000)
   {
      v /= 1000;
      unit = "M";
   }
   
   display.print(label); display.print(" ");  display.print(v<1000?" ": "");display.print(v<100?" ": "");display.print(v<10?" ": ""); display.print(v); display.print(unit);
   display.print(v<-1?"*": " "); 
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

#define ALLCAPSENSE
#ifdef ALLCAPSENSE
  // show all the capsense for this board
 for(int i=0;i<=faQuadLast;++i)
      showfaQuadcapValue((faQuads ) i);
#endif
#define xALLRESISTANCE
#ifdef ALLRESISTANCE
  // show all the capsense for this board
 for(int i=0;i<=faQuadLast;++i)
      showfaQuadresistanceValue((faQuads ) i);
#endif


#ifdef ALLQUADS
  // show all the quads for this board
 for(int i=0;i<=faQuadLast;++i)
      showfaQuadValue((faQuads ) i);
#endif
#ifdef SOMEOFEACH
 for(int i=0;i<2;++i)
      showfaPairValue((faPairs ) i);
for(int i = fa2W;i<= faQuadLast;++i)
      showfaQuadValue((faQuads ) i);
#endif

// for(int i=0;i<8;++i)
 //     { Serial.print(i);Serial.print(" "), Serial.println(analogRead(faAnalogPins[i]  )); }
Serial.println(boardName);

display.println(boardName);
display.display();

}




