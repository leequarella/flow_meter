int flowPin = 2;    //This is the input pin on the Arduino

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

  setupDisplay();
  pinMode(flowPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(flowPin), Flow, RISING);  //Configures interrupt 1 (pin 3 on the Arduino Uno) 
}

void loop() {
  heartBeat();
  detectPulse();
  render();

  interrupts();
  delay (1000);
  noInterrupts();
}

void detectPulse() {
  if(pulseDetected) {
    pulseDetected = false;
    totalGallons++;
    Serial.println("");
    Serial.println((String)"Total Gallons: " + totalGallons);
  }
}

void render(){
  if (currentMode == 1) {
    display(currentMode, shutoffGallons);
  } else {
    display(currentMode, totalGallons);
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

void Flow()
{
  pulseDetected = true;
}
