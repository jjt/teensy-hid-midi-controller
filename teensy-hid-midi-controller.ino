#include <Bounce.h>

const int channel = 1;
const int vel = 99;
const int num_btns = 23; // One more than we need because pin 6 is nixed
const int root_note = 48; // C3
const int bounce_rate = 5;

// Controller pin layout as of Oct 5th, 2012
//  
//  3   6   9   4  13  17  20
//  2   7   10  5  14  18  21 
//  1   8   11  0  15  19  22
//          12     16
//


// This will be the note order from root_note to root_note + 22
// Could make a vector of pointers, but things went weird on me 
// when I tried that, so here we are
Bounce buttons[] = {
  Bounce(0,bounce_rate),
  Bounce(1,bounce_rate),
  Bounce(2,bounce_rate),
  Bounce(3,bounce_rate),
  Bounce(4,bounce_rate),
  Bounce(5,bounce_rate),
  Bounce(7,bounce_rate), // Teensy's pin 6 is weird because it's the LED
  Bounce(8,bounce_rate),
  Bounce(9,bounce_rate),
  Bounce(10,bounce_rate),
  Bounce(11,bounce_rate),
  Bounce(12,bounce_rate),
  Bounce(13,bounce_rate),
  Bounce(14,bounce_rate),
  Bounce(15,bounce_rate),
  Bounce(16,bounce_rate),
  Bounce(17,bounce_rate),
  Bounce(18,bounce_rate),
  Bounce(19,bounce_rate),
  Bounce(20,bounce_rate),
  Bounce(21,bounce_rate),
  Bounce(22,bounce_rate),
  Bounce(23,bounce_rate)
};

// Pinouts don't match the notes we want so translate them
// Based on array index, not the pin numbers (jumps at 6)
int button_trans[num_btns] = {5,2,9,16,19,12,17,10,3,18,11,4,0,20,13,6,1,21,14,7,22,15,8};

void setup() {
  for(int i = 0; i < num_btns + 1; i++) {
    if(i==6) {
      continue;
    }
    pinMode(i, INPUT_PULLUP);
  }
}

void loop() {
  for(int i = 0; i < num_btns; i++) {
    buttons[i].update();
    if (buttons[i].fallingEdge()) {
      usbMIDI.sendNoteOn(root_note + button_trans[i], vel, channel);
    }
    
    if (buttons[i].risingEdge()) {
       usbMIDI.sendNoteOff(root_note + button_trans[i], vel, channel); 
    }
  }
}

