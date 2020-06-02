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
  { HIGH,  HIGH,  HIGH,  HIGH, HIGH,  HIGH,  LOW  }, // 0
  { LOW, HIGH,  HIGH,  LOW, LOW, LOW, LOW }, // 1
  { HIGH,  HIGH,  LOW, HIGH,  HIGH,  LOW, HIGH  }, // 2
  { HIGH,  HIGH,  HIGH,  HIGH,  LOW, LOW, HIGH  }, // 3
  { LOW, HIGH,  HIGH,  LOW, LOW, HIGH,  HIGH  }, // 4
  { HIGH,  LOW, HIGH,  HIGH,  LOW, HIGH,  HIGH  }, // 5
  { HIGH,  LOW, HIGH,  HIGH,  HIGH,  HIGH,  HIGH  }, // 6
  { HIGH,  HIGH,  HIGH,  LOW, LOW, LOW, LOW }, // 7
  { HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH,  HIGH  }, // 8
  { HIGH,  HIGH,  HIGH,  LOW, LOW, HIGH,  HIGH  }  // 9
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
  delay (1);
  if(hundreds > 0) {
    displayDigit(2, hundreds);
    delay (1);
  }
  displayDigit(3, tens);
  delay (1);
  displayDigit(4, ones);
  delay (1);
}

void displayDigit(int digit, int character) {
  for (int i = 0; i < 4; i++) {
    if (i == digit-1) {
      digitalWrite(digitPins[i], LOW);
      displayCharacter(character);
    } else {
      digitalWrite(digitPins[i], HIGH);
    }
  }
}

void displayCharacter(int character) {
  for (int i = 0; i < 7; i++) {
    int pin = segmentPins[i];
    int signal = characters[character][i];
    digitalWrite(pin, signal);
  }
}
