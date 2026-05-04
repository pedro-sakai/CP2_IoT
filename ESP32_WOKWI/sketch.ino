#include <WiFi.h>
#include <WiFiClientSecure.h> 
#include <PubSubClient.h>
#include <DHT.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "7b4ffbd40fc844f9ab5582772cea1c8e.s1.eu.hivemq.cloud";
const char* mqtt_user = "cp2iot"; 
const char* mqtt_pass = "Cp2iot123abc";   

#define DHTPIN 15
#define DHTTYPE DHT22
#define TRIG_PIN 5
#define ECHO_PIN 18

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure espClient; 
PubSubClient client(espClient);

unsigned long lastMsg = 0;

void setup_wifi() {
  delay(10);
  Serial.println("\nConectando WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexao MQTT Cloud...");
    String clientId = "ESP32_Maq1_" + String(random(0xffff), HEX);
  
    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass)) {
      Serial.println("Conectado ao Cloud!");
    } else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  
  espClient.setInsecure(); 
  client.setServer(mqtt_server, 8883); 
  
  dht.begin();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float lerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duracao = pulseIn(ECHO_PIN, HIGH);
  return duracao * 0.034 / 2; 
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000) { 
    lastMsg = now;
    float t = dht.readTemperature();
    float d = lerDistancia();

    if (!isnan(t)) {
      client.publish("maquina1/temperatura", String(t).c_str());
      client.publish("maquina1/distancia", String(d).c_str());
      Serial.print("Enviado ao Cloud -> Temp: "); Serial.print(t);
      Serial.print(" | Dist: "); Serial.println(d);
    }
  }
}