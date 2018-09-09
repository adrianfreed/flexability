/*
 * 
 * 
 * 
//
11 A17
10 A16
9 A15 
8 A12

7 A5 T
6 A13
5 A11
4 A10

3 A6
2 A7
1T A8  T     A8->29(A18)
0T A9  T     A9->18(A4)

29 A0   29->33T
30 A1 T
31 A2 T T 
32 A3 T T
25 T
18 T 
33 T
DAC/A14
13 LED
 */
 
const boolean debugging = true; // 

void setup() {
analogReadResolution(13);
analogReadAveraging(4);

  Serial.begin(debugging?9600:57600);
}
const int delaytime=1;



void loop(){

 


pinMode(29, INPUT_PULLUP); 
pinMode(30, INPUT_PULLDOWN); 
if(delaytime!=0) delay(delaytime); // establish a settlement time before the read
    // this is to compensate for the potentially slow charge through the resistive material
    // to the input capacitor on the adc input.
{
  int vp = analogRead(A0);
  int vn = analogRead(A1);
  if(debugging) {Serial.print ("button 1 "); Serial.print(vp - vn);  Serial.println("D");}
Serial.println();

}
pinMode(31, INPUT_PULLUP); 
pinMode(32, INPUT_PULLDOWN); 
{
  int vp = analogRead(A2);
  int vn = analogRead(A3);
  if(debugging) {Serial.print ("button 2 "); Serial.print(vp - vn); Serial.println("D"); }
Serial.println();

}
{

pinMode(0, OUTPUT); digitalWrite(0,LOW);
  int touch = touchRead(1);
pinMode(1, INPUT_PULLUP); 
{
  int vp = analogRead(A8);
  int vn = analogRead(A9);
  pinMode(1, INPUT) ; // save power
  if(debugging) {Serial.print ("FSR Round "); Serial.print(touch); Serial.print("C    ");Serial.print(vp - vn); Serial.println("R"); }
Serial.println();

}
{

pinMode(2, OUTPUT); digitalWrite(2,LOW);
pinMode(3, INPUT_PULLUP); 
{
  int vp = analogRead(A6);
  int vn = analogRead(A7);
  pinMode(3, INPUT) ; // save power
  if(debugging) {Serial.print ("LDR "); Serial.print(vp - vn); Serial.println("R"); }
Serial.println();

}
}
}

}




