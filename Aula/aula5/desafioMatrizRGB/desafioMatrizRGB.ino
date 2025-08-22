
// Heitor Rauber Scussiato =]

int cores[6][4] = { 
  // pode adicionar quantas cores precisar, o código se adapta a qualquer valor.
  // (só mude o tamanho da matriz)
  {150,0,0,    0}, // R, G, B, vezes usado
  {0,150,0,    0},
  {0,0,150,    0},
  {100,150,0,  0},
  {100,0,150,  0},
  {0,150,150,  0}
};

int led[3] = {9,10,11};

int potVal=0;
int potOld=-10;
int on=0;


void fixTamaho(int num) {
  if    (num < 10)    {Serial.print(" " + String(num) + " ");}
  else if (num < 100) {Serial.print(" " + String(num));}
  else                {Serial.print(String(num));}
  Serial.print(" | ");
}

void menu() {
  int total = 0;
   for (int i=0;i<(sizeof(cores)/sizeof(cores[0]));i++) {
    total += cores[i][3];
  }  
  Serial.println("\n\nTotal de usos: " + String(total));
  delay(500);
  for (int i=0;i<(sizeof(cores)/sizeof(cores[0]));i++) {
    float pcent = cores[i][3];
    pcent = pcent/total*100;
    (String(cores[i][3]) + " (" + String(pcent) + "%)");
    Serial.print(String(i+1) + "# ");  
    fixTamaho(cores[i][0]);
    fixTamaho(cores[i][1]);
    fixTamaho(cores[i][2]);
    Serial.println(String(cores[i][3]) + " (" + String(pcent) + "%)");
    delay(5000/(sizeof(cores)/sizeof(cores[0])));
    }  
    delay(1000);
    Serial.println("\n");
}

void ligaLed(int id) {
  Serial.println("Cor " + String(id+1) + " Ligada!");
  for (int i=0;i<3;i++) {
    analogWrite(led[i], cores[id][i]);  
  }  
  cores[id][3] += 1;
  delay(100);
}

void setup() {
    Serial.begin(9600);  
    Serial.print("Inicializando");
    delay(500);
    for (int i=0;i<3;i++) {
      pinMode(led[i], OUTPUT);
      Serial.print(".");
      delay(250);
    }
    delay(250);
    pinMode(3, OUTPUT);
    Serial.println("\n\nPronto para Uso!\n\n");
    delay(1000);
    float pcent = cores[0][3];
}

void loop() {
  potVal = map(analogRead(0), 0, 1020, 0, (sizeof(cores)/sizeof(cores[0]))-1);
  if (potVal!=potOld) {potOld=potVal; Serial.println("Cor Selecionada:" + String(potVal+1)); }
   if (digitalRead(2) == HIGH && on==0) {ligaLed(potVal); on=1;} else if (digitalRead(2) == LOW) {on=0;}
   if (digitalRead(3) == HIGH) {menu();}
   delay(100);
}
