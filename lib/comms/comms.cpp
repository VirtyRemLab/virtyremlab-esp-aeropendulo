#include "comms.h"

// PARÁMETROS DE LAS COMUNICACIONES
// String para el envio de mensajes en websockets
String mensaje;
u_int8_t *dataBloc;
float auxCom = 0;
float data[WEBSOCKET_DATA_LENGH];


//////////////////////////////////////////////////////////// 
// CONEXIÓN WIFI
////////////////////////////////////////////////////////////

void WIFIInit(){
  Serial.println("Conectando a la red WiFi...");
  // Inicia la conexión WiFi
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_19_5dBm);
  WiFi.setSleep(false);

  WiFi.begin(SSID, PASSWORD);

  // Espera hasta que se conecte
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    OLED_waiting_conn();
    delay(10000);
    Serial.print(".");
  }

  // Mensaje de éxito
  Serial.println("\n¡Conectado!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}


//////////////////////////////////////////////////////////// 
// COMUNICACIONES WEBSOCKETS
////////////////////////////////////////////////////////////


WebSocketsClient webSocket;

void webSocketInit(){
  webSocket.begin(WEBSOCKET_SERVER, WEBSOCKET_PORT, "/");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(WS_RECONNECT_S); // reconectar cada WS_RECONNECT_S s si se cae
}

// Callback para la gestión de los mensajes entrantes
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
      case WStype_DISCONNECTED:
        Serial.println("[WS] Desconectado");
        break;
      case WStype_CONNECTED:
        Serial.println("[WS] Conectado al servidor");
        // Enviar mensaje inicial
        webSocket.sendTXT("Hola desde el ESP32");
         
        break;
      case WStype_TEXT:
        Serial.printf("[WS] Mensaje recibido: %s\n", payload);
        
        // Cambio de frequencia
        cJSON *root = cJSON_Parse((const char *) payload);
       
        cJSON *cmd_event = cJSON_GetObjectItem(root, "event");
        cJSON *cmd_vel_man = cJSON_GetObjectItem(root, "vel_man");
        cJSON *cmd_ctrl_mode = cJSON_GetObjectItem(root, "ctrl_mode");
        //cJSON *tm_item = cJSON_GetObjectItem(root, "tm");
      
        if (cJSON_IsString(cmd_ctrl_mode) && (cmd_ctrl_mode->valuestring != NULL)) {
          switch (atoi(cmd_ctrl_mode->valuestring))
          {
            case TEST_MODE:
              SYSTEM_CRTL_MODE = TEST_MODE;
              break;
            case PID_MODE:
              SYSTEM_CRTL_MODE = PID_MODE;
              break;

            }
        }

        if (cJSON_IsString(cmd_event) && (cmd_event->valuestring != NULL)) {
          switch (atoi(cmd_event->valuestring))
          {
          case POWEROFF:
              SYSTEM_EVENTS = POWEROFF;
              event_dispatcher(&SYSTEM_STATE, &SYSTEM_EVENTS,&SYSTEM_CRTL_MODE);

            break;
          
          case POWERON:
              SYSTEM_EVENTS = POWERON;
              event_dispatcher(&SYSTEM_STATE, &SYSTEM_EVENTS,&SYSTEM_CRTL_MODE);

            break;

          case START:
              SYSTEM_EVENTS = START;
              event_dispatcher(&SYSTEM_STATE, &SYSTEM_EVENTS,&SYSTEM_CRTL_MODE);

            break;

            case STOP:
              SYSTEM_EVENTS = STOP;
              event_dispatcher(&SYSTEM_STATE, &SYSTEM_EVENTS,&SYSTEM_CRTL_MODE);

            break;

                  

            default:
            break;
          }
        }


        if (cJSON_IsString(cmd_vel_man) && (cmd_vel_man->valuestring != NULL)) {
          _r_vel_man =atof(cmd_vel_man->valuestring);
          //event_dispatcher(&SYSTEM_STATE, &SYSTEM_EVENTS);

        }



        // if (cJSON_IsString(tm_item) && (tm_item->valuestring != NULL)) {
        //   printf("Tm: %f\n", atof(tm_item->valuestring) );
        //   Tm = (unsigned long) atof(tm_item->valuestring);
        // }
      
        break;
    }
  }


void webSocketSendMainDataBinary(float *data, u_int8_t length){
    if (webSocket.isConnected()){                    
        webSocket.sendBIN((u_int8_t*)data, length*sizeof(float));
    }
}

void webSocketLoop(){

    // Loop websockets
    webSocket.loop();
}

////////////////////////////////////////////////////////////
// Tarea de trasnmisión
////////////////////////////////////////////////////////////

// De manera cíclica se envia el estado del sistema al servidor WS
// Longitud de los paquetes: 6 floats
// REG 0: Estado del sistema 
// REG 1: yk   R
// REG 2: rk   R
// REG 3: uk   R
// REG 4: ek   R  
// REG 5: M1   R
// REG 6: M2   R
// REG 7: vel_man W
// REG 8: pos_man W
// REG 9: ctrl_mode W
// REG 10: ref_type W
// REG 11: freq  W
// REG 12: amp   W
// REG 13: Kp    W
// REG 14: Ki    W
// REG 15: Kd    W



void tareaTransmision(void* parameters){
  for (;;){
    xSemaphoreTake(xBinarySemaphoreTransmision, portMAX_DELAY);
    mensaje = String(_yk,2);
    data[0] = (float) SYSTEM_STATE;
    data[1] = (float)_yk;
    data[2] = (float)_Ref;
    data[5] = (float)_M1;
    data[6] = (float)_M2;
    data[7] = (float)_r_vel_man;
    data[9] = (float)SYSTEM_CRTL_MODE;
    webSocketSendMainDataBinary(data, WEBSOCKET_DATA_LENGH);
    Serial.print("Enviado:");
    Serial.println(_Ref);
    }
}