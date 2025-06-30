#include <Adafruit_NeoPixel.h>
#define DISPLAY 6
#define PIXELS 64

#define LEFT 3
#define RIGHT 4

Adafruit_NeoPixel strip(PIXELS, DISPLAY, NEO_GRB + NEO_KHZ800);

unsigned long lastmove = 0;
const int moveinterval = 400;

struct Point {
  int x;
  int y;
};

Point snake[64];
int snakeLenght = 3;

int dx = 1;
int dy = 0;

int foodX, foodY;
unsigned long lastFoodTime;
const unsigned long foodDuration = 5000;

int getPixelIndex(int x, int y) {
  if (y % 2 == 0) {
    return y * 8 + x;
  } else {  //y % 2 != 0
    return y * 8 + (7 - x);
  }
}

void moveSnake() {
  for (int i = snakeLenght - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0].x += dx;
  snake[0].y += dy;

  if (snake[0].x > 7) snake[0].x = 0;
  if (snake[0].x < 0) snake[0].x = 7;
  if (snake[0].y > 7) snake[0].y = 0;
  if (snake[0].y < 0) snake[0].y = 7;

  strip.clear();

  //Zeichne die Schlange
  for (int i = 0; i < snakeLenght; i++) {
    int index = getPixelIndex(snake[i].x, snake[i].y);
    strip.setPixelColor(index, strip.Color(0, 255, 0));

    int foodIndex = getPixelIndex(foodX, foodY);
    strip.setPixelColor(foodIndex, strip.Color(255, 255, 0));
  }


  strip.show();
}

void spawnPoint() {
  snake[0] = { 3, 4 };  //Head
  snake[1] = { 2, 4 };  //Body
  snake[2] = { 1, 4 };  //Tail
}

void placeFood() {
  int foodx, foody;
  bool valid = false;

  while (!valid) {
    foodx = random(0, 8);
    foody = random(0, 8);

    valid = true;

    for (int i = 0; i < snakeLenght; i++) {
      if (foodx == snake[i].x && foody == snake[i].y) {
        valid = false;
        break;
      }
    }
  }
  foodX = foodx;
  foodY = foody;
  lastFoodTime = millis();

  int foodIndex = getPixelIndex(foodX, foody);
  strip.setPixelColor(foodIndex, strip.Color(255, 255, 0));
  strip.show();
}
// void collision() {
// }

// void Left_Button(){

// }

// void Right_Button(){

// }

// void button_function(){  ???

// }


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);

  strip.begin();
  strip.clear();
  strip.setBrightness(50);
  strip.show();

  spawnPoint();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();
  if (now - lastmove >= moveinterval) {
    moveSnake();
    lastmove = now;
  }

  if (millis() - lastFoodTime >= foodDuration) {
    placeFood();
  }
}
