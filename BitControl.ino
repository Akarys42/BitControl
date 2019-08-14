// By Matteo Bertucci (https://github.com/Akarys42)
// Under MIT licence

#include "Joystick.h"

Joystick_ Joystick[1] = {
  Joystick_(0x03, JOYSTICK_TYPE_JOYSTICK, 27, 0, true, true, false, false, false, false, false, false, false, false, false)
};

//////////////////////////////////////////
int pin = 3;
const int line = 6;
const int column = 4;
const int joystick = 3;
const int deadzone = 20;
const int joystickButton[3] = {24, 25, 26};
const int d  = 50;
//////////////////////////////////////////

const int deadzoneMin = 512 - deadzone;
const int deadzoneMax = 512 + deadzone;
int linePin[line];
int columnPin[column];
int pinJoystick = 0;
int x;
int y;
bool lastState[joystick];

void setup() {
  for (int l = 0; l < line; l++) {
    pinMode(pin, OUTPUT);
    linePin[l] = pin;
    pin++;
  }

  for (int c = 0; c < column; c++) {
    pinMode(pin, INPUT);
    columnPin[c] = pin;
    pin++;
  }

  Joystick[0].begin(true);
}

void loop() {
  for (int k = 0; k < line; k++) {
    digitalWrite(linePin[k], HIGH);
    for (int v = 0; v < column; v++) {
      if (digitalRead(columnPin[v]) == HIGH) {
        Joystick[0].pressButton(getButtonId(k, v));
      }
      else {
        Joystick[0].releaseButton(getButtonId(k, v));
      }
    }
    digitalWrite(linePin[k], LOW);
  }

  Joystick[0].sendState();

  for (int c = 0; c < joystick; c++) {
    x = analogRead(pinJoystick) * -1 + 1024;
    pinJoystick++;
    y = analogRead(pinJoystick);
    pinJoystick++;
    if (isInDeadzone(x) == false || isInDeadzone(y) == false) {
      Joystick[0].pressButton(joystickButton[c]);
      delay(d);
      Joystick[0].sendState();
      Joystick[0].setXAxis(x);
      Joystick[0].setYAxis(y);
      Joystick[0].sendState();
      lastState[c] = true;
    }
    else {
      if (lastState[c] == true) {
        Joystick[0].setXAxis(512);
        Joystick[0].setYAxis(512);
        Joystick[0].sendState();
        delay(d);
        Joystick[0].releaseButton(joystickButton[c]);
        Joystick[0].sendState();
      }
      lastState[c] = false;
    }
  }
  pinJoystick = 0;
}

int getButtonId(int k, int v) {
  int buttonId;
  buttonId = v * line;
  buttonId = buttonId + k;
  return buttonId;
}

bool isInDeadzone(int pwr) {
  if (pwr > deadzoneMin && pwr < deadzoneMax) {
    return true;
  }
  else {
    return false;
  }
}
