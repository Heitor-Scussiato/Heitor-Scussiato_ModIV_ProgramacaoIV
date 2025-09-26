#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "TP-Link_688A";
const char *password = "debarbamiguel";
const int http_port = 8080;

WiFiClient client;

void setup() {
  delay(1000);
  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF); delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); Serial.println(".");
  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println ("");
  Serial.print ("Conectado a "); Serial.println (ssid);
  Serial.print ("Endereço IP: "); Serial.println (WiFi.localIP ());
  Serial.print("MAC: ");    Serial.println(WiFi.macAddress());
}

void enviaServer(String postData) {
  HTTPClient http;
  http.begin(client, "http://modulo4.migueldebarba.com.br/heitorrs/aula4/insertleitura.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);
  String payload = http.getString();
  Serial.println("httpCode:" + String(httpCode));
  Serial.println("payload:" + payload);
  http.end();
}


void loop() {

delay(500);
    String Mac = WiFi.macAddress();
    int umidade = random(50, 100); // teste de valor
    int temperatura = random(-15, 40); // teste de valor
    String datatime = "2025-09-26 17:00";
    String postData = "idmac=" + String(Mac) + "&umidade=" + String(umidade) + "&temperatura=" + String(temperatura) + "&datatime=" + datatime;
    enviaServer(postData);   delay(1000);
  
  delay(10000);
}
