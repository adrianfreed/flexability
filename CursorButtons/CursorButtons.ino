/* Mouse Cursor Buttons
 *  Teensy 3
   Select Keyboard from the "Tools > USB Type" menu
   
   AF July 2018

   Apple's Keyboard mapping for cursor control:
   
  Move up  8 or numeric keypad 8
  Move down K or numeric keypad 2
  Move left U or numeric keypad 4
  Move right  O or numeric keypad 6
  Move diagonally down and to the left  J or numeric keypad 1
  Move diagonally down and to the right L or numeric keypad 3
  Move diagonally up and to the left  7 or numeric keypad 7
  Move diagonally up and to the right 9 or numeric keypad 9
  Press the mouse button  I or numeric keypad 5
  Hold the mouse button M or numeric keypad 0
  Release the mouse button  . (period)
*/

#include <Bounce.h>
const int debounceTime = 20;  //mS
//Bounce object handles contact chatter or "bounce", and simplifies state changes

Bounce button0 = Bounce(0, debounceTime);
Bounce button1 = Bounce(1, debounceTime);  
Bounce button2 = Bounce(2, debounceTime);  
Bounce button3 = Bounce(3, debounceTime);  
Bounce button4 = Bounce(4, debounceTime);
Bounce button5 = Bounce(5, debounceTime); 
Bounce button6 = Bounce(6, debounceTime); 
Bounce button7 = Bounce(7, debounceTime);
Bounce button8 = Bounce(8, debounceTime);
Bounce button9 = Bounce(9, debounceTime);
Bounce button10 = Bounce(10, debounceTime);

void setup() {
 
  // The pushbuttons connect from each pin to ground. 

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);  
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
 pinMode(10, INPUT_PULLUP);
}

void loop() {
  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();
  button8.update();
  button9.update();
 button10.update();

  // Check each button for "falling" edge, i.e, high to low transition.
   if (button0.fallingEdge()) {
    Keyboard.print("8");
  }
  if (button1.fallingEdge()) {
    Keyboard.print("k");
  }
  if (button2.fallingEdge()) {
    Keyboard.print("u");
  }
  if (button3.fallingEdge()) {
    Keyboard.print("o");
  }
  if (button4.fallingEdge()) {
    Keyboard.print("j");
  }
  if (button5.fallingEdge()) {
    Keyboard.print("l");
  }
  if (button6.fallingEdge()) {
    Keyboard.print("7");
  }
  if (button7.fallingEdge()) {
    Keyboard.print("9");
  }
  if (button8.fallingEdge()) {
    Keyboard.print("i");
  }
  if (button9.fallingEdge()) {
    Keyboard.print("m");
  }
 if (button10.fallingEdge()) {
    Keyboard.print(".");
  }

 #ifdef RELEASEneeded
 if (button0.risingEdge()) {
    Keyboard.println("B0 release");
  }
  if (button1.risingEdge()) {
    Keyboard.println("B1 release");
  }
  if (button2.risingEdge()) {
    Keyboard.println("B2 release");
  }
  if (button3.risingEdge()) {
    Keyboard.println("B3 release");
  }
  if (button4.risingEdge()) {
    Keyboard.println("B4 release");
  }
  if (button5.risingEdge()) {
    Keyboard.println("B5 release");
  }
  if (button6.risingEdge()) {
    Keyboard.println("B6 release");
  }
  if (button7.risingEdge()) {
    Keyboard.println("B7 release");
  }
  if (button8.risingEdge()) {
    Keyboard.println("B8 release");
  }
  if (button9.risingEdge()) {
    Keyboard.println("B9 release");
  }
 if (button10.risingEdge()) {
    Keyboard.println("B8 release");
  }
 #endif
 }

