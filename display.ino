/*
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
 */


int characters[10][7] = {
  { LOW,  LOW,  LOW,  HIGH, LOW,  LOW,  LOW  }, // 0
  { HIGH, LOW,  LOW,  HIGH, HIGH, HIGH, HIGH }, // 1
  { LOW,  LOW,  HIGH, LOW,  LOW,  HIGH, LOW  }, // 2
  { LOW,  LOW,  LOW,  LOW,  HIGH, HIGH, LOW  }, // 3
  { HIGH, LOW,  LOW,  HIGH, HIGH, LOW,  LOW  }, // 4
  { LOW,  HIGH, LOW,  LOW,  HIGH, LOW,  LOW  }, // 5
  { LOW,  HIGH, LOW,  LOW,  LOW,  LOW,  LOW  }, // 6
  { LOW,  LOW,  LOW,  HIGH, HIGH, HIGH, HIGH }, // 7
  { LOW,  LOW,  LOW,  LOW,  LOW,  LOW,  LOW  }, // 8
  { LOW,  LOW,  LOW,  HIGH, HIGH, LOW,  LOW  }  // 9
};

void setupDisplayPins() {
  for (int i = 0; i <= 6; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  for (int i = 0; i <= 3; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
}

void display(int mode, int phrase) {
  int ones = (phrase%10);
  int tens = ((phrase/10)%10);
  int hundreds = ((phrase/100)%10);

  displayDigit(1, mode);
  delay(1);
  displayDigit(2, hundreds);
  delay(1);
  displayDigit(3, tens);
  delay(1);
  displayDigit(3, ones);
}

void displayDigit(int digit, int character) {
  for (int i = 1; i <= 4; i++) {
    if (i == digit) {
      digitalWrite(digitPins[digit], HIGH);
    } else {
      digitalWrite(digitPins[digit], LOW);
    }
    displayCharacter(character);
  }
}

void displayCharacter(int character) {
  for (int i = 0; i < 7; i++) {
    int pin = segmentPins[i];
    int signal = characters[character][i];
    digitalWrite(pin, signal);
  }
}
