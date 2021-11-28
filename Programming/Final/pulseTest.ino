int pulsePin = A2;
int pulseLight = 53;
int pulseSignal; 
const int smoothVarPulse = 10;
const int bpmMillis = 2;
double bpm[bpmMillis];
int bpmcounterPulse = 0;
int signalData[smoothVarPulse];
int counterPulse = 0;
int sD;
int beats;
int lastCount1 = 0;
int lastCount2 = 100000;

void setup() {
  // put your setup code here, to run once:
  pinMode(pulseLight,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (abs(lastCount2 - lastCount1) > 200) {
    pulseSignal = analogRead(pulsePin);
    signalData[counterPulse%smoothVarPulse] = pulseSignal;
    sD = 0;
    for (int i = 0; i < smoothVarPulse; i++) {
      sD = sD + signalData[i];
    }
    signalData[counterPulse%smoothVarPulse] = (sD + pulseSignal) / (1 + smoothVarPulse);
    if (signalData[(counterPulse-2)%smoothVarPulse] < signalData[(counterPulse-1)%smoothVarPulse] && signalData[(counterPulse-1)%smoothVarPulse] > signalData[counterPulse%smoothVarPulse]) {
      digitalWrite(pulseLight, HIGH);
      bpm[bpmcounterPulse%bpmMillis] = millis();
      bpmcounterPulse = bpmcounterPulse + 1;
      
      beats = 60.0/(abs(bpm[0] - bpm[1])/1000.0);
    } else {
      digitalWrite(pulseLight, LOW);
    }
    
    lastCount2 = millis();
    //Serial.println(signalData[counterPulse%smoothVarPulse]);
    Serial.println(String(beats));
    counterPulse = counterPulse + 1;
  }
  lastCount1 = millis();
  
  
  
}
