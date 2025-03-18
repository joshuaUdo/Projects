// Define segment pins (A to G + DP)
int segmentPins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// Number patterns for a common cathode display (HIGH = ON)
byte numbers[10][8] = {
 //C,D,E,B,A,F,G 
  {1,1,1,1,1,1,0,0}, // 0
  {1,0,0,1,0,0,0,0}, // 1
  {0,1,1,1,1,0,1,0}, // 2
  {1,1,0,1,1,0,1,0}, // 3
  {1,0,0,1,0,1,1,0}, // 4
  {1,1,0,0,1,1,1,0}, // 5
  {1,1,1,0,1,1,1,0}, // 6
  {1,0,0,1,1,0,0,0}, // 7
  {1,1,1,1,1,1,1,0}, // 8
  {1,0,0,1,1,1,1,0}  // 9
};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void displayNumber(int num) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], numbers[num][i]);
  }
}

void loop() {
  for (int num = 0; num <= 9; num++) { 
    displayNumber(num);
    delay(2000); 
  }
}
