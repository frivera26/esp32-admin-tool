

// **************************************************************
// Definiciones
// **************************************************************
#define RELAY1  27   //GPIO27 para salida de Relay 1
#define RELAY2  26   //GPIO26 para salida de Relay 2
#define WIFILED 12   //GPIO12 lED indicador WiFi
#define MQTTLED 13   //GPIO27 LED indicador MQTT

// **************************************************************
// Versión del hardware
// **************************************************************
#define HW "ADMIN_ESP32 v1 00000000"    // Versión del hardware

// **************************************************************
// Zona WiFi
// **************************************************************
boolean wifi_staticIP;           // Uso de IP estática
char    wifi_ssid[30];           // Red WiFi
char    wifi_password[30];       // Contraseña de red WiFi
char    wifi_ip_static[15];      // IP estático
char    wifi_gateway[15];        // Gateway
char    wifi_subnet[15];         // Subred
char    wifi_primaryDNS[15];     // DNS primario
char    wifi_secondaryDNS[15];   // DNS secundario

// **************************************************************
// Zona configuración general
// **************************************************************
char    id[30];                   // ID del dispositivo
int     bootCount;               // Número de reinicios

// **************************************************************
// Zona AP
// **************************************************************
boolean ap_accessPoint;          // Uso de modo AP
char    ap_nameap[31];           // SSID AP
char    ap_passwordap[63];       // Password AP
unsigned char    ap_canalap;     // Canal AP
unsigned char    ap_hiddenap;    // Es visible o no el AP (0-Visible 1-Oculto)
unsigned char    ap_connetap;    // Número de conexiones

// **************************************************************
// Zona Otras variables
// **************************************************************
u_int8_t ip[4];                  // Variable función convertir string a IP
