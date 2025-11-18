#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include <config.h>
#include <Pantalla.h>
#include <tareas.h>
#include <states.h>
#include <ESP32Servo.h>
#include <ESC.h>
#include <math.h>

extern float volatile _yk,_r_vel_man,_M1,_M2,Amp,Freq;

extern float volatile _uk[4],_ik[4],_dk,_pk, _ek[4], _yk,_Tm ; 
extern float volatile _Kp, _Ki , _Kd, _Ref,_vM1_ms,_vM2_ms;

extern bool volatile  _motors_power;

void initHardwareControl();
void tareaControl(void *parameters);
float lecturaPosicionAngular(adc1_channel_t adc_channel);



#endif