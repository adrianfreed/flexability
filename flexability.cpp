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

#include "flexability.h"

 char *faConnectorPairlabels[] = {"1A", "1B","2A", "2B", "3A", "3B"};
 char *faConnectorQuadlabels[] = {"1W", "1X","1Y", "1Z","2W", "2X","2Y", "2Z","3W", "3X","3Y", "3Z"};

// Teensy 2.0 has 3 connectors and no op-amp
#if defined(TEENSYDUINO) 
   #if defined(__AVR_ATmega32U4__)
const int faPairLast = fa3B; 
const int faQuadLast = fa3Z;
 char *boardName = "FlexAbility T2.0";
const int faDigitalPins[] = {21,20,19,18,17,16,15,14,13,12,11,22 };
const int faAnalogPins[] = {A0,A1,A2, A3, A4, A5, A6, A7, A8, A9, A10, A11};
const int faTouchPins[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
const bool faOpampBuffer[] ={false, false, false, false, false, false, false, false, false, false, false, false };
const float faPullupResistance = 35000.0f; // Ohms
const float  faPowerSupply = 5.0f ; //Volts
   #elif defined(__MKL26Z64__)  
const int faPairLast = fa2B;      
const int faQuadLast = fa2Z;

 char *boardName ="FlexAbility LC";
const int faDigitalPins[] = {0,1,3,4,5,6,9,10 };
const int faAnalogPins[] = {A11,A10,A6, A7, A9, A8, A3, A2};
const int faTouchPins[] = {0,1,3,4, 23, 22, 17, 16};

const bool faOpampBuffer[] ={true, true, true, true, false, false, false, false };
const float faPullupResistance = 50000.0f; // Ohms    20k to 50k according to datasheet
const float  faPowerSupply = 3.3f ; //Volts

    #elif defined(__MK20DX256__)       
 char *boardName ="FlexAbility T3.2";
const int faDigitalPins[] = {0,1,3,4,5,6,9,10 };
const int faAnalogPins[] = {A11,A10,A6, A7, A9, A8, A3, A2};
const int faTouchPins[] = {0,1,-1,-1, 23, 22, 17, 16};

const bool faOpampBuffer[] ={true, true, true, true, false, false, false, false };
const float faPullupResistance = 50000.0f; // Ohms  20k to 50k according to datasheet
const float  faPowerSupply = 3.3f; //Volts


const int faPairLast = fa2B;      
const int faQuadLast = fa2Z;

    #elif defined(__MK64FX512__)
char *boardName = "FlexAbility Teensy 3.5";
   #elif defined(__MK66FX1M0__)
  char *boardName = "FlexAbility Teensy 3.6";
    #else
       #error "Unsupported board"
    #endif
#endif
static inline void gndOutput(int pin);
static inline void floatPin(int pin);
static inline void pullupPin(int pin);
static inline void gndOutput(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}
static inline void floatPin(int pin)
{
  pinMode(pin, INPUT);
}
static inline void pullupPin(int pin)
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
      delayMicroseconds(10);

if(! faOpampBuffer[c*2+1])
{
  // give the capacitor in the adc time to charge if the input impedance is high
  v = analogRead(faAnalogPins[c*2 + 1]);
  delayMicroseconds(500);
}
    v = analogRead(faAnalogPins[c*2 + 1]);
    floatPin(faDigitalPins[c*2+ 0]);
    if(pullup)floatPin(faDigitalPins[c*2+ 1]);

  }
  return v;
 
}

bool faSwitchPressedPair(faPairs c)
{
    int v = faAnalogReadPair(c, true);
    return (v>=0) && (v<200);
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
    if(! faOpampBuffer[c+1])
{
  // give the capacitor in the adc time to charge if the input impedance is high
  v = analogRead(faAnalogPins[c]);
  delayMicroseconds(500);
}
    v = analogRead(faAnalogPins[c]);
    if(pullup) floatPin(faDigitalPins[c]);

  }
  return v;
 
}

int faTouchRead(faQuads c)
{ 
  int rv = -1;
 #if defined(TEENSYDUINO) && !defined(__AVR_ATmega32U4__)
  if(faTouchPins[c] !=-1)
        rv = touchRead(faTouchPins[c]);
 #endif
  return rv;
}
int32_t faAdcToResistance(int v, int maxvalue, float powervoltage, float pullupresistance)
{
  int32_t rv = -1;
  if(v < 0.95f*maxvalue)
  {
    float t = (float) v/maxvalue;
     rv = t* pullupresistance / (1.0f-t);

  }
 
  return rv;
}
