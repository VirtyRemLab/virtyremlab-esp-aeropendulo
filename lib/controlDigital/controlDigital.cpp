#include "controlDigital.h"
#include<malloc.h>
#include<Arduino.h>

void VaciarTabla(volatile float *tabla, int n)
{
    for (int i = 0; i < n;i++)
        tabla[i] = 0;
}


void desplazartabla(volatile float tabla[], int n){
    int i;
    for( i = n - 1 ; i > 0 ; i = i - 1){
        tabla[i] = tabla [i - 1];
    }
}

float productoescalar(const float volatile v1[], const float volatile v2[], int n){
    int i;
    float productoescalar = 0;
    for(i = 0; i < n; i ++){
        productoescalar += v1[i] * v2[i];
    }
    return productoescalar;
}

float ConversorAD(int pin){
  int conv, conv_calibrada;
  float tension;
  conv = analogRead(pin);
  conv_calibrada = lround((0.9656 * conv) + 224.2290);
  tension = conv_calibrada * (33.0 / 4095.0) - 15;
  return tension;
}


float Clip(float Val, float _max, float _min){

  return max(_min, min(Val, _max));
}