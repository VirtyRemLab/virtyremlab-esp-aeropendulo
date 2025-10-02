#include "control.h"

void tareaControl(void* parameters){
  
    for (;;)
    {
      // Espera hasta que la ISR libere el semáforo
      xSemaphoreTake(xBinarySemaphoreControl, portMAX_DELAY);
      
      // Simulación
      y = sin(2.*PI*freq*t/SAMPLES_IN_S);  // Simula valor entre 0.0 y 1
      t++;
    
      // Release data transmission thread
      if (((unsigned long)t)%SAMPLE_PERIOD_COM_MS==0){
        xSemaphoreGive(xBinarySemaphoreTransmision);
      }
    
  
    }
  }