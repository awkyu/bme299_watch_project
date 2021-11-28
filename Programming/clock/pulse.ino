



void num2BinaryPulse(int num) {
  for(int i = 0; i < 7; i++) {
    sevenBinaryPulse[i] = bitRead(num, i);
  }
}


void pulseProgram() {
    if (abs(lastCount2 - lastCount1) > 200) {
    pulseSignal = analogRead(pulsePin);
    signalData[counterPulse%smoothVarPulse] = pulseSignal;
    sD = 0;
    for (int i = 0; i < smoothVarPulse; i++) {
      sD = sD + signalData[i];
    }
    signalData[counterPulse%smoothVarPulse] = (sD + pulseSignal) / (1 + smoothVarPulse);
    if (signalData[(counterPulse-2)%smoothVarPulse] < signalData[(counterPulse-1)%smoothVarPulse] && signalData[(counterPulse-1)%smoothVarPulse] > signalData[counterPulse%smoothVarPulse]) {
      if (mode == 3 && watchUp) {
        analogWrite(pulseLight, maxBrightness);
      }
      bpm[bpmcounterPulse%bpmMillis] = millis();
      bpmcounterPulse = bpmcounterPulse + 1;
      
      beats = 60.0/(abs(bpm[0] - bpm[1])/1000.0);
      num2BinaryPulse(beats);
    } else {
      analogWrite(pulseLight, 0);
    }
    
    lastCount2 = millis();
    counterPulse = counterPulse + 1;

    if (beats >= 140 && beats < 180 && mode == 3 && watchUp){
      for(int i = 0; i < 7; i++) {
        analogWrite(binaryLED[i],255);
        delay(10);
      }
      for(int i = 0; i < 4; i++) {
        analogWrite(modeLED[i],255);
        delay(10);
      }
      analogWrite(pulseLight,255);
      delay(10);
      for(int i = 0; i < 7; i++) {
        analogWrite(binaryLED[i],0);
        delay(10);
      }
      for(int i = 0; i < 4; i++) {
        analogWrite(modeLED[i],0);
        delay(10);
      }
      analogWrite(pulseLight,0);
      delay(10);
   
    }
    //Serial.println(signalData[counterPulse%smoothVarPulse]);
    //Serial.println(String(beats));
    
  }
  lastCount1 = millis();
  
  
}
