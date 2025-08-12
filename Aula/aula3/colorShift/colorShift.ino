int Led[3] = {3,5,6};
int cores[8][3] = {
// R,  G,  B
  {200,0,  0  }, 
  {0,  200,0  },
  {0,  0,  200},
  {130,200,0  },
  {130,0,  200},
  {0,  200,200},
  {130,200,200},
  {0  ,0  ,0  }
};

int LedOld[3] = {0,0,0};

void setup() {
  for (int i=0; i<sizeof(Led)-1; i++) {
    pinMode(Led[i], OUTPUT);
    analogWrite(Led[i], 100);
    delay(500);
    digitalWrite(Led[i], LOW);
  }
  delay(1000);
}

void loop() {
  for (int cor=0;cor<8;cor++) {
    for (int i=0; i<3; i++) {
       if (LedOld[i]-cores[cor][i]<0) {
        int diff = LedOld[i]-cores[cor][i];
        for (LedOld[i]; LedOld[i]<cores[cor][i]; LedOld[i]++) {
            analogWrite(Led[i], LedOld[i]);
            delay(500/diff*-1);
        }
       } else {
        int diff = LedOld[i];
        for (LedOld[i]; LedOld[i]>cores[cor][i]; LedOld[i]--) {
            analogWrite(Led[i], LedOld[i]);
            delay(500/diff);
        }
       }
    }
    delay(500);
  }
  delay(500);
}
