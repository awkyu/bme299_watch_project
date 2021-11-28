double photometerSignal;
int photoPin = A0;


void photometerProgram() {
  photometerSignal = analogRead(photoPin);
  //Serial.println(maxBrightness);
  maxBrightness = 250.0*(photometerSignal/2250.0);
  if (maxBrightness < 150 && watchUp) {
    for (int i = 0; i < 7; i++) {
      analogWrite(binaryLED[i],0);
    }
    delay(500);
    for (int i = 0; i < 7; i++) {
      if (sevenBitBinaryHours[i] == 1) {
        writeLED = maxBrightness;
      } else {
        writeLED = 0;
      }
      analogWrite(binaryLED[i],writeLED);
    }
    delay(500);
    for (int i = 0; i < 7; i++) {
      if (sevenBitBinaryMinutes[i] == 1) {
        writeLED = maxBrightness;
      } else {
        writeLED = 0;
      }
      analogWrite(binaryLED[i],writeLED);
    }
    delay(500);
    for (int i = 0; i < 7; i++) {
      if (sevenBitBinarySeconds[i] == 1) {
        writeLED = maxBrightness;
      } else {
        writeLED = 0;
      }
      analogWrite(binaryLED[i],writeLED);
    }
    delay(500);
  }
}
