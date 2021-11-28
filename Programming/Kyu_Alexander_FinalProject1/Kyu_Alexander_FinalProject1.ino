int sevenBitBinaryHours[7];
int sevenBitBinaryMinutes[7];
int sevenBitBinarySeconds[7];
int binaryLED[7] = {43, 41, 39, 37, 35, 33, 31};
int modeLED[4] = {45, 47, 49, 51};
int hoursStart = 15;
int minutesStart = 43;
int hours;
int minutes;
int seconds = 0;





int pulsePin = A2;
int pulseLight = 53;
int sevenBinaryPulse[7];

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





int lastTap = 0;
int lastTap2 = 1000000;
//string for outputting the x,y, and z data
String dataString;
//variables used in converting the raw x,y,z data into units of gravity
int zeroConst = 4096/2;
double numbG = 400;


//the number of data points used for smoothing the data
const int smoothVar = 15;
//used for keeping track of the times for tapping -- used for detecting tapping and double taps
const int tapTimeArrSize = 2;
//Define variables for the Z-, Y-, and X- data
int zData;
int yData;
int xData;
//Variables for smoothed data -- look below for how they are calculated from zData, yData, and xData
double ZData;
double YData;
double XData;
//arrays of recent data points -- useful for smoothing and for checking for recent jumps in data
double allXData[smoothVar];
double allYData[smoothVar];
double allZData[smoothVar];
//initialize count variable to keep track of which array index is needed -- used for the arrays above
int count = 0;
//variables used in smoothing the curve
double zD = 0;
double yD = 0;
double xD = 0;
//two time variables to make data print only after a certain time period (20 milliseconds, look below)
int printSlow = micros();
int printSlow2 = 0;
//variables to keep track of tapping
int tapTimeArr[tapTimeArrSize] = {1000000, 0};
int tapTimeCount = 0;


int maxBrightness = 255;



int mode = 0;
boolean watchUp = false;
int writeLED;



void setup() {
  // put your setup code here, to run once:
  //setup serial for printing data
  Serial.begin(9600); 
  //makes data 12 bit (0-4095) instead of 10 bit (0-1023)
  analogReadResolution(12);
  pinMode(pulseLight,OUTPUT);
  for(int i = 0; i < 7; i++) {
    pinMode(binaryLED[i], OUTPUT);
  }
  for(int i = 0; i < 4; i++) {
    pinMode(modeLED[i], OUTPUT);
  }
  
}




void loop() {
  // put your main code here, to run repeatedly:
  accelerometerProgram();
  pulseProgram();
  clockProgram();
  photometerProgram();

  if (watchUp) {
    displayProgram();
  } else {
    for (int i = 0; i < 7; i++) {
      analogWrite(binaryLED[i],0);
    }
    //digitalWrite(binaryLED[1], HIGH);
    for (int i = 0; i < 4; i++) {
      analogWrite(modeLED[i],0);
    }
  }
}



void clockProgram() {
  seconds = (millis()/1000)%60;
  minutes = (((millis()/1000)/60) + minutesStart)%60;
  hours = (((millis()/1000)/3600) + hoursStart)%24;
  num2BinaryHour(hours);
  num2BinaryMinutes(minutes);
  num2BinarySeconds(seconds);
}

void num2BinaryHour(int num) {
  for(int i = 0; i < 7; i++) {
    sevenBitBinaryHours[i] = bitRead(num, i);
  }
}
void num2BinaryMinutes(int num) {
  for(int i = 0; i < 7; i++) {
    sevenBitBinaryMinutes[i] = bitRead(num, i);
  }
}
void num2BinarySeconds(int num) {
  for(int i = 0; i < 7; i++) {
    sevenBitBinarySeconds[i] = bitRead(num, i);
  }
}

void displayProgram() {
  switch(mode) {
    case 0:
      for (int i = 0; i < 7; i++) {
        if (sevenBitBinaryHours[i] == 1) {
          writeLED = maxBrightness;
        } else {
          writeLED = 0;
        }
        analogWrite(binaryLED[i],writeLED);
      }
      break;
    case 1:
      for (int i = 0; i < 7; i++) {
        if (sevenBitBinaryMinutes[i] == 1) {
          writeLED = maxBrightness;
        } else {
          writeLED = 0;
        }
        analogWrite(binaryLED[i],writeLED);
      }
      break;
    case 2:
      for (int i = 0; i < 7; i++) {
        if (sevenBitBinarySeconds[i] == 1) {
          writeLED = maxBrightness;
        } else {
          writeLED = 0;
        }
        analogWrite(binaryLED[i],writeLED);
      }
      break;
    case 3:
      for (int i = 0; i < 7; i++) {
        if (sevenBinaryPulse[i] == 1) {
          writeLED = maxBrightness;
        } else {
          writeLED = 0;
        }
        analogWrite(binaryLED[i],writeLED);
      }
      break;
  }
  analogWrite(modeLED[mode],maxBrightness);

  
}
