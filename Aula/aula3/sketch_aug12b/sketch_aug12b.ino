int Led[3] = {3,5,6};
int cores[8][3] = {
// R,  G,  B
  {0  ,0  ,0  },
  {200,0,  0  }, 
  {0,  200,0  },
  {0,  0,  200},
  {150,200,0  },
  {150,0,  200},
  {0,  200,200},
  {150,150,150}
};

int oldPotVal = -10;

void setup() {
  Serial.begin(9600);
  for (int i=0; i<sizeof(Led)-1; i++) {
    pinMode(Led[i], OUTPUT);
    analogWrite(Led[i], 100);
    delay(500);
    digitalWrite(Led[i], LOW);
  }
  Serial.println(String(sizeof(cores)/sizeof(cores[0])));
  delay(1000);
}

void loop() {
  int potVal = map(analogRead(0), 0,1024,0, sizeof(cores)/sizeof(cores[0]));
  if (potVal != oldPotVal) {
    for (int i=0; i<3; i++) {
      analogWrite(Led[i], cores[potVal][i]);  
    }
    oldPotVal = potVal;
  }
  delay(5);
}
