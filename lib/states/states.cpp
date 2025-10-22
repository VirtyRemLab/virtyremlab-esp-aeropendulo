#include "states.h"

enum STATES SYSTEM_STATE = PID;
enum EVENTS SYSTEM_EVENTS = NONE;



void event_dispatcher(enum STATES* state, enum EVENTS* event){


    switch (SYSTEM_STATE)
    {

    case STANDBY:
        if(*event==RUN_PID){
            *state = PID;
        }
        if(*event==RUN_TEST){
            *state = TEST;
        }
        if(*event==FAULT){
            *state = ALARM;
        }

        break;

    case TEST:
        if(*event==STOP){
            *state = STANDBY;
        }

        if(*event==FAULT){
            *state = ALARM;
        }

        break;


        case PID:
        if(*event==STOP){
            *state = STANDBY;
        }

        if(*event==FAULT){
            *state = ALARM;
        }

        break;

    case ALARM:
        if(*event==RESET){
            *state = STANDBY;
        }

        break;


        default:
        break;
        }
        *event = NONE;
}