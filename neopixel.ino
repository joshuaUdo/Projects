#include <Adafruit_NeoPixel.h>

#define PIN 6 
#define NUMPIXELS 150

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin(); 
  strip.setBrightness(255);
  strip.show();  
}

void loop() {
  for (int i = 0; i < NUMPIXELS; i++) {
    int r = 0;  // No red
    int g = random(150, 255);  
    int b = random(50, 150); 

    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
  delay(50);
}

  /*for(int hue = 0; hue < 65536; hue += 256) {
   strip.fill(strip.ColorHSV(hue));
   strip.show();
   delay(50);
   }*/

