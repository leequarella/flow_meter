/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
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

int segmentPins[7] = {3, 4, 5, 6, 7, 8, 9};
int digitPins[4] = {10, 11, 12, 13};

int characters[10][7] = {
  { LOW,  HIGH, LOW, LOW,  HIGH, LOW,  LOW  }, // 0
  { LOW,  LOW,  LOW, HIGH, LOW,  LOW,  LOW  }, // 1
  { HIGH, HIGH, LOW, HIGH, LOW,  HIGH, LOW  }, // 2
  { LOW,  HIGH, LOW, HIGH, LOW,  LOW,  HIGH }, // 3
  { HIGH, LOW,  LOW, HIGH, HIGH, LOW,  LOW  }, // 4
  { LOW,  HIGH, LOW, LOW,  HIGH, LOW,  LOW  }, // 5
  { LOW,  HIGH, LOW, LOW,  LOW,  LOW,  LOW  }, // 6
  { LOW,  LOW,  LOW, HIGH, HIGH, HIGH, HIGH }, // 7
  { LOW,  LOW,  LOW, LOW,  LOW,  LOW,  LOW  }, // 8
  { LOW,  LOW,  LOW, HIGH, HIGH, LOW,  LOW  }  // 9
};

void setupDisplay() {
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
