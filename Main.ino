#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define DHTPIN 4             // Pin where the DHT sensor is connected
#define DHTTYPE DHT22        // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

int mq6Pin = 34;           // MQ-6 sensor analog input pin
int sensorValue = 0;

const char* ssid = "your-SSID";         // Replace with your Wi-Fi SSID
const char* password = "your-PASSWORD"; // Replace with your Wi-Fi password
String serverUrl = "http://your-server-ip/data";  // Replace with your Flask server URL

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  pinMode(mq6Pin, INPUT);  // Set MQ6 sensor pin as input
  dht.begin();             // Initialize the DHT sensor
  delay(2000);
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Read sensor value from MQ-6
  sensorValue = analogRead(mq6Pin);

  // Print sensor values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C\t");
  Serial.print("LPG GAS Leak (Sensor Value): ");
  Serial.println(sensorValue);

  // Prepare JSON data
  String jsonData = "{\"temperature\": " + String(temperature) + 
                    ", \"humidity\": " + String(humidity) + 
                    ", \"sensor_value\": " + String(sensorValue) + "}";

  // Send data to Flask server via HTTP POST
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);  // Server URL
    http.addHeader("Content-Type", "application/json");

    // Send POST request
    int httpResponseCode = http.POST(jsonData);

    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully to server");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.println("Error in sending POST request");
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();  // Close connection
  } else {
    Serial.println("Wi-Fi Disconnected");
  }

  delay(8000);  // Wait for 8 seconds before sending the next request
}
