#include <Adafruit_NeoPixel.h>

#define DO_PIN 6
#define NUMPIXELS 200

#define PROX_SENSOR_1 4
#define PROX_SENSOR_2 5

Adafruit_NeoPixel strip(NUMPIXELS, DO_PIN, NEO_GRB + NEO_KHZ800);

const int segmentLength = 5;
int position = 0;
int direction = 1;

void setup() {
  Serial.begin(9600);
  pinMode(PROX_SENSOR_1, INPUT);
  pinMode(PROX_SENSOR_2, INPUT);
  strip.begin();
  strip.setBrightness(200);
  strip.clear();
  strip.show();
}

void loop() {
  int sensor1 = digitalRead(PROX_SENSOR_1);
  int sensor2 = digitalRead(PROX_SENSOR_2);

  if (sensor1 == HIGH || sensor2 == HIGH) {
    animatedSnake();
  } else {
    strip.clear();
    strip.show();
  }
}

void animatedSnake() {
  strip.clear();

  for (int i = 0; i < segmentLength; i++) {
    int pixelIndex = (position + i) % NUMPIXELS;

    // Pulsing brightness using sine wave
    float brightness = 0.6 + 0.4 * sin((millis() / 100.0) + i);

    // Use HSV for a rainbow gradient with slight hue shift per pixel
    int hue = (millis() / 5 + i * 20) % 65536;
    uint32_t color = strip.gamma32(strip.ColorHSV(hue, 255, 255 * brightness));

    strip.setPixelColor(pixelIndex, color);
  }

  strip.show();
  delay(30);

  // Move snake with bounce effect
  position += direction;
  if (position <= 0 || position >= NUMPIXELS - segmentLength) {
    direction *= -1;
  }
}
