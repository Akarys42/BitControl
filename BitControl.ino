// By Matteo Bertucci (https://github.com/Akarys42)
// Under MIT licence

#include "Joystick.h"

Joystick_ Joystick[3] = {
  Joystick_(0x03, JOYSTICK_TYPE_JOYSTICK, 24, 0, true, true, false, false, false, false, false, false, false, false, false),
  Joystick_(0x04, JOYSTICK_TYPE_JOYSTICK, 0, 0, true, true, false, false, false, false, false, false, false, false, false),
  Joystick_(0x05, JOYSTICK_TYPE_JOYSTICK, 0, 0, true, true, false, false, false, false, false, false, false, false, false)
};

//////////////
int pin = 3;
const int line = 6;
const int column = 4;
const int joystick = 3;
//////////////

int linePin[line];
int columnPin[column];
int pinJoystick = 0;

void setup() {
  for(int l = 0; l < line; l++) {
    pinMode(pin, OUTPUT);
    linePin[l] = pin;
    pin++;
  }

  for(int c = 0; c < column; c++) {
    pinMode(pin, INPUT);
    columnPin[c] = pin;
    pin++;
  }

  for(int j = 0; j < joystick; j++) {
    Joystick[j].begin();
  }
}

void loop() {
  for(int k = 0; k < line; k++) {
    digitalWrite(linePin[k], HIGH);
    for(int v = 0; v < column; v++) {
      if(digitalRead(columnPin[v]) == HIGH) {
        Joystick[0].pressButton(getButtonId(k, v));
      }
      else {
        Joystick[0].releaseButton(getButtonId(k, v));
      }
    }
    digitalWrite(linePin[k], LOW);
  }

  for(int c = 0; c < joystick; c++) {
    Joystick[c].setXAxis(analogRead(pinJoystick) * -1 + 1024 );
    pinJoystick++;
    Joystick[c].setYAxis(analogRead(pinJoystick));
    pinJoystick++;
  }
  pinJoystick = 0;
}

int getButtonId(int k, int v) {
  int buttonId;
  buttonId = v * line;
  buttonId = buttonId + k;
  return buttonId;
}
