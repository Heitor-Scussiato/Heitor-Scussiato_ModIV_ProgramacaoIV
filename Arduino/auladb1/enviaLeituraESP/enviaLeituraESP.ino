#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "Familia Feliz";
const char *password = "mana@mano";
const int http_port = 8080;

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for SSD1306 display connected to custom I2C pins
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Custom I2C pins
#define I2C_SDA 12  // GPIO12 (D6)
#define I2C_SCL 14  // GPIO14 (D5)'

float umidade = 0;
float temperatura = 0;
int mode = 0;
int push = 0;

WiFiClient client;

void setup() {
  delay(1000);
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // Initialize OLED display with the I2C address (0x3C) and custom I2C pins
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  pinMode(D0, INPUT);
  pinMode(D8, INPUT);
  pinMode(D1, OUTPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF); delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); Serial.println(".");

  Serial.print("Conectando");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print("Conectando");
    for (int j=0;j<i;j++) {display.print(".");}
    i++;
    if (i>9) {i=0;}
    display.display(); 
  }
  
  delay(500);
  display.clearDisplay();
  Serial.println ("");
  Serial.print ("Conectado a "); Serial.println (ssid);
  Serial.print ("Endereço IP: "); Serial.println (WiFi.localIP ());
  Serial.print("MAC: ");    Serial.println(WiFi.macAddress());

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Conectado!");
  display.display(); delay(500);
  display.setTextSize(1);
  display.print("SSID: ");
  display.println(ssid);
  display.display(); delay(250);
  display.print("IP: ");
  display.println(WiFi.localIP ());
  display.display(); delay(250);
  display.print("MAC: \n");
  display.println(WiFi.macAddress());
  display.display(); delay(2500);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("HEITOR RS.");
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

void setVal() {
  delay(100);
      umidade = random(50, 100);
      temperatura = random(-10, 43);
      digitalWrite(D5, HIGH);
  delay(500);
}

void loop() {

  if (digitalRead(D0) == HIGH && push == 0) {
    push = 1;
    mode += 1;
    Serial.println("\nModo alterado - " + String(mode));
    if (mode => 2) {mode = 0;}
    digitalWrite(D5, HIGH);   // essa desgraça tá ferrando com tudo
    delay(100);               // simplesmente, a tela congela nessa parte
    display.display();        // vou ter que refazer a lógica do botão
  } 
  if (digitalRead(D0) == LOW) {push = 0;}
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("HEITOR RS.");
  display.setTextSize(1);
  if (mode == 1) {
    umidade = map(analogRead(A0), 0, 1024, 0, 100);
    Serial.println("A0: " + String(umidade));
  } else if (mode == 2) {
    temperatura = map(analogRead(A0), 0, 1024, -30, 50);
  }
  
  display.println("\nUm: " + String(umidade) + "%");
  display.println("Temp: " + String(temperatura) + "C");
  display.display(); 

  digitalWrite(D1, LOW);

  if (digitalRead(D8) == HIGH) {
    delay(100);
    display.setCursor(0, 50);
    display.println("Enviando...");   
    display.display();
    digitalWrite(D5, HIGH);
    String Mac = WiFi.macAddress();
    String datatime = "2025-09-28 18:00";
    String postData = "idmac=" + String(Mac) + "&umidade=" + String(umidade) + "&temperatura=" + String(temperatura) + "&datatime=" + datatime;
    enviaServer(postData);
    delay(1000);
    digitalWrite(D1, LOW);
    setVal();
    delay(500);
    display.clearDisplay();
    digitalWrite(D1, HIGH);
    delay(100);
  }
}
