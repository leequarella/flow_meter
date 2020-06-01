int flowPin = 2;
//int segmentPins[7] = {3, 4, 5, 6, 7, 8, 9};
//int digitPins[4] = {10, 11, 12, 13};
int segmentPins[7] = {4, 8, 12, 10, 9, 5, 13};
int digitPins[4] = {A5, 6, 7, 3};
int potPin = A0;
int modeButtonPin = A1;
int resetButtonPin = A2;

volatile int pulse = 0;
int loopCount;
int totalGallons = 0;
int currentMode = 1;
int shutoffGallons = 50;
bool pulseDetected = false;

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("STARTING");

  setupDisplayPins();
  pinMode(flowPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(modeButtonPin, INPUT);
  pinMode(resetButtonPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(flowPin), Flow, RISING);  //Configures interrupt 1 (pin 3 on the Arduino Uno) 
}

void loop() {
  //heartBeat();
  //detectPulse();
  render();
  setShutoffGallons();
  checkModeChange();

  //interrupts();
  delay (7);
  //noInterrupts();
}

void detectPulse() {
  if(pulseDetected) {
    pulseDetected = false;
    totalGallons++;
    Serial.println("");
    Serial.println((String)"Total Gallons: " + totalGallons);
  }
}

void render() {
  if (currentMode == 1) {
    //Serial.println((String)"1: " + shutoffGallons);
    display(currentMode, shutoffGallons);
  } else {
    //Serial.println((String)"2: " + totalGallons);
    display(currentMode, totalGallons);
  }
}

void checkModeChange() {
  int buttonState = digitalRead(modeButtonPin);
  if (buttonState == HIGH) {
    changeMode();
  }
}

void changeMode() {
  if (currentMode == 1) {
    currentMode = 2;
  } else {
    currentMode = 1;
  }
}

void heartBeat() {
  if(loopCount > 70){
    loopCount = 0;
    Serial.println(".");

  } else {
    loopCount++;
    Serial.print(".");
  }
}

void setShutoffGallons() {
  int val = analogRead(potPin);
  shutoffGallons = val/3;
}

void Flow()
{
  pulseDetected = true;
}
