#include "states.h"

enum STATES SYSTEM_STATE = STANDBY;
enum EVENTS SYSTEM_EVENTS = NONE;

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

void event_dispatcher(enum STATES* state, enum EVENTS* event){

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
        
        if(*event==START_PID){
            *state = PID;
        }
        if(*event==START_TEST){
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