int LDRpin = A0;
int counter = 0;
int LDRvalue = 0;
int formervolt = false;
int segmentpins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

byte numbers[10][8] = {
  {1, 1, 1, 1, 1, 1, 0, 0},
  {1, 0, 0, 1, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 1, 0},
  {1, 1, 0 ,1, 1, 0, 1, 0},
  {1, 0, 0, 1, 0, 1, 1, 0},
  {1, 1, 0, 0, 1, 1, 1, 0},
  {1, 1, 1, 0, 1, 1, 1, 0},
  {1, 0, 0, 1, 1, 0, 0, 0},
  {1, 1, 1, 1, 1, 1 ,1, 0},
  {1, 0, 0, 1, 1, 1, 1, 0}
};  

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++){
    pinMode(segmentpins[i], OUTPUT);
  }
}

void displaynumber (int num){
  for(int i = 0; i < 8; i++){
    digitalWrite(segmentpins[i], numbers[num][i]);
  }
}

void loop() {
  LDRvalue = analogRead(LDRpin);
  float ldrvolt = LDRvalue * 5.0 / 1023;
  Serial.println(ldrvolt);
  delay(1000);

  displaynumber(counter);
  if(ldrvolt < 4.5 && !formervolt){
    counter++;
    if(counter > 9) counter = 0;
    displaynumber(counter);
    formervolt = true;  
  }else if(ldrvolt >= 4.5){
    formervolt = false;
  }
  delay(1000);
}
