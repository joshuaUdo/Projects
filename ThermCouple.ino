#include "max6675.h"

int SO_PIN = 4;  
int CS_PIN = 5;  
int SCK_PIN = 6; 

MAX6675 thermocouple(SCK_PIN, CS_PIN, SO_PIN);

void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {
  //Celcuis
  Serial.print("Temperature: ");
  Serial.print(thermocouple.readCelsius());
  Serial.print("C ");

  //Fahrenheit
  Serial.print(thermocouple.readFahrenheit());
  Serial.println("F ");

  delay(1000);
}
