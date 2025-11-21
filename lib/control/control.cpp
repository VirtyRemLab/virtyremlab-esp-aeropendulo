#include "control.h"

float volatile  _r_vel_man=0,_M1=0,_M2=0,Amp=15,Freq=1/15.0;
bool volatile  _motors_power=false;

float volatile _uk[4],_ik[4],_dk,_pk, _ek[4], _yk=0,_Tm=0.001 ; 
float volatile _Kp=7, _Ki=0 , _Kd=0, _Ref,_vM1_ms=1400,_vM2_ms=1400;
int _v_ref_ms = 1400;
float r_sin = 0;
float r_square = 0;
double t=0.0;

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
      
      desplazartabla(_ik, 4);
      desplazartabla(_ek, 4);
      desplazartabla(_uk, 4);
      _yk = lecturaPosicionAngular(PIN_POT);
      _ek[0] = _Ref - _yk;
    
      switch (SYSTEM_STATE)
      {
        // Modo en espera 
        case  STANDBY:
          _motors_power = false;
          _r_vel_man = 0;
          _M1 = MOTORS_MIN_SPEED-200;
          _M2 = MOTORS_MIN_SPEED-200;
          _uk[0] = 0;
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

          _M1 = MOTORS_MIN_SPEED-200;
          _M2 = MOTORS_MIN_SPEED-200;
          _uk[0] = 0;

          break;
        
        // Modo manual en cadena abierta. El usuario puede indicar la velocidad de los motores
        // La variable de la velocidad de los motores será _r_vel_man
        case TEST:
          _M1 = MOTORS_MIN_SPEED + _r_vel_man;
          _M2 = MOTORS_MIN_SPEED - _r_vel_man;
                   
        
          break;

        // Modo control en cadena cerrada mediante PID. El usuario puede cambiar las ganancias del regulador
        case PID:
          // Calculo de la entrada
          r_sin = Amp * (float) sin(2. * M_PI * Freq * t );
          r_square = Amp * (float)(r_sin > 0.0);
          _Ref = r_square;
          // Acción Proporcional
          _pk = _ek[0] * _Kp;
          // Acción integral
          _ik[0] = 0.5*_Kp * _Ki *_Tm * (_ek[0] + _ek[1]) + _ik[1];

          // anti-Windup (pendiente)
          _ik[0] = Clip(_ik[0], 300, -300); // Limitada a mano de momento

          // Acción diferencial
          _dk = (_Kp * _Kd / _Tm) * (_ek[0] - _ek[1]);

          _uk[0] = _pk + _ik[0] + _dk;

          // Escritura de la acción de control en los motores
          _vM1_ms = _v_ref_ms + _uk[0];
          _vM1_ms = Clip(_vM1_ms,MOTORS_MAX_SPEED_CTRL,MOTORS_MIN_SPEED_CTRL);
          
          _vM2_ms = _v_ref_ms - _uk[0];
          _vM2_ms = Clip(_vM2_ms,MOTORS_MAX_SPEED_CTRL,MOTORS_MIN_SPEED_CTRL);
          _M1 = _vM1_ms;
          _M2 = _vM2_ms;
          break;

        default:
          break;
      }
      
      
      digitalWrite(MOTORS_POWER_PIN, _motors_power);

      if(_motors_power){
      _esc_M1.speed(_M1);
      _esc_M2.speed(_M2);     
      }






      k++;
      t += _Tm;
      // Release data transmission thread
      if (((unsigned long)k)%SAMPLE_PERIOD_COM_MS==0){
        xSemaphoreGive(xBinarySemaphoreTransmision);
        k = 0;
      }
    }
  }