#include <WiFi.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int soilPin = 34;
int relayPin = 26;

const char* ssid = "YourWiFi";
const char* password = "YourPassword";

void setup() {
Serial.begin(115200);

pinMode(relayPin, OUTPUT);
digitalWrite(relayPin, HIGH);

dht.begin();

WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}

Serial.println("WiFi Connected");
}

void loop() {
float temp = dht.readTemperature();
float hum = dht.readHumidity();
int soil = analogRead(soilPin);

Serial.print("Temperature: ");
Serial.println(temp);

Serial.print("Humidity: ");
Serial.println(hum);

Serial.print("Soil Moisture: ");
Serial.println(soil);

if (soil > 3000) {
digitalWrite(relayPin, LOW);
Serial.println("Pump ON - Soil Dry");
}
else {
digitalWrite(relayPin, HIGH);
Serial.println("Pump OFF - Soil Wet");
}

if (temp > 35) {
Serial.println("Warning: High Temperature");
}

if (hum < 40) {
Serial.println("Low Humidity Alert");
}

delay(3000);
}