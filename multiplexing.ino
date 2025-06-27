 int segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};

int digitPins[] = {9, 10};

 byte numberPatterns[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};


void displayDigit(int digit, int number) {
    digitalWrite(digitPins[digit], LOW); 
    for (int i = 0; i < 8; i++) {
        digitalWrite(segmentPins[i], (numberPatterns[number] >> i) & 1);
    }
    delay(1000);  
    digitalWrite(digitPins[digit], HIGH); 
}

void setup() {
    for (int i = 0; i < 8; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }
    for (int i = 0; i < 2; i++) {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], HIGH); 
    }
}

void loop() {
    int time = 59;  

    while (time >= 0) {
        int ones = time % 10;
        int tens = (time / 10) % 10;

        
        displayDigit(0, tens);
        displayDigit(1, ones);

        delay(1000); 
        time--;  
    }
}
