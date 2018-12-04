/*
Quick test of new chip that does debouncing and thresholding
of variable resistances.
The chips 6 switch outputs are hooked up
to a row of pins on a Teensy. (15-22)

*/


void setup() {
	Serial.begin(9600);
  pinMode(22,INPUT);
  pinMode(21,INPUT);
  pinMode(20,INPUT);
  pinMode(17,INPUT);
  pinMode(16,INPUT);
  pinMode(15,INPUT);
  
}

void loop() {
       delay(100);
    Serial.print(digitalRead(22));
    Serial.print(" ");
    Serial.print(digitalRead(21));
    Serial.print(" ");
    Serial.print(digitalRead(20));
    Serial.print(" ");
    Serial.print(digitalRead(17));
    Serial.print(" ");
    Serial.print(digitalRead(16));
    Serial.print(" ");
    Serial.print(digitalRead(15));
    Serial.println(" ");
}
