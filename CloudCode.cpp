#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

#define WIFI_SSID "YourWiFi"
#define WIFI_PASSWORD "YourPass"

#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-secret-key"
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

int soilPin = 34;
int relayPin = 26;

void setup() {
Serial.begin(115200);
pinMode(relayPin, OUTPUT);
digitalWrite(relayPin, HIGH);

WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
}

config.host = FIREBASE_HOST;
config.signer.tokens.legacy_token = FIREBASE_AUTH;
Firebase.begin(&config, &auth);

dht.begin();
}

void loop() {
float temp = dht.readTemperature();
float hum = dht.readHumidity();
int soil = analogRead(soilPin);

Firebase.setFloat(firebaseData,"/farm/temp",temp);
Firebase.setFloat(firebaseData,"/farm/humidity",hum);
Firebase.setInt(firebaseData,"/farm/soil",soil);

if(soil > 3000){
digitalWrite(relayPin, LOW);
Firebase.setString(firebaseData,"/farm/status","Pump ON");
}
else{
digitalWrite(relayPin, HIGH);
Firebase.setString(firebaseData,"/farm/status","Pump OFF");
}

delay(5000);
}