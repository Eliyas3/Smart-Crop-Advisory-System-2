#include <WiFi.h>
#include <DHT.h>
#include <HTTPClient.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int soilPin = 34;
int rainPin = 35;
int ldrPin = 32;
int relayPump = 26;
int buzzer = 27;

const char* ssid = "YourWiFi";
const char* password = "YourPassword";

String serverName = "http://yourserver.com/update.php";

void setup() {
Serial.begin(115200);

pinMode(relayPump, OUTPUT);
pinMode(buzzer, OUTPUT);

digitalWrite(relayPump, HIGH);
digitalWrite(buzzer, LOW);

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
int rain = analogRead(rainPin);
int light = analogRead(ldrPin);

Serial.println("------ Smart Crop Data ------");
Serial.print("Temp: ");
Serial.println(temp);

Serial.print("Humidity: ");
Serial.println(hum);

Serial.print("Soil: ");
Serial.println(soil);

Serial.print("Rain: ");
Serial.println(rain);

Serial.print("Light: ");
Serial.println(light);

if (soil > 3000 && rain > 2500) {
digitalWrite(relayPump, LOW);
Serial.println("Pump ON");
}
else {
digitalWrite(relayPump, HIGH);
Serial.println("Pump OFF");
}

if (temp > 38) {
tone(buzzer, 1000);
delay(1000);
noTone(buzzer);
Serial.println("High Temp Alert");
}

if (WiFi.status() == WL_CONNECTED) {
HTTPClient http;

String url = serverName + "?temp=" + String(temp) +
"&hum=" + String(hum) +
"&soil=" + String(soil) +
"&rain=" + String(rain) +
"&light=" + String(light);

http.begin(url);
http.GET();
http.end();
}

if (soil > 3200)
Serial.println("Advice: Irrigate Crop");

if (rain < 1500)
Serial.println("Advice: Rain Expected");

if (light < 1000)
Serial.println("Advice: Low Sunlight");

delay(5000);
}