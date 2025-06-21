#include <Adafruit_NeoPixel.h>

#define DO_PIN 6
#define NUMPIXELS 300

#define PROX_SENSOR_1 4
#define PROX_SENSOR_2 5

Adafruit_NeoPixel strip(NUMPIXELS, DO_PIN, NEO_GRB + NEO_KHZ800);

const int segmentLength = 20;
int position = 0;
int colorIndex = 0;

uint32_t colors[] = {
  strip.Color(255, 0, 0),     // Red
  strip.Color(255, 128, 0),   // Orange
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 0, 255)      // Blue
};

const int numColors = sizeof(colors) / sizeof(colors[0]);

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
    colorAnimation();
  } else {
    strip.clear();
    strip.show();
  }
}

void colorAnimation() {
  strip.clear();

  for (int i = 0; i < segmentLength; i++) {
    int pixelIndex = (position + i) % NUMPIXELS;
    strip.setPixelColor(pixelIndex, colors[colorIndex]);
  }

  strip.show();
  delay(20);

  
  position++;

  if (position >= NUMPIXELS) {
    position = 0;
    colorIndex++;
    if (colorIndex >= numColors) {
      colorIndex = 0;
    }
  }
}
