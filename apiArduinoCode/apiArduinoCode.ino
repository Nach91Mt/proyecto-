#include <WiFi.h>
#include <ArduinoJson.h>
#include <FastLED.h>

#define NUM_LEDS 300        // Cantidad total de LEDs en la tira
#define DATA_PIN 2         // Pin de datos conectado a la tira de LEDs
int BRIGHTNESS= 255;     // Brillo de los LEDs (0-255)
//establecco el numero de nleds y el color que van a tener
CRGB leds[NUM_LEDS];
CRGB colorLeds;
// Configuración de la red Wi-Fi
const char* ssid = "Chupacabras";
const char* password = "12345678";

// URL del servidor
const char* serverUrl = "nach.pythonanywhere.com";
const int serverPort = 80;
const char* endpoint = "/json";

// Tamaño máximo de respuesta HTTP
const int MAX_RESPONSE_SIZE = 1024;
int ilu,nleds,pro;
// Objeto de cliente Wi-Fi
WiFiClient client;

void setup() {
  Serial.begin(9600);
  
  //Establezco los nleds y su brillo 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Conexión a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }
  Serial.println("Conectado a la red Wi-Fi");
  actualizar();
}

void loop() {
    
    switch (pro)
    {
    case 1:
      efect1();
      break;
    case 2:
    efect2();
      break;
    case 3:
    efect3();
      break;
    default:
      break;
    }
   
    }
  void efect1(){
    // Encender el primer LED
    leds[0] = colorLeds;

  // Encender los dos LEDs siguientes
  for (int i = 1; i < 3; i++) {
    leds[i] = colorLeds;
    FastLED.show();
    delay(10);
  }

  // Apagar todos los LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
     if(pro!=1){
      break;
    }
   
  }

  // Mover los dos LEDs encendidos a lo largo de la tira
  for (int i = 3; i < NUM_LEDS; i++) {
    if(pro!=1){
      break;
    }
    
    leds[i - 3] = CRGB::Black;
    leds[i] = colorLeds;
    FastLED.show();
    delay(10);
    
    
  }
  
  // Apagar los dos LEDs finales
  for (int i = NUM_LEDS - 3; i < NUM_LEDS; i++) {
    if(pro!=1){
      break;
    }
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(10);
    
  }
  actualizar();
  }
  
  void efect2(){
    fill_solid(leds,NUM_LEDS,colorLeds);
    for(int i =0;i<255;i++){
      if(pro !=2){
        break;
      }
      FastLED.setBrightness(i);
      FastLED.show();
    }
    actualizar();
    for(int i=255; i>0;i--){
      if(pro !=2){
        break;
      }
      FastLED.setBrightness(i);
      FastLED.show();
    }
    actualizar();
  }
 
 void efect3(){
  fill_solid(leds,NUM_LEDS,CRGB::Red);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  actualizar();
 }
 // funcion que actualiza la informacionde la api
  void actualizar(){
    // Verificar si se puede conectar al servidor
  if (client.connect(serverUrl, serverPort)) {
    // Realizar la solicitud HTTP GET
    client.print(String("GET ") + endpoint + " HTTP/1.1\r\n" +
                 "Host: " + serverUrl + "\r\n" +
                 "Connection: close\r\n\r\n");

    // Esperar a que llegue la respuesta del servidor
    while (!client.available()) {
     // delay(100);
    }
    // Omitir los encabezados HTTP
    String response = client.readString();
    int index = response.indexOf("\r\n\r\n");
    if (index != -1) {
      response = response.substring(index + 4);
    }
    // Leer y almacenar la respuesta HTTP
    
    // Cerrar la conexión
    client.stop();

    // Verificar si la respuesta HTTP es válida
    if (response.length() > 0) {
      // Crear un objeto JSON para analizar la respuesta
      DynamicJsonDocument jsonBuffer(MAX_RESPONSE_SIZE);
      DeserializationError error = deserializeJson(jsonBuffer, response);
      Serial.println("Respuesta del servidor:");
      Serial.println(response);
      // Verificar si el análisis del JSON fue exitoso
      if (error) {
        Serial.print("Error al analizar el JSON: ");
        Serial.println(error.c_str());
      } 
        // Extraer los valores y almacenarlos en variables
        String hexadecimal=jsonBuffer["color"];
        //combierto string a uint8_t para que sea reconocido como hexadecimal y me cambie el color
        uint32_t  color1 = strtol(hexadecimal.c_str(),NULL,16);
         ilu = jsonBuffer["ilu"];
         nleds = jsonBuffer["leds"];
         pro = jsonBuffer["pro"];
        /*
        // Imprimir los valores en el monitor serie
        Serial.print("Color: ");
        */Serial.println(color1);
        /*Serial.print("Iluminación: ");
        Serial.println(ilu);
        Serial.print("LEDs: ");
        Serial.println(nleds);
        Serial.print("Pro: ");
        Serial.println(pro);
      */
        
        BRIGHTNESS=ilu;
        //NUM_LEDS=nleds;
        colorLeds.setColorCode(color1);
        FastLED.setBrightness(BRIGHTNESS);
    } 
  }
  
}

