#include "control.h"

float volatile _yk = 0;

float lecturaPosicionAngular(adc1_channel_t adc_channel){


  float m;
  int sum = 0;
  for (int i = 0; i < N_SAMPLES_CONVER; i++)
    sum = sum + adc1_get_raw(adc_channel);
  float lecturaPot_int = (float) sum / N_SAMPLES_CONVER ;
  m = (float)(MAX_POS_GRADOS - MIN_POS_GRADOS) / (MAX_POT_BIT - MIN_POT_BIT);
  return m * (lecturaPot_int - MIN_POT_BIT) + MIN_POS_GRADOS;



}

void tareaControl(void* parameters){
  
    for (;;)
    {
      // Espera hasta que la ISR libere el semáforo
      xSemaphoreTake(xBinarySemaphoreControl, portMAX_DELAY);
      


      switch (SYSTEM_STATE)
      {
        case PID:
          _yk = lecturaPosicionAngular(PIN_POT);
          break;
        
        default:
          break;
      }



      // Simulación
      y = sin(2.*PI*freq*t/SAMPLES_IN_S);  // Simula valor entre 0.0 y 1
      t++;
    
      // Release data transmission thread
      if (((unsigned long)t)%SAMPLE_PERIOD_COM_MS==0){
        xSemaphoreGive(xBinarySemaphoreTransmision);
      }
    
  
    }
  }