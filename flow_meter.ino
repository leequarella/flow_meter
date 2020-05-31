int flowPin1 = 2;    //This is the input pin on the Arduino
int flowPin2 = 3;    //This is the input pin on the Arduino

volatile int totalPulses1 = 0; //volatile to ensure updates correctly during interrupt
volatile int totalPulses2 = 0;
int loopCount;
int oldPulse2 = 0;

void setup() {
  Serial.begin(9600);
  //pinMode(flowPin1, INPUT);
  pinMode(flowPin2, INPUT);

  //attachInterrupt(digitalPinToInterrupt(flowPin1), Flow, CHANGE);  //Configures interrupt 0 (pin 2 on the Arduino Uno) 
  attachInterrupt(digitalPinToInterrupt(flowPin2), Flow2, CHANGE);  //Configures interrupt 1 (pin 3 on the Arduino Uno) 
}

void loop() {
  if(loopCount > 70){
    loopCount = 0;
    Serial.println(".");

  } else {
    loopCount++;
    Serial.print(".");
  }

  if(oldPulse2 != totalPulses2) {
    Serial.println("");
    Serial.println((String)"Pulse from pin" + flowPin2 + "."); 
    int diff = totalPulses2 - oldPulse2;
    Serial.println((String)"Difference: " + diff);
    Serial.println((String)"New Total: " + totalPulses2);
    oldPulse2 = totalPulses2;
  }
  delay (30);
}
 
void Flow()
{
  totalPulses1++; 
  Serial.println("");
  Serial.println((String)"Flow Pin 1: " + totalPulses1);
}

void Flow2()
{
  totalPulses2++; 
  //Serial.println("");
  //Serial.println((String)"Flow Pin 2: " + totalPulses2);
}
