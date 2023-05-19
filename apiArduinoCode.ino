#include <WiFi.h>
#include <ArduinoJson.h>

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

  // Conexión a la red Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a la red Wi-Fi...");
  }
  Serial.println("Conectado a la red Wi-Fi");
}

void loop() {
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
    } 
  }
}

