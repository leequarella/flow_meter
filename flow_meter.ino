int flowPin = 3;    //This is the input pin on the Arduino

volatile int pulse = 0;
int loopCount;
int totalGallons = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("");
  Serial.println("STARTING");
  pinMode(flowPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(flowPin), Flow, RISING);  //Configures interrupt 1 (pin 3 on the Arduino Uno) 
}

void loop() {
  if(loopCount > 70){
    loopCount = 0;
    Serial.println(".");
  } else {
    loopCount++;
    Serial.print(".");
  }

  if(totalPulses == 1) {
    totalPulses = 0;
    totalGallons++;
    Serial.println("");
    Serial.println((String)"Total Gallons: " + totalGallons);
  }
  interrupts();
  delay (1000); 
  noInterrupts();
}

void Flow()
{
  pulse = 1;
}
