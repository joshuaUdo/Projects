#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "DHT.h"

#define DHTTYPE DHT11

const char *ssid = "iPhone 14 Plus";   // Enter SSID here
const char *password = "jbgadget2023"; // Enter Password here
WebServer server(80);

// Thingspeak Setup
String apiKey = "23RVPWROQRM5KB6A";
const char *thingspeakServer = "https://api.thingspeak.com";

// DHT Sensor setup
uint8_t DHTPin = 4;
DHT dht(DHTPin, DHTTYPE);

unsigned long lastSend = 0;
unsigned long interval = 15000;
float currentTemperature = 0.0; // Use distinct names for clarity
float currentHumidity = 0.0;    // Use distinct names for clarity
bool sensorReadSuccess = false; // Flag to indicate if last sensor read was successful

void handle_OnConnect();
void handle_NotFound();
String sendHTML (float temperaturestat, float Humiditystat);

void setup()
{
  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);

  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    Serial.print("Status: ");
    Serial.println(WiFi.status());
  }

  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient(); // Handle client requests for the web server

  // Check if it's time to send data to ThingSpeak and read sensor
  if ((millis() - lastSend) >= interval)
  {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (isnan(temp) || isnan(hum))
    {
      Serial.println("Failed to read from DHT sensor");
      sensorReadSuccess = false; // Mark sensor read as unsuccessful
    }
    else
    {
      currentTemperature = temp; // Update global variables with latest successful readings
      currentHumidity = hum;
      sensorReadSuccess = true;  // Mark sensor read as successful

      Serial.println("Sending data to ThingSpeak...");
      Serial.print("Temp: ");
      Serial.println(currentTemperature);
      Serial.print("Humidity: ");
      Serial.println(currentHumidity);

      if (WiFi.status() == WL_CONNECTED)
      {
        HTTPClient http;
        String url = String(thingspeakServer) + "/update?api_key=" + apiKey + "&field1=" + String(currentTemperature) + "&field2=" + String(currentHumidity);

        http.begin(url);
        int httpCode = http.GET();
        http.end();

        if (httpCode > 0)
        {
          Serial.println("Data sent successfully!");
        }
        else
        {
          Serial.print("HTTP error: ");
          Serial.println(httpCode);
        }
      }
    }
    lastSend = millis(); l
  }
}

void handle_OnConnect()
{
  if (sensorReadSuccess) {
    server.send(200, "text/html", sendHTML(currentTemperature, currentHumidity));
  } else {
    server.send(200, "text/html", "<h1>Sensor Error: Could not read data.</h1><p>Please check the sensor connection.</p>");
  }
}

void handle_NotFound()
{
  server.send(404, "text/plain", "Not found");
}

String sendHTML(float Temperaturestat, float Humiditystat)
{
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head>\n";
  ptr += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP32 Weather Station</title>\n";
  ptr += "<style>\n";
  ptr += "  body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background: linear-gradient(135deg, #f0f4f8, #c8d8e8); color: #333; margin: 0; padding: 20px; display: flex; justify-content: center; align-items: center; min-height: 100vh; }\n";
  ptr += "  .container { background-color: #fff; padding: 40px; border-radius: 20px; box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1); text-align: center; max-width: 500px; width: 100%; transition: transform 0.3s ease; }\n";
  ptr += "  .container:hover { transform: translateY(-5px); }\n";
  ptr += "  h1 { font-size: 2.5rem; color: #1e3a5f; margin-bottom: 20px; }\n";
  ptr += "  .data-container { display: flex; justify-content: space-around; flex-wrap: wrap; margin-top: 30px; }\n";
  ptr += "  .data-item { font-size: 1.5rem; margin: 15px; padding: 20px; border-radius: 15px; background-color: #eef2f6; box-shadow: inset 0 2px 4px rgba(0, 0, 0, 0.05); flex: 1; min-width: 150px; }\n";
  ptr += "  .data-item p { margin: 0; font-weight: bold; }\n";
  ptr += "  .value { font-size: 2rem; color: #007bff; margin-top: 5px; }\n";
  ptr += "  .label { font-size: 1rem; color: #777; }\n";
  ptr += "  @media (max-width: 600px) { h1 { font-size: 2rem; } .container { padding: 20px; } .data-item { font-size: 1.2rem; } .value { font-size: 1.8rem; } }\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div class=\"container\">\n";
  ptr += "  <h1>ESP32 Weather Report</h1>\n";

  // Temperature data item
  ptr += "  <div class=\"data-container\">\n";
  ptr += "    <div class=\"data-item\">\n";
  ptr += "      <p class=\"label\">Temperature</p>\n";
  ptr += "      <p class=\"value\">";
  ptr += String(Temperaturestat, 1);
  ptr += "°C</p>\n";
  ptr += "    </div>\n";

  // Humidity data item
  ptr += "    <div class=\"data-item\">\n";
  ptr += "      <p class=\"label\">Humidity</p>\n";
  ptr += "      <p class=\"value\">";
  ptr += String(Humiditystat, 1);
  ptr += "%</p>\n";
  ptr += "    </div>\n";
  ptr += "  </div>\n";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
