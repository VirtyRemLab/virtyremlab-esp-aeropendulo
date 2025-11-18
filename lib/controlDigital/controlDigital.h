#ifndef CONTROL_H_
#define CONTROL_H_

//macros para observar que constante cambiamos
#define KP_ACTIVA 0
#define KI_ACTIVA 1
#define KD_ACTIVA 2

#define PIN_AD1 35
#define PIN_AD2 34

#define KP_INICIAL 1
#define KI_INICIAL  0
#define KD_INICIAL 0 
#define Ts 1e-3 

#include "regStruct.h"


extern RZ volatile _Reg;

void VaciarTabla(volatile float *tabla, int n);
void desplazartabla(volatile float tabla[], int n);
float productoescalar(const float volatile v1[], const float volatile v2[], int n);

float ConversorAD(int pin);
float Clip(float Val, float max, float min);

#endif