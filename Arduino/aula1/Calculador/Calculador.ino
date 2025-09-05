int lastVal = 100;
int currVal = 1000;
int currIdx = 0;
int somaVal[] = {};
int total = 0;
int leave = 0;
int decH = 0;

void setup() {
  pinMode(13, INPUT);
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  Serial.print("Hello World");
  delay(1000);
  clean();
}

void loop() {
 leave = 0;
 currIdx = 0;
 while (leave != 1) {
  decH = 0;  
  while (true) {
    currVal = map(analogRead(A0), 0, 1022, 0, 10) + (decH * 10);
    if (lastVal != currVal) {
      clean();
      Serial.println("Digite um valor");
      Serial.println("Coloque o potenciometro em '0' para terminar");
      Serial.println("Botão 13 seleciona");
      Serial.println("Botão 12 aumenta 10");
      Serial.println("Botão 11 subtrai 10");
      Serial.println(String(currIdx+1) + "º valor: " + String(currVal));
    }
    lastVal = currVal;
    if (digitalRead(13) == HIGH) {
      if (map(analogRead(A0), 0, 1022, 0, 10) == 0) {
        leave = 1;
        Serial.println("leaving...");
        break;
      } else {
        somaVal[currIdx] = currVal;
        currIdx += 1;
        Serial.print("Salvando");
        for (int i=0; i<3; i++) {
          delay(100);
          Serial.print(".");  
        }
        break;
      } 
    }
    if (digitalRead(12) == HIGH) {
      Serial.print("Aumentando");
      for (int i=0; i<3; i++) {
        delay(100);
        Serial.print(".");  
      }
      decH += 1;
      clean();
    }
    if (digitalRead(11) == HIGH) {
      Serial.print("Diminuindo");
      for (int i=0; i<3; i++) {
        delay(100);
        Serial.print(".");  
      }
      decH -= 1;
      clean();
    }
    delay(100);
  }

  
  delay(100);
  lastVal = 100;
 }
 
  Serial.print("Salvando");
  for (int i=0; i<3; i++) {
    delay(500);
    Serial.print(".");  
  }
  
  delay(500);
  Serial.println("");
  Serial.println("");
  
  Serial.print("Somando");
  for (int i=0; i<3; i++) {
    delay(500);
    Serial.print(".");  
  }
  delay(500);
  clean();
  
  for (int num=0; num<currIdx; num++) {
    total += somaVal[num];  
    Serial.println(String(num+1) + "º valor: " + String(somaVal[num]));
    delay(250);
  }
  delay(500);
  Serial.println("Soma Valores: " + String(total));
  
  delay(3000);
  clean();
  
  Serial.print("Resetando");
  for (int i=0; i<3; i++) {
    delay(500);
    Serial.print(".");  
  }
  
  delay(500);
  clean();
}

void clean() {
  for (int i=0; i<50; i++) {  
    Serial.println("");
  }
}
