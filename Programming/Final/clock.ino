int sevenBinary[7];
int binaryLED[7] = {43, 41, 39, 37, 35, 33, 31};


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

int[] num2Binary(int num) {
  int sevenBitBinary[7];
  for(int i = 0; i < 7; i++) {
    sevenBitBinary[i] = bitRead(num, i);
  }

  return sevenBitBinary;
}
