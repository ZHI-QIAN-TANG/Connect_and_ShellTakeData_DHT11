#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>
#define DHTPIN 11 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "chts520";
const char* password = "12345678";
String IFTTT="https://maker.ifttt.com/trigger/DHT11/with/key/dZYY4mtmzWYKwiI9BkVZV-"; 

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  dht.begin();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
} // setup()

void loop()
{
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  String IFTTTurl=IFTTT+"?value1="+String((float)t)+"&value2="+String((float)h); 
  HTTPClient http;
  Serial.print("===HTTP Send data to IFTTT===\n");
  http.begin(IFTTTurl);

  Serial.print("===HTTP GET Status===\n");
  int httpCode = http.GET();
          if(httpCode > 0) {
            Serial.printf("HTTP to get Feeback status: %d\n", httpCode);
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
            else {
            Serial.printf("HTTP to get Feedback failed, error: %s\n", http.errorToString(httpCode).c_str());
            }
          Serial.println("=================================");
          http.end();
        }
    delay(3600000);
}