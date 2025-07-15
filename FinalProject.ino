#include <Wire.h>
#include <Arduino.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Fingerprint.h>

#define fingerPrintSensorTX
#define fingerPrintSensorRX
#define mySerial Serial1

#define displayPin
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SCREEN_ADDRESS 0x3C

#define buzzerPin
#define powerSwitch
#define ledPin

bool powerState = false;
bool dbConnection = false;

//API settings for the supabase connection.
const char* supabaseURL 
const char* supabaseKey

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
uint8_t id;

enum state{
  Register,
  validate
};

void memoryBuffer(){}

void registerFingerPrint(){}

void validateFingerPrint(){}

void fingerPrintLogic(){}

void display(){}

void numberTag(){}

void databaseFunction(){}

void setup(){
  Serial.begin(9600);
  finger.begin(52600); 

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);
}

void loop(){}
