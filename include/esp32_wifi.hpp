
#include <WiFi.h>
#include <DNSServer.h>
#include <ESPmDNS.h>

const byte DNSSERVER_PORT = 53;
DNSServer dnsServer;

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

int wifi_mode = WIFI_STA;

unsigned long previousMillisWIFI = 0;
unsigned long intervalWIFI = 30000;

// Hostname for ESPmDNS. Should work at least on windows. Try http://adminesp32.local
const char *esp_hostname = id;

void startAP(){
    log("Info: Inicializando en modo AP");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    WiFi.softAPConfig(apIP,apIP, netMsk);
    WiFi.setHostname(deviceID().c_str());
    WiFi.softAP(ap_nameap, ap_passwordap, ap_canalap, ap_hiddenap, ap_connetap);
    log("Info: WiFi AP" + deviceID() + " - IP " + ipStr(WiFi.softAPIP()));
    dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
    dnsServer.start(DNSSERVER_PORT, "*", apIP);
    wifi_mode = WIFI_AP;
}

// **************************************************************
// Start Client, attempt to connect to WiFi network
// **************************************************************
void startCient(){
    if (wifi_staticIP) {
        if (!WiFi.config(CharToIP(wifi_ip_static), CharToIP(wifi_gateway), CharToIP(wifi_subnet), CharToIP(wifi_primaryDNS), CharToIP(wifi_secondaryDNS))){
            log("Error: Falló al conectar el modo estación");
        }
    }

    WiFi.hostname(deviceID());
    WiFi.begin(wifi_ssid, wifi_password);
    log("Info: Conectando WiFi " + String(wifi_ssid));
    delay(50);
    byte b=0;

    while(WiFi.status() != WL_CONNECTED && b < 60){
        b++;
        log("Warning: Intentando conexión WiFi...");
        delay(500);
        // Para parpadear LED WiFi cuando está conectándose al WiFi no bloqueante
        // Parpadeo simple del LED cada 100 ms
        blinkSingle(100, WIFILED);
        delay(100);
    }

    if (WiFi.status() == WL_CONNECTED){
        // WiFi Station conectado
        log("Info: WiFi conectado ( " + String(WiFi.RSSI()) + " ) IP " + ipStr(WiFi.localIP()));
        // Parpadeo ramdon del LED
        blinkRandomSingle(10, 100, WIFILED);
        delay(100);
    }else{
        // WiFi Station NO conectado
        log(F("Error: WiFi no conectado"));
        // Parpadeo ramdon del LED
        blinkRandomSingle(10, 100, WIFILED);
        delay(100);
    }

}

// **************************************************************
// Wifi.mode(WIFI_STA)      - Station mode: the ESP32 connects to an access point
// Wifi.mode(WIFI_AP)       - Access point mode: stations can connect to the ESP32
// Wifi.mode(WIFI_AP_STA)   - Access point and a Station connected to another access point
// **************************************************************
void wifi_setup(){
    WiFi.disconnect();

    // 1) Si está activo en modo AP
    if (ap_accessPoint){
        startAP();
        log("Info: WiFi modo AP");
    }

    // 2) Caso contrario en modo Estación (Cliente)
    else {
        WiFi.mode(WIFI_STA);
        wifi_mode = WIFI_STA;
        startCient();
        log("Info: WiFi modo estación");
    }

    // Iniciar hostname briadcast en modo STA o AP
    if (wifi_mode == WIFI_STA || wifi_mode == WIFI_AP){
        if (MDNS.begin(esp_hostname)){
            MDNS.addService("http", "tcp", 80);
            //log(esp_hostname);
            //MDNS.addService("ws", "tcp", 81);
        }
    }
}

// **************************************************************
// Loop modo cliente
// **************************************************************
void wifiLoop(){
    unsigned long currentMillis = millis();

    if (WiFi.status() != WL_CONNECTED && (currentMillis - previousMillisWIFI >= intervalWIFI)){
        // Para parpadear un LED cuando está conectándose al WiFi no bloqueante
        // Parpadeo Simple del LED cada 100 ms
        blinkSingle(100, WIFILED);

        WiFi.disconnect();
        WiFi.reconnect();
        previousMillisWIFI = currentMillis;

    }else {
        // Parpadeo del LED Tiempo ON y Tiempo OFF
        blinkSingleAsy(10, 500, WIFILED);
    }
}

// **************************************************************
// Loop modo AP
// **************************************************************
void wifiAPLoop(){
    // Parpadeo del LED con tiempo variable como transferencia de datos
    blinkRandomSingle(50, 100, WIFILED);
    // Captive portal DNS re-direct
    dnsServer.processNextRequest(); 
}