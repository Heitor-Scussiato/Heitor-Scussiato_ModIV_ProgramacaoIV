float cestos[3][6] = {
  // peixeMin, peixeMax, #peixeMax, #peixe, pesoMax, pesoTotal.
  {1, 3,  9, 0, 30, 0}, // P,  
  {4, 6,  7, 0, 45, 0}, // M
  {7, 10, 6, 0, 65, 0}  // G
};

int potVal = 0;

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  Serial.begin(9600);
  Serial.println("Hello World! "); 
}

void pesca(int peso) {
   Serial.println("Peso: " + String(peso));
    int tara = 0;
    if (peso < 4) {tara = 0;} else if (peso < 7) {tara = 1;} else {tara = 2;}
    if (cestos[tara][3]+1 <= cestos[tara][2]) {
      if (cestos[tara][5]+peso <= cestos[tara][4]) {
        cestos[tara][3]++; 
        cestos[tara][5] += peso;
      } else {Serial.println("Peixe excede o peso, você devolveu para o Açude");}
    } else {Serial.println("Você já tem muitos peixes, você devovleu para o Açude");}
}

void menu() {
  for (int i=0;i<3;i++) {
    Serial.println("");
    Serial.println("Cesto"+String(i));
    for (int j=0;j<6;j++) {
      Serial.print(String(cestos[i][j])+" ");
    }
  }
  delay(2000);
}
  
void loop() {
    int peso = map(analogRead(5), 0, 1022, 1, 10);
    Serial.println("Peso: "+String(peso));
    if (digitalRead(0) == HIGH) {pesca(peso);}  
    if (digitalRead(1) == HIGH) {menu();}
    delay(125);
}
