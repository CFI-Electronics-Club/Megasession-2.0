// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "SPIFFS.h"

Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp; // Define the sensor events (variables) to be retrieved from the sensor

// Replace with your network credentials
const char* ssid = "";
const char* pass = "";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readMPUTemperature()
{
  mpu.getEvent(&a, &g, &temp);
  float t = temp.temperature;
  if (isnan(t)){
    Serial.println("Failed to read from MPU6050 Sensor");
    return "";
   }
   else{
    Serial.println(t);
    return String(t);
   }
}

// Init MPU6050
void beginMPU(){
  if (!mpu.begin(0x68)) {
    Serial.println("Sensor Error! Wrong I2C Address");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 working! I2C initiated");
}

void beginSPIFFS() {
  if (!SPIFFS.begin(true)) // Open the 'data' file in SPIFFS plugin and check if there is any empty content.
  { 
    Serial.println("An error has occurred while mounting SPIFFS");
  }
  else
    Serial.println("SPIFFS data file retreived successfully");
}

// Initialize WiFi
void beginWiFi() {
  //WiFi.mode(WIFI_STA);  //Wifi in static mode(client mode) 
  WiFi.begin(ssid, pass);
  Serial.println("");
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.print("The IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  beginMPU();
  beginSPIFFS();
  beginWiFi();
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readMPUTemperature().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  Serial.println(readMPUTemperature());
  delay(1000);
}
