
#include "tareas.h"

// SEMÁFOROS
// Semáforo binario para sincronizar la interrupción por timer y la tarea de control.
SemaphoreHandle_t xBinarySemaphoreControl;
SemaphoreHandle_t xBinarySemaphoreTransmision;

// Handle para un hardware timer 
hw_timer_t * timer = NULL;



void semaphoresInit(){
    // Creamos los semáforos para la sincronización de los diferentes hilos
    xBinarySemaphoreControl = xSemaphoreCreateBinary();
    xBinarySemaphoreTransmision = xSemaphoreCreateBinary();
}

void timersInit(){
    timer = timerBegin(1, 80, true); // Iniciamos el reloj con un pre-scaler de 80 --> F_conteo= 1Mz (el reloj es de 80MHz)
    timerAttachInterrupt(timer, &onTimer_1us, true);  // Indicamos la ISR
    timerAlarmWrite(timer, SAMPLES_IN_MS, true);     // Configuramos el desbordamiento 
    timerAlarmEnable(timer);   
  
}

void tasksInit(TaskFunction_t tareaControl, TaskFunction_t tareaTransmision){
      // Creamos la tarea de control
  xTaskCreatePinnedToCore(
    tareaControl,           /* Task function. */
    "tareaControl",        /* name of task. */
    8192,                    /* Stack size of task */
    NULL,                     /* parameter of the task */
    6,                        /* priority of the task */
    NULL,
    1); 



    // PARA QUE NO INTERRUPA LA EJECUCIÓN DE LA RUTINA DE CONTROL HAY QUE TENER EN CUENTA QUE EL LOOP SE EJECUTA EN NÚCLEO 0, PARA ELLO DEJAR EL CONTROL EN EL NÚCLEO 1
    xTaskCreatePinnedToCore(
    tareaTransmision,           /* Task function. */
    "tareaTransmision",        /* name of task. */
    10000,                    /* Stack size of task */
    NULL,                     /* parameter of the task */
    2,                        /* priority of the task */
    NULL,
    0); 

}



// Función para la rutina de interrupción por desbordamiento de timer
void IRAM_ATTR onTimer_1us(){
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR( xBinarySemaphoreControl, &xHigherPriorityTaskWoken);
}

