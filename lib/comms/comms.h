#ifndef COMMS_H
#define COMMS_H

#include <Arduino.h>
#include <WebSocketsClient.h>
#include "cJSON.h"
#include <config.h>
#include <WiFi.h>  
#include <Pantalla.h>  
#include <tareas.h>

#define WEBSOCKET_DATA_LENGH 2


extern String mensaje;
extern u_int8_t *dataBloc;
extern float auxCom ;
extern float data[WEBSOCKET_DATA_LENGH];



//////////////////////////////////////////////////////////// 
// CONEXIÓN WIFI
////////////////////////////////////////////////////////////

void WIFIInit();

//////////////////////////////////////////////////////////// 
// COMUNICACIONES WEBSOCKETS
////////////////////////////////////////////////////////////


// BORRAR
//extern WebSocketsClient webSocket;

// Se emplea la librería arduinoWebsockets:
// https://github.com/Links2004/arduinoWebSockets?utm_source=platformio&utm_medium=piohome

void webSocketInit();

// Callback para la gestión de los mensajes entrantes
void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

// Función para enviar los datos
void webSocketSendMainDataBinary(float *data, u_int8_t length);
void webSocketLoop();

void tareaTransmision(void *parameters);
#endif