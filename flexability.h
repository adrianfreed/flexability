 #include <Arduino.h>
 
 #include <stdlib.h>
 
 typedef enum { fa1A=0, fa1B, fa2A, fa2B, fa3A, fa3B} faPairs;
 typedef enum { fa1W=0, fa1X, fa1Y, fa1Z, fa2W, fa2X, fa2Y, fa2Z,fa3W, fa3X, fa3Y, fa3Z} faQuads;


extern  char *faConnectorPairlabels[];
extern  char *faConnectorQuadlabels[] ;

extern const int faPairLast; 
extern const int faQuadLast;
extern  char *boardName;
extern const int faDigitalPins[];
extern const int faAnalogPins[];
extern const int faTouchPins[] ;
extern const bool faOpampBuffer[];
extern const float faPullupResistance; // Ohms
extern const float  faPowerSupply; //Volts



extern int faAnalogReadPair(faPairs c, bool pullup);
extern int faAnalogReadQuad(faQuads c, bool pullup);
extern int faTouchRead(faQuads c);
extern bool faSwitchPressedPair(faPairs c);

extern int32_t faAdcToResistance(int v, int maxvalue, float powervoltage, float pullupresistance);
