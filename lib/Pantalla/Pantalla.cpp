
#include "Pantalla.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, RST_OLED);

void initOLED(uint8_t textSize)
{
    Wire.begin(SDA_OLED, SCL_OLED); 
    // Inicializa la pantalla
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        
        for (;;);  // Detenerse si falla
  }
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);             // Tamaño de texto
  display.setTextColor(SSD1306_WHITE);  // Color
  display.println("Ready");
  display.display();
}


void OLED_clear(){

  display.clearDisplay();
  display.setCursor(0, 0); 
}

void OLED_waiting_conn(){
  OLED_clear();
  display.print("Conectando \n");
  display.display();
}

void OLED_main_info(double freq, unsigned long Tm, uint32_t IP){
  OLED_clear();
  display.print("WIFI \n");
  display.print("IP:");
  display.println(IP);
  display.print("WEBSOCKET CONNECTION \n");
  display.print("Tm: " + String(Tm) + "\n");
  display.print("Freq: " + String(freq) + "\n");
  display.display();
}

void OLED_desconnect(){
  OLED_clear();
  display.print("Desconectado! \n");
  display.display();
}