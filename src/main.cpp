// ***********************************************
// Bibliotecas
// ***********************************************
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>


// ***********************************************
// Archivos *.hpp - Fragmentar el código
// ***********************************************
#include "settings.hpp"
#include "functions.hpp"
#include "settingsReset.hpp"
#include "settingsRead.hpp"
#include "settingsSave.hpp"
#include "esp32_wifi.hpp"

// ***********************************************
// Coloca la declaración de funciones aquí:
// ***********************************************


// ***********************************************
// Setup
// ***********************************************
void setup() {
    // Baudrate
    Serial.begin(115200);  

    // Asignación de frecuencia al ESP32
    setCpuFrequencyMhz(240);    

    // Inicio del log por serial
    log("\nInfo: Iniciando Setup");

    // Configuración de los pines
    settingPines();

    // Inicializar SPIFFS
   /* if (!SPIFFS.begin()) {
        log(F("Error: Falló la inicialización del SPIFFS"));
        while (true);
    }*/

    // Leer la configuración de WiFi
    settingsReadWiFi();

    // Configuracion WiFi
    WiFi.disconnect(true);
    delay(1000);

    // Setup del WiFi
    wifi_setup();


}


// ***********************************************
// Loop principal núcleo 0
// ***********************************************
void loop() {

    yield();
    // ***********************************************
    // WiFi
    // ***********************************************
    if (wifi_mode == WIFI_STA){
        wifiLoop();
    }

    if (wifi_mode == WIFI_AP){
        wifiAPLoop();
    }

}
