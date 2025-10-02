////////////////////////////////////////////////////////////////////////////////////
// EQUIPOS REMOTOS BASADOS EN ESP 32
// Programa base para el desarrollo de equipos de prácticas remotos. Este ejemplo integra los elementos software 
// necesarios para implementar las siguientes funcionalidades:
//      - Periodo de muestreo determinista
//      - Comunicaciones en tiempo real (websockets)
//      - Máquina de estados para gestionar los modos de funcionamiento del dispositivo.


#include <Arduino.h>
#include <Pantalla.h>
#include <comms.h>
#include <WebSocketsClient.h>
#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#include <tareas.h>
#include <control.h>




void setup()
{

  // INICIALIZACIONES

  // ------------------------------------------------------------
  // Puerto serie  
  Serial.begin(115200);
  // ------------------------------------------------------------
  // Semáforos
  semaphoresInit();

  // ------------------------------------------------------------  
  // Configuración de la interrupción por timner
  timersInit();

  // ------------------------------------------------------------
  //  Pantalla OLED
  initOLED(1);
  // ------------------------------------------------------------
  //  WIFI
  WIFIInit();
  // ------------------------------------------------------------
  //  Websocket client
  webSocketInit();
  // ------------------------------------------------------------
  // TAREAS
  tasksInit(tareaControl,tareaTransmision);
}

void loop() {

  webSocketLoop();

  if (WiFi.status() != WL_CONNECTED){
    OLED_desconnect();
  }
  else{
    OLED_main_info(freq,Tm,WiFi.localIP());
    
  }

}
