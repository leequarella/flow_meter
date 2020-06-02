int flowPin = 2;
int segmentPins[7] = {4, 8, 12, 10, 9, 5, 13};
int digitPins[4] = {A5, 6, 7, 3};
int modeButtonPin = A0;
int hundredsButton = A1;
int tensButton = A2;
int onesButton = A3;

volatile int pulse = 0;
int loopCount;
int totalGallons = 0;
int currentMode = 1;
int shutoffGallons = 50;
bool pulseDetected = false;

//button debouncing
unsigned long lastModeChangeTime = 0;
unsigned long debounceModeChangeDelay = 500;
unsigned long debounceGallonsChangeDelay = 200;
unsigned long lastGallonsChangeTime = 0;

void setup() {
  setupDisplayPins();

  pinMode(flowPin, INPUT);
  pinMode(hundredsButton, INPUT);
  pinMode(tensButton, INPUT);
  pinMode(onesButton, INPUT);
  pinMode(modeButtonPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(flowPin), Flow, RISING);  //Configures interrupt 1 (pin 3 on the Arduino Uno) 
}

void loop() {
  detectPulse();
  render();
  pollGallonButtons();
  checkModeChange();

  //interrupts();
  delay (7);
  //noInterrupts();
}

void detectPulse() {
  if(pulseDetected) {
    pulseDetected = false;
    totalGallons++;
  }
}

void render() {
  if (currentMode == 1) {
    display(currentMode, shutoffGallons);
  } else {
    display(currentMode, totalGallons);
  }
}

void checkModeChange() {
  if ((millis() - lastModeChangeTime) > debounceModeChangeDelay) {
    int buttonState = digitalRead(modeButtonPin);
    if (buttonState == HIGH) {
      lastModeChangeTime = millis();
      changeMode();
    }
  }
}

void changeMode() {
  if (currentMode == 1) {
    currentMode = 2;
  } else {
    currentMode = 1;
  }
}

void pollGallonButtons() {
  if((millis() - lastGallonsChangeTime) > debounceGallonsChangeDelay) {

    if(digitalRead(hundredsButton) == HIGH){
      shutoffGallons += 100;
      lastGallonsChangeTime = millis();
    } else if ( digitalRead(tensButton) == HIGH ) {
      shutoffGallons += 10;
      lastGallonsChangeTime = millis();
    } else if ( digitalRead(onesButton) == HIGH ) {
      shutoffGallons += 1;
      lastGallonsChangeTime = millis();
    }

    if (shutoffGallons > 999) {
      shutoffGallons = 0;
    }
  }
}

void Flow()
{
  pulseDetected = true;
}
