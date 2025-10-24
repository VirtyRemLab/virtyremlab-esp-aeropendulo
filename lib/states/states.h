#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
enum STATES {
  STANDBY,
  STARTING,
  READY,
  TEST,
  PID,
  ALARM
};

enum EVENTS {
  NONE,
  POWERON,
  POWEROFF,
  START_PID,
  START_TEST,
  STOP,
  RESET,
  FAULT
};

void  event_dispatcher(enum STATES* state, enum EVENTS* event);
char *state2string(enum STATES state);
// Creamos declaramos el estado y evento del sistema
extern enum STATES SYSTEM_STATE;
extern enum EVENTS SYSTEM_EVENTS;

#endif
