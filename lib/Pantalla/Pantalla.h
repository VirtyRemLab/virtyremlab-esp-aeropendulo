#ifndef PANTALLA_H
#define PANTALLA_H


#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SPI.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Reset no está conectado
#define SCREEN_ADDRESS 0x3C  // Dirección I2C común para esta pantalla
extern Adafruit_SSD1306 display;

// Función para inicializar la pantalla
void initOLED(uint8_t textSize);
// Borrar pantalla
void OLED_clear();
// Pantalla espera a la conexión
void OLED_waiting_conn();

// Pantalla principal
void OLED_main_info(double freq, unsigned long Tm, uint32_t IP);
// Pantalla desconectado
void OLED_desconnect();

#endif