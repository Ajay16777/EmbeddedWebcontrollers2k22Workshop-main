#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


const char *ssid = "Sen BILIRSIN";
const char *password = "ikbendom123";

// Your Domain name with URL path or IP address with path
const char *serverName = "http://192.168.0.209:2022/update-sensor";
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
float temperature;
float humidity;
float pressure;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;



void setup()
{
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
   bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delay(1000);

  Serial.println();

}
void getBME280Readings(){
 
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");
  
  // Convert temperature to Fahrenheit
  /*Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");*/
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}
void loop()
{
 
  // Send an HTTP POST request every 5s
  if ((millis() - lastTime) > timerDelay)
  {
    
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      WiFiClient client;
      HTTPClient http;

      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName); 
      getBME280Readings();

      // Create data and serialize it to JSON
      DynamicJsonDocument doc(1024);
      doc["temperature"] = bme.readTemperature();
      doc["humidity"] = bme.readHumidity();
      doc["altitude"]= bme.readAltitude(SEALEVELPRESSURE_HPA); 
      doc["pressure"]=bme.readPressure(); 
      String mesage = "";
      serializeJson(doc, mesage);

      // HTTP request with a content type: application/json
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST(mesage);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      // Free resources
      http.end();
    }
    else
    {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
    }
}