#include <Adafruit_NeoPixel.h>
#define DISPLAY 6
#define PIXELS 64

#define LEFT 3
#define RIGHT 4
#define POWER 5

Adafruit_NeoPixel strip(PIXELS, DISPLAY, NEO_GRB + NEO_KHZ800);

unsigned long lastmove = 0;
const int moveinterval = 400;

unsigned long lastLeftPress = 0;
unsigned long lastRightPress = 0;

bool lastLeftState = HIGH;
bool lastRightState = HIGH;
const unsigned long debounceDelay = 400;

bool powerState = false;
unsigned long powerHoldStart = 0;

bool gameOver = false;
bool gameOverHandled = false;
unsigned long gameOverTime = 0;

struct Point {
  int x;
  int y;
};

Point snake[64];
int snakeLength = 3;

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
  for (int i = snakeLength - 1; i > 0; i--) {
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
  for (int i = 0; i < snakeLength; i++) {
    int index = getPixelIndex(snake[i].x, snake[i].y);
    strip.setPixelColor(index, strip.Color(0, 255, 0));
  }

  int foodIndex = getPixelIndex(foodX, foodY);
  strip.setPixelColor(foodIndex, strip.Color(255, 255, 0));

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

    for (int i = 0; i < snakeLength; i++) {
      if (foodx == snake[i].x && foody == snake[i].y) {
        valid = false;
        break;
      }
    }
  }

  foodX = foodx;
  foodY = foody;
  lastFoodTime = millis();

  int foodIndex = getPixelIndex(foodX, foodY);
  strip.setPixelColor(foodIndex, strip.Color(255, 255, 0));
  strip.show();
}

void eatFood() {
  if (snake[0].x == foodX && snake[0].y == foodY) {
    snakeLength++;
    placeFood();
  }
}

void collision() {
  for (int i = 1; i < snakeLength; i++) {
    if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
      gameOver = true;
      break;
    }
  }
}

void drawExplosionAt(int centerX, int centerY) {
  for (int radius = 0; radius <= 4; radius++) {
    for (int dx = -radius; dx <= radius; dx++) {
      for (int dy = -radius; dy <= radius; dy++) {
        int x = centerX + dx;
        int y = centerY + dy;
        if (abs(dx) == radius || abs(dy) == radius) {
          if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            int index = getPixelIndex(x, y);
            strip.setPixelColor(index, strip.Color(255, 50, 0));  // Orange-red
          }
        }
      }
    }

    strip.show();
    delay(100);
    strip.clear();
  }
  
  strip.clear();
  strip.show();
}

void Left_Button() {
  if (dx == 1 && dy == 0) {
    dx = 0;
    dy = -1;
  }
  // If moving up, turn left
  else if (dx == 0 && dy == -1) {
    dx = -1;
    dy = 0;
  }
  // If moving left, turn down
  else if (dx == -1 && dy == 0) {
    dx = 0;
    dy = 1;
  }
  // If moving down, turn right
  else if (dx == 0 && dy == 1) {
    dx = 1;
    dy = 0;
  }
}
void Right_Button() {
  if (dx == 1 && dy == 0) {
    dx = 0;
    dy = 1;
  }
  // If moving down, turn left
  else if (dx == 0 && dy == 1) {
    dx = -1;
    dy = 0;
  }
  // If moving left, turn up
  else if (dx == -1 && dy == 0) {
    dx = 0;
    dy = -1;
  }
  // If moving up, turn rightz
  else if (dx == 0 && dy == -1) {
    dx = 1;
    dy = 0;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(POWER, INPUT_PULLUP);

  strip.begin();
  strip.clear();
  strip.setBrightness(50);
  strip.show();

  spawnPoint();
  // placefood();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long now = millis();

  if (digitalRead(POWER) == LOW) {
    if (powerHoldStart == 0) {
      powerHoldStart = now;
    } else if (now - powerHoldStart > 2000) {
      powerState = !powerState;
      powerHoldStart = 0;
      delay(1500);

      if (powerState) {
        spawnPoint();
        placeFood();
        snakeLength = 3;
        gameOver = false;
        gameOverHandled = false;
      } else {
        strip.clear();
        strip.show();
      }
    }
  } else {
    powerHoldStart = 0;
  }

  if (!powerState) return;

  if (gameOver && !gameOverHandled) {
    drawExplosionAt(snake[0].x , snake[0].y);
    gameOverHandled = true;
    gameOverTime = now;
    return;
  }

  if (gameOver && gameOverHandled && (now - gameOverTime >= 3000)) {
  spawnPoint();
  placeFood();
  dx = 1;
  dy = 0;
  snakeLength = 3;
  gameOver = false;
  gameOverHandled = false;
  return;
}

  if (!powerState) return;

  if (now - lastmove >= moveinterval) {
    moveSnake();
    collision();
    lastmove = now;
  }

  bool currentLeftState = digitalRead(LEFT);
  if (lastLeftState == HIGH && currentLeftState == LOW && (now - lastLeftPress > debounceDelay)) {
    Serial.println("Left button pressed!");
    Left_Button();
    lastLeftPress = now;
  }
  lastLeftState = currentLeftState;

  bool currentRightState = digitalRead(RIGHT);
  if (lastRightState == HIGH && currentRightState == LOW && (now - lastRightPress > debounceDelay)) {
    Serial.println("Right button pressed!");
    Right_Button();
    lastRightPress = now;
  }
  lastRightState = currentRightState;

  if (millis() - lastFoodTime >= foodDuration) {
    placeFood();
  }
  eatFood();
}
