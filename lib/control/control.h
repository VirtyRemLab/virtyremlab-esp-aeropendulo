#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include <config.h>
#include <Pantalla.h>
#include <tareas.h>
#include <states.h>
#include <ESP32Servo.h>
#include <ESC.h>

extern float volatile _yk,_r_vel_man;
extern bool volatile  _motors_power;

void initHardwareControl();
void tareaControl(void *parameters);
float lecturaPosicionAngular(adc1_channel_t adc_channel);



#endif