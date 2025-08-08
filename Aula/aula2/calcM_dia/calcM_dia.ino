int valores[100] = {};
int pagMenu = 1;
int lastValue = -100;
int index = 0;

void setup() {
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  Serial.begin(9600);
  Serial.print("Hello World");
  delay(1000);
  clean();
}

void loop() {
  int potVal = map(analogRead(A0), 0, 1020, 0, 10);
  if (digitalRead(11) == HIGH) {
    Serial.println("[Adicionado valor: " + String(potVal) + "]");  
    valores[index] = potVal;
    index++;
    delay(50);
    if (digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
      Serial.println("Array Resetado!");
      reset();
      delay(500);
    }
    delay(450);
    Serial.println("");
  } else if (digitalRead(12) == HIGH) {
    if (digitalRead(11) == HIGH && digitalRead(12) == HIGH) {
      Serial.println("Array Resetado!");
      reset();
      delay(500);
    }
    delay(500);
    if (digitalRead(12) == HIGH) {
    funcao();
    delay(500);
    }
    trocaMenu();
    delay(250);
    Serial.println("");
  }
  if (lastValue != potVal) {
    clean();
    Serial.println("Valor pot: " + String(potVal));  
    lastValue = potVal;
  }
}

void funcao() {
  Serial.println("");
  float total = 0;
  if (pagMenu == 1) {
      Serial.println("[FUNÇÃO APLICADA: 'Média Total']");
      Serial.println("");
      delay(1000);
      for (int i=0; i<index; i++) {
        Serial.println(String(i+1)+"ºN: "+String(valores[i]));
        total += valores[i];
        delay(2000/index);
      }
      Serial.println("");
      delay(1000);
      Serial.println("Total: "+String(total));
      delay(500);
      Serial.println("Média: "+String(total/index));
      delay(3000);
      
   } else if (pagMenu == 3) {
      Serial.println("[FUNÇÃO APLICADA: 'Média Impares']");
      Serial.println("");
      delay(1000);
      Serial.println("Separação");
      int impares[100] = {};
      int indexImpar = 0;
      for (int i=0; i<index-1; i++) {
        if (valores[i]%2 == 0) {
          Serial.println(String(i+1)+"ºN: "+String(valores[i])+" = PAR");
        } else {
          Serial.println(String(i+1)+"ºN: "+String(valores[i])+" = IMPAR");
          impares[indexImpar] = valores[i];
          indexImpar++;
        }
        delay(2000/index);
      }
      Serial.println("");
      delay(1000);
      Serial.println("Soma Final");
      for (int i=0; i<indexImpar; i++) {
        Serial.println(String(i+1)+"ºN: "+String(impares[i]));
        total += impares[i];
        delay(2000/indexImpar);
      }
      delay(1000);
      Serial.println("Total: "+String(total));
      delay(500);
      Serial.println("Média: "+String(total/indexImpar));
      delay(3000);
      
    } else if (pagMenu == 2) {
      Serial.println("[FUNÇÃO APLICADA: 'Média Pares']");
      Serial.println("");
      delay(1000);
      Serial.println("Separação");
      int pares[100] = {};
      int indexPar = 0;
      for (int i=0; i<index-1; i++) {
        if (valores[i]%2 == 0) {
          Serial.println(String(i+1)+"ºN: "+String(valores[i])+" = PAR");
           pares[indexPar] = valores[i];
           indexPar++;
        } else {
          Serial.println(String(i+1)+"ºN: "+String(valores[i])+" = IMPAR");
        }
        delay(2000/index);
      }
      Serial.println("");
      delay(1000);
      Serial.println("Soma Final");
      for (int i=0; i<indexPar; i++) {
        Serial.println(String(i+1)+"ºN: "+String(pares[i]));
        total += pares[i];
        delay(2000/indexPar);
      }
      delay(1000);
      Serial.println("Total: "+String(total));
      delay(500);
      Serial.println("Média: "+String(total/indexPar));
      delay(3000);
    }

  lastValue = -100;
  clean();
}

void trocaMenu() {
    pagMenu += 1; 

    if (pagMenu  > 3) {
      pagMenu  = 1;
    }

    if (pagMenu == 1) {
      Serial.print("[FUNÇÃO ATUAL: 'Média Total']");
    } else if (pagMenu == 2) {
      Serial.print("[FUNÇÃO ATUAL: 'Média Pares']");
    } else if (pagMenu == 3) {
      Serial.print("[FUNÇÃO ATUAL: 'Média Impares']");
    }
}

void clean() {
  for (int i=0; i<50; i++) {  
    Serial.println("");
  }
}

void reset() {
  for (int i=0; i<index; i++) {
    valores[i] = 0; 
  }
  index = 0;
  lastValue = -100;
}
