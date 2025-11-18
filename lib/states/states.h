#ifndef STATES_H
#define STATES_H

#include <Arduino.h>
enum STATES {
  STANDBY,
  STARTING,
  READY,
  PID,
  TEST,
  ALARM
};

enum EVENTS {
  NONE,
  POWERON,
  POWEROFF,
  START,
  STOP,
  RESET,
  FAULT
};

enum CTRL_MODES
{
  TEST_MODE,
  PID_MODE
};

void  event_dispatcher(enum STATES* state, enum EVENTS* event,enum CTRL_MODES* ctrl_mode);
char *state2string(enum STATES state);
// Creamos declaramos el estado y evento del sistema
extern enum STATES SYSTEM_STATE;
extern enum EVENTS SYSTEM_EVENTS;
extern enum CTRL_MODES SYSTEM_CRTL_MODE;

#endif
