#ifndef STATES_H
#define STATES_H

enum STATES {
  STANDBY,
  TEST,
  PID,
  ALARM
};

enum EVENTS {
  NONE,
  RUN_PID,
  RUN_TEST,
  STOP,
  RESET,
  FAULT
};

void event_dispatcher(enum STATES state, enum EVENTS event);

// Creamos declaramos el estado y evento del sistema
extern enum STATES SYSTEM_STATE;
extern enum EVENTS SYSTEM_EVENTS;

#endif
