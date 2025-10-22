#ifndef CONTROL_H
#define CONTROL_H

#include <Arduino.h>
#include <config.h>
#include <Pantalla.h>
#include <tareas.h>
#include <states.h>

extern float volatile _yk;

void tareaControl(void *parameters);
float lecturaPosicionAngular(adc1_channel_t adc_channel);



#endif