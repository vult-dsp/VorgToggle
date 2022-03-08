/*

Author: Leonardo Laguna Ruiz 2018

This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.
https://creativecommons.org/licenses/by-sa/4.0/

*/

#include <Bounce2.h>
#include <EEPROMWearLevel.h>

Bounce debouncer = Bounce();

const int LP = 4;
const int HP = 0;
const int BUTTON = 3;

int state = LOW;

#define EEPROM_LAYOUT_VERSION 0
#define AMOUNT_OF_INDEXES 1

void setup() {
  pinMode(LP, OUTPUT);
  pinMode(HP, OUTPUT);
  pinMode(BUTTON, INPUT);

  debouncer.attach(BUTTON);
  debouncer.interval(5);

  EEPROMwl.begin(EEPROM_LAYOUT_VERSION, AMOUNT_OF_INDEXES);

  state = EEPROMwl.read(0);

  digitalWrite(LP, state);
  digitalWrite(HP, !state);
}

void loop() {
  debouncer.update();

  if (debouncer.rose()) {
    state = !state;
    digitalWrite(LP, state);
    digitalWrite(HP, !state);
    EEPROMwl.update(0, state);
  }
}
