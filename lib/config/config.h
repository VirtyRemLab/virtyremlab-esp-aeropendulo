#ifndef CONFIG_H
#define CONFIG_H
/// CONSTANTES DE CONFIGURACIÓN DEL PROYECTO

#include <esp_adc_cal.h>

// TIMERS
#define SAMPLES_IN_S 1000.
#define SAMPLES_IN_MS 1000
#define SAMPLE_PERIOD_COM_MS 100


// Dirección y puerto del servidor alojado en el backend del servicio
//const char* websocket_server = "192.168.0.253";  
//#define WEBSOCKET_SERVER "192.168.1.128" 
#define WEBSOCKET_SERVER "156.35.152.161" 
#define WEBSOCKET_PORT  8765    
#define WS_RECONNECT_S 5000

//SSID y Credenciales 
#define SSID  "Uniovi-i40"     
#define PASSWORD  "1000000001" 

// #define SSID  "--"     
// #define PASSWORD  "DBggArg_40_4B"


// VARIABLES Y CONFIGURACIÓN DEL CONTROL

// pin al que se conecta el potenciómetro
#define PIN_POT  ADC1_CHANNEL_4 

// Variables de escala para la 
#define MIN_POT_BIT 535
#define MAX_POT_BIT 2055
#define N_SAMPLES_CONVER 5

#define MIN_POS_GRADOS -90
#define MAX_POS_GRADOS 0
#define PIN_POT  ADC1_CHANNEL_4

// Pines del motor
#define MOTOR1_ESC_PIN 13 //
#define MOTOR2_ESC_PIN 12 //
#define MOTORS_POWER_PIN 25 //
// Valores de calibración de los ESC configurados con el sofware BLHeliSuite (windows + arduino UNO) 
#define MOTORS_MIN_SPEED 1012 
#define MOTORS_MAX_SPEED 1996
#define MOTORS_MIN_SPEED_CTRL 1200 
#define MOTORS_MAX_SPEED_CTRL 1600
#define SPEED_CTRL 1400
#define MOTORS_ARM_SPEED 500 



// Valores del lazo de control
extern double freq ;
extern unsigned long Tm ;
extern double k ;
extern double y ;
        


#endif