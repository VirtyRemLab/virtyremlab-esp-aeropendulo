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
       
        cJSON *freq_item = cJSON_GetObjectItem(root, "freq");
        cJSON *tm_item = cJSON_GetObjectItem(root, "tm");
      
      
        if (cJSON_IsString(freq_item) && (freq_item->valuestring != NULL)) {
          printf("freq: %f\n", atof(freq_item->valuestring) );
          freq = atof(freq_item->valuestring);
        }
  
        if (cJSON_IsString(tm_item) && (tm_item->valuestring != NULL)) {
          printf("Tm: %f\n", atof(tm_item->valuestring) );
          Tm = (unsigned long) atof(tm_item->valuestring);
        }
      
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

void tareaTransmision(void* parameters){
  for (;;){
    xSemaphoreTake(xBinarySemaphoreTransmision, portMAX_DELAY);
    mensaje = String(y,2);
    data[0] = (float)y;
    webSocketSendMainDataBinary(data, WEBSOCKET_DATA_LENGH);
    Serial.println("Enviado: " + mensaje + mensaje + mensaje + mensaje + mensaje + mensaje + mensaje);
    }
}