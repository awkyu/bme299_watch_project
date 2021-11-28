//this program reads from the accelerometer (A0,A2,A4) and sends it over serial to the PC
//author Alexander Kyu

//Define which pins correspond to the Z-, Y-, and X- channels on the accelerometer
int zPin = A11;
int yPin = A10;
int xPin = A9;




void accelerometerProgram() {
  //function to record data and check for certain other gestures/conditions
  PrintSerialData();
  //count the number of times data is recorded -- used for keeping correct array of last smoothVar number of data points
  count = count + 1;
}

void CheckThresholdHandUp(){
  //check if hand is in the right position for it to be considered in the "visible" position
  if (ZData > 0.60 && ZData < 1.1 && YData > -.35 && YData < .5 && XData > -.55 && XData < 0) {
    //1Serial.println("Watch Up");
    watchUp = true;
  } else {
    watchUp = false;
  }
}

void CheckThresholdDoubleTap() {
  //check if movement is in threshold for tap and that the last tap was longer than .2 seconds ago to prevent misreading data(double counting a tap)
  if ((abs(ZData - allZData[(count - 1)%smoothVar]) > .12) && (abs(XData - allXData[(count - 1)%smoothVar]) < .04) && (abs(YData - allYData[(count - 1)%smoothVar]) < .04) && (abs(lastTap - lastTap2) > 200000)) {
    tapTimeArr[tapTimeCount%tapTimeArrSize] = micros();
    tapTimeCount = tapTimeCount + 1;
    lastTap = micros();
    //Serial.println("Single Tap");
    //check if the last tap was less than .5 seconds ago, if so, then its considered a double tap
    if (abs(tapTimeArr[0] - tapTimeArr[1]) < 500000) {
      //Serial.println("Double Tap"); 
      mode = mode + 1;
      analogWrite(modeLED[0],0);
      analogWrite(modeLED[1],0);
      analogWrite(modeLED[2],0);
      analogWrite(modeLED[3],0);
      if (mode == 4) {
        mode = 0;
      }
    }
  }
  lastTap2 = micros();
}



void PrintSerialData(){
  //read data from each pin
  zData = analogRead(zPin);
  yData = analogRead(yPin);
  xData = analogRead(xPin);
  //convert read data to units of gravity
  ZData = -1 * (zData - zeroConst) / numbG; ///numbG - zeroConst); 
  YData = (yData - zeroConst) / numbG; ///numbG - zeroConst); 
  XData = -1 * (xData - zeroConst) / numbG; ///numbG - zeroConst); 
  //record new data into array of last smoothVar number of data points
  allZData[count%smoothVar] = ZData;
  allYData[count%smoothVar] = YData;
  allXData[count%smoothVar] = XData;
  //reset these variables as zero for iterative summation
  zD = 0;
  yD = 0;
  xD = 0;
  //find average of the last smoothVar number of points and smooth new data point with this average
  for (int i = 0; i < smoothVar; i++) {
    zD = zD + allZData[i];
    yD = yD + allYData[i];
    xD = xD + allXData[i];
  }
  //smoothed data point
  ZData = (ZData + zD) / (1 + smoothVar);
  YData = (YData + yD) / (1 + smoothVar);
  XData = (XData + xD) / (1 + smoothVar);


  //combine data into one string
  dataString = String(XData) + ", " + String(YData) + ", " + String(ZData);// + "," + String(ZData + YData + xData); // + ", " + String(xInitial) + ", " + String(yInitial) + ", " + String(zInitial);

  //check if hand is at visible level and check for double tap
  CheckThresholdHandUp();
  CheckThresholdDoubleTap();

  //only print data once ever 20 milliseconds  
  printSlow = micros();
  if (printSlow - printSlow2 > 1000000) {
    //print data to serial terminal
    Serial.println(dataString);
    printSlow2 = micros();
  }


  

}
