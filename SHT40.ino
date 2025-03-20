#include <Wire.h>
#include <Adafruit_SHT4x.h>

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

void setup(){
  Serial.begin(115200);
  delay(1000);
  Wire.begin();

  if(!sht4.begin()){
    Serial.println("SHT40 not detected...");
    while(1);
  }
  Serial.print("SHT40 initialized...");
}

void loop(){
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);

  Serial.print("Tempurature: ");
  Serial.print(temp.tempurature);
  Serial.print("Humdity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(2000);
}
