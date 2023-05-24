#include <WiFi.h>
#include <ArduinoJson.h>
#include <FastLED.h>

#define NUM_LEDS 60        // Cantidad total de LEDs en la tira
#define DATA_PIN 6         // Pin de datos conectado a la tira de LEDs
#define BRIGHTNESS 255     // Brillo de los LEDs (0-255)
//establecco el numero de leds y el color que van a tener
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
const int MAX_RESPONSE_SIZE = 2024;
int ilu,leds,pro;
// Objeto de cliente Wi-Fi
WiFiClient client;

void setup() {
  Serial.begin(9600);
  
  //Establezco los leds y su brillo 
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
    delay(100);
  }

  // Apagar todos los LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  // Mover los dos LEDs encendidos a lo largo de la tira
  for (int i = 3; i < NUM_LEDS; i++) {
    if(pro!=1){
      break;
    }
    leds[i - 3] = CRGB::Black;
    leds[i] = CRGB::color;
    FastLED.show();
    delay(100);
    
  }
  actualizar();
  // Apagar los dos LEDs finales
  for (int i = NUM_LEDS - 3; i < NUM_LEDS; i++) {
    if(pro!=1){
      break;
    }
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
    
  }
  actualizar();
  }
  
  void efect2(){
    fil.solid(leds,NUM_LEDS,color)
    FastLED.show();
    for(int i =0;i<255;i++){
      if(pro !=2){
        break;
      }
      FastLED.setBrightness(i);
    }
    actualizar()
    for(int i=255; i>0;i--){
      if(pro !=2){
        break;
      }
      FastLED.setBrightness(i);
    }
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
      delay(100);
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
        String color = jsonBuffer["color"];
         ilu = jsonBuffer["ilu"];
         leds = jsonBuffer["leds"];
         pro = jsonBuffer["pro"];

        // Imprimir los valores en el monitor serie
        Serial.print("Color: ");
        Serial.println(color);
        Serial.print("Iluminación: ");
        Serial.println(ilu);
        Serial.print("LEDs: ");
        Serial.println(leds);
        Serial.print("Pro: ");
        Serial.println(pro);

        BRIGHTNESS=ilu;
        NUM_LEDS=leds;
        colorLeds=color;
        FastLED.setBrightness(BRIGHTNESS);
    } 
  }
}

