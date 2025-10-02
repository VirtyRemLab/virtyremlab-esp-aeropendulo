#ifndef TAREAS_H
#define TAREAS_H

#include <Arduino.h>
#include <config.h>


extern SemaphoreHandle_t xBinarySemaphoreControl;
extern SemaphoreHandle_t xBinarySemaphoreTransmision;

void IRAM_ATTR onTimer_1us();
void semaphoresInit();
void timersInit();
void tasksInit(TaskFunction_t tareaControl, TaskFunction_t tareaTransmision);
#endif