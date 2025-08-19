float cestos[3][6] = {
  // peixeMin, peixeMax, #peixeMax, #peixe, pesoMax, pesoTotal.
  {1, 3,  9, 0, 30, 0}, // P,  
  {4, 6,  7, 0, 45, 0}, // M
  {7, 10, 6, 0, 65, 0}  // G
};

int bot1 = 0;
int bot2 = 0;

int etapa = 0;
int potVal = 0;

float distancia = 0;
float profundidade = 0;
int isca = 0; // 1=P | 2=M | 3=G
int forca = 0;
int tempo = 0;
int peso = 0;

void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  Serial.begin(9600);
  Serial.println("Hello World! "); 
}

void loop() {
    potVal = analogRead(5);
    Serial.print(".");
    if (digitalRead(0) == HIGH && etapa!=2) {pescar();}
    if (digitalRead(1) == HIGH && etapa==0) {matriz();}
    delay(125);
}

void pescar() {
    if (etapa == 0) { // força do lance
       etapa = 1;
       distancia = map(potVal, 0, 1022, 1, 200)/4;
       Serial.println("Você joga o anzol em" + String(distancia) + "m");
       delay(1000);
    } else
    
    if (etapa == 1) { // profundidate
        etapa = 2;
        profundidade = map(potVal, 0, 1022, 0, 100)/4;
        Serial.println("O anzol afunda até esticar a linha em" + String(profundidade) + "m");
        delay(1000);
    } else
    
    if (etapa == 2) { // pegar peixe
      isca = random(-4,4);  // TODO: Fazer variavel que muda conforme a distancia / profundidade
      if (isca > 0) {
        peso = (((random(3)+1)*3)+1);
        tempo = peso*10;
        int pego = 0;
        for (int i=0; i<tempo*100;i++){
            Serial.println("PEIXE! Aperte para puxar!!!");

            if (digitalRead(0) == HIGH) {
              if (bot1 == 0) {
                forca++;  // TODO: Ataque "Critico" com o potenciometro
                Serial.println(String(forca)+"x!  " + String(i)+"/"+String(tempo));
                bot1=1;
              }  
            } else {bot1=0;}
            
            if (forca/10 > isca) {
              Serial.println("PEIXE PEGO!");
              pego = peso;
              break;
            }
            delay(0.01);
        }
        if (pego > 0) {
          Serial.println("Peso: " + String(pego));
          int tara = map(pego, 1, 10, 0, 2);
          if (cestos[tara][3]+1 <= cestos[tara][2]) {
            if (cestos[tara][5]+pego <= cestos[tara][4]) {
              cestos[tara][3]++;
              cestos[tara][5] += pego;
              etapa = 0;
            } else {Serial.println("Peixe excede o peso, você devolveu para o Açude");}
          } else {Serial.println("Você já tem muitos peixes, você devovleu para o Açude");}
        } else {
            Serial.println("Que pena...");  
            etapa = 0;
        }
        
      } else {
       Serial.println("Nada..."); 
       delay(1000);
      }    
    }
}

void matriz() {
  for (int i=0;i<3;i++) {
    Serial.println("Cesto"+String(i));
    for (int j=0;j<6;j++) {
      Serial.print(String(cestos[i][j])+" ");
    }
  }
  delay(2000);
}
