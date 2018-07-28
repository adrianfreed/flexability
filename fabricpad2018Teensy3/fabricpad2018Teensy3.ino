/*
 */
 
const boolean debugging = true; // send the processed data over serial console for debugging instead of OSC



const int leftpin=0, toppin=1, bottompin=2,  rightpin=3;

void setup() {
analogReadResolution(13);
analogReadAveraging(4);

  Serial.begin(debugging?9600:57600);
}
const int dtime=40;

struct  padVoltages {  int l; int t; int r; int b; } ;

struct padVoltages padRead() {
      struct padVoltages r;
      r.l = analogRead(A0);     r.l = analogRead(A0);     r.l = analogRead(A0);     r.l = analogRead(A0);
      r.t = analogRead(A1); r.t = analogRead(A1); r.t = analogRead(A1); r.t = analogRead(A1); r.t = analogRead(A1);
      r.b = analogRead(A2); r.b = analogRead(A2); r.b = analogRead(A2); r.b = analogRead(A2); r.b = analogRead(A2);
      r.r = analogRead(A3); r.r = analogRead(A3); r.r = analogRead(A3); r.r = analogRead(A3); r.r = analogRead(A3);
  return r;
}


void loop(){
  static int state = 0;
  struct padVoltages p;
 float x1, x2, y1, y2, z1, z2;


 
  if(dtime!=0)delay(dtime); // establish a settlement time before the read
    // this is to compensate for the potentially slow charge through the resistive material
    // to the input capacitor on the adc input.

pinMode(leftpin, INPUT); 
pinMode(rightpin, INPUT); 
pinMode(toppin, OUTPUT); digitalWrite(toppin, HIGH);
pinMode(bottompin, OUTPUT); digitalWrite(bottompin, LOW);

p = padRead();
 p = padRead(); 

if(debugging)
{Serial.println("raw X:");
Serial.print(p.t); Serial.print(" ");
Serial.print(p.b); Serial.print(" ");
Serial.print(p.l); Serial.print(" ");
Serial.print(p.r); 
Serial.println();
}
 x1 = 100.0f * (p.l -p.b)/((float)p.t-p.b);
x2 = 100.0f * (p.r -p.b)/((float)p.t-p.b);

pinMode(toppin, INPUT); 
pinMode(bottompin, INPUT); 
pinMode(leftpin, OUTPUT); digitalWrite(leftpin, HIGH);
pinMode(rightpin, OUTPUT); digitalWrite(rightpin, LOW);

p = padRead(); 
 
 p = padRead(); 




if(debugging)
{Serial.println("raw Y:");
Serial.print(p.l); Serial.print(" ");
Serial.print(p.r); Serial.print(" ");

Serial.print(p.t); Serial.print(" ");
Serial.print(p.b);
Serial.println(" ");
}
 y1 = 10.0f/8.0f *(100.0f * (p.t -p.r)/((float)p.l-p.r) - 20.0f);
 y2 =  10.0f/8.0f *(100.0f * (p.b -p.r)/((float)p.l-p.r) - 20.0f);

pinMode(bottompin, INPUT); 
pinMode(rightpin, INPUT); 
pinMode(toppin, OUTPUT); digitalWrite(toppin, HIGH);
pinMode(leftpin, OUTPUT); digitalWrite(leftpin, LOW);

p = padRead(); 
p = padRead(); 

if(p.b<(7205))
{
  if(state==0)
 {
   // (int)((x1/20)*5 + y2/20)
    Keyboard.print("abcdeefghhijklmnnopqqrstuvvwxyzz0123456789"[(int)((x1+x2)/10/2) + 10* ((int)(y1+y2)/2/33)]);
 }
 state = 1;
  Serial.print("y1 "); Serial.print(y1); Serial.print(" ");
Serial.print("y2 "); Serial.print(y2); Serial.print(" ");
Serial.print("x1 "); Serial.print(x1); Serial.print(" ");
Serial.print("x2 "); Serial.print(x2); Serial.println(" ");

}
else
  state = 0;
  

if(debugging)
{Serial.println("raw Z:");
Serial.print(p.t); Serial.print(" ");
Serial.print(p.l); Serial.print(" ");
Serial.print(p.b); Serial.print(" ");
Serial.print(p.r); 
Serial.println(" ");
Serial.println(" ");Serial.println(" ");Serial.println(" ");
}
 }


