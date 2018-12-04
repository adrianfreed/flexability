/* UART Example, any character received on either the real
   serial port, or USB serial (or emulated serial to the
   Arduino Serial Monitor when using non-serial USB types)
   is printed as a message to both ports.

   This example code is in the public domain.
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

