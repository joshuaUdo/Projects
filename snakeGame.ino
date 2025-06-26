#include <Adafruit_Neopixel.h>
#define DISPLAY 6
#define PIXELS 64

#define LEFT 3
#define RIGHT 4

Adafruit_NeoPixel strip(PIXELS, PIN, NEO_GRB + NEO_KHZ800);

void Left_Button(){

}

void Right_Button(){

}

void checkButton(){

}

void moveSnake(){

}

void placeFood(){

}

void collision(){
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
