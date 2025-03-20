#include <SPI.h>
#include "Adafruit_MAX6675.h"

#define CLK 13
#define CS 10
#define DO 12

Adafruit_MAX6675 thermocouple(CLK, CS, DO);

void setup(){
  Serial.begin(115200);
  delay(1000);
  Serial.print("Start...");
}
void loop(){
  float tempurature = thermocouple.readCelsius();
  Serial.print("Tempurature: ");
  Serial.print(tempurature);
  Serial.println("C");

  delay(1000);
}
