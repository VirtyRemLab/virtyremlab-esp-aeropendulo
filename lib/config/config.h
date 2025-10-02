#ifndef CONFIG_H
#define CONFIG_H
/// CONSTANTES DE CONFIGURACIÓN DEL PROYECTO


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

extern double freq ;
extern unsigned long Tm ;
extern double t ;
extern double y ;
        


#endif