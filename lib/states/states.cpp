#include "states.h"

enum STATES SYSTEM_STATE = STANDBY;
enum EVENTS SYSTEM_EVENTS = NONE;
enum CTRL_MODES SYSTEM_CRTL_MODE=TEST_MODE;

char *state2string(enum STATES state){
    switch (state)
    {
    case STANDBY: 
        return "STANDBY";
    case READY:
        return "READY";    
    case TEST:
        return "TEST";
    case PID:      
        return "PID";
    case ALARM:
        return "ALARM";

    default:
        break;
    }
}

void event_dispatcher(enum STATES* state, enum EVENTS* event, enum CTRL_MODES* ctrl_mode ){

    Serial.println("Evento");
    switch (*state)
    {

    case STANDBY:
        if(*event==POWERON){
            *state = READY;
        }
        if(*event==FAULT){
            *state = ALARM;
        }

        break;


    case READY:
        if(*event==POWEROFF){
            *state = STANDBY;
        }
        
        if(*event==START && *ctrl_mode==PID_MODE){
            *state = PID;
        }
        if(*event==START && *ctrl_mode==TEST_MODE){
            *state = TEST;
        }
        if(*event==FAULT){
            *state = ALARM;
        }

        break;

    case TEST:
        if(*event==STOP){
            *state = READY;
        }
        if(*event==POWEROFF){
            *state = STANDBY;
        }

        if(*event==FAULT){
            *state = ALARM;
        }

        break;


        case PID:
        if(*event==STOP){
            *state = READY;
        }

        if(*event==POWEROFF){
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