#include "control.h"

float volatile _yk = 0, _r_vel_man=0;
bool volatile  _motors_power=false;

// Variables motores
ESC _esc_M1 (MOTOR1_ESC_PIN, 1000, 2000, MOTORS_ARM_SPEED); 
ESC _esc_M2 (MOTOR2_ESC_PIN, 1000, 2000, MOTORS_ARM_SPEED); 

float lecturaPosicionAngular(adc1_channel_t adc_channel){


  float m;
  int sum = 0;
  for (int i = 0; i < N_SAMPLES_CONVER; i++)
    sum = sum + adc1_get_raw(adc_channel);
  float lecturaPot_int = (float) sum / N_SAMPLES_CONVER ;
  m = (float)(MAX_POS_GRADOS - MIN_POS_GRADOS) / (MAX_POT_BIT - MIN_POT_BIT);
  return m * (lecturaPot_int - MIN_POT_BIT) + MIN_POS_GRADOS;



}


void initHardwareControl(){
  pinMode(MOTORS_POWER_PIN, OUTPUT);

  // motores
  pinMode(MOTOR1_ESC_PIN, OUTPUT);
  pinMode(MOTOR2_ESC_PIN, OUTPUT);
}

void tareaControl(void* parameters){
  
    for (;;)
    {
      // Espera hasta que la ISR libere el semáforo
      xSemaphoreTake(xBinarySemaphoreControl, portMAX_DELAY);
      


      switch (SYSTEM_STATE)
      {
        // Modo en espera 
        case  STANDBY:
          _motors_power = false;
          break;

        // Modo ready con los motores activos  
        case READY:
          
          // armado de los motores
          if(! _motors_power){
            _motors_power = true;
            _esc_M1.arm(); 
            _esc_M2.arm();
            delay(100);
            digitalWrite(MOTORS_POWER_PIN, _motors_power);
            delay(500);
            _esc_M1.speed(MOTORS_MIN_SPEED-200); 
            _esc_M2.speed(MOTORS_MIN_SPEED-200);             
          }

          _yk = lecturaPosicionAngular(PIN_POT);
          

          break;
        
        // Modo manual en cadena abierta. El usuario puede indicar la velocidad de los motores
        // La variable de la velocidad de los motores será _r_vel_man
        case TEST:
        
          break;

        // Modo control en cadena cerrada mediante PID. El usuario puede cambiar las ganancias del regulador
        case PID:

          break;
        
        default:
          break;
      }
      
      digitalWrite(MOTORS_POWER_PIN, _motors_power);







      t++;

      // Release data transmission thread
      if (((unsigned long)t)%SAMPLE_PERIOD_COM_MS==0){
        xSemaphoreGive(xBinarySemaphoreTransmision);
        t = 0;
      }
    }
  }