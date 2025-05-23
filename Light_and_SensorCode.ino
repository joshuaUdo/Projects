//HRTC
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 9
int IRSensor = 2;
int LED = 8;

Adafruit_NeoPixel strip(NUMPIXELS, PIN);

void setup(){
  Serial.begin(9600); 
  pinMode(IRSensor, INPUT); 
  pinMode(LED, OUTPUT); 
  strip.setBrightness(255);
  strip.show();
}

void loop(){
  int sensorStatus = digitalRead(IRSensor); 
  if (sensorStatus == 1) {
    digitalWrite(LED, LOW); 
    Serial.println("Motion Ended!"); 
  }
  else {
    digitalWrite(LED, HIGH);
    delay(5000);
    Serial.println("Motion Detected!");

    for (int i = 0; i <NUMPIXELS; i++){
      int r = random();
      int g = random();
      int b = random();

      strip.setPixelColor(i, strip.Color(r, g, b));
      delay(50);
    }
  }
}


