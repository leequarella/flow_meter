int flowPin = 3;    //This is the input pin on the Arduino

volatile int totalPulses = 0;
int loopCount;
int oldPulse = 0;

void setup() {
  Serial.begin(9600);
  pinMode(flowPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(flowPin), Flow, CHANGE);  //Configures interrupt 1 (pin 3 on the Arduino Uno) 
}

void loop() {
  if(loopCount > 70){
    loopCount = 0;
    Serial.println(".");

  } else {
    loopCount++;
    Serial.print(".");
  }

  if(oldPulse != totalPulses) {
    int diff = totalPulses - oldPulse;
    oldPulse = totalPulses;
    Serial.println("");
    Serial.println((String)"Pulse from pin" + flowPin + ".");
    Serial.println((String)"Difference: " + diff);
    Serial.println((String)"New Total: " + totalPulses);
  }
  delay (60);
}

void Flow()
{
  totalPulses++;
}
