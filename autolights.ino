const int LDR_PIN = A0;  
const int TRANSISTOR_PIN = 7;  
float THRESHOLD = 500; 

void setup() {
    pinMode(TRANSISTOR_PIN, OUTPUT);
    pinMode(LDR_PIN, INPUT);
    Serial.begin(9600);
}

void loop() {
    int lightValue = analogRead(LDR_PIN); 

    Serial.print("Brightness: ");
    Serial.println(lightValue);

    if (lightValue < THRESHOLD) {  
        digitalWrite(TRANSISTOR_PIN, HIGH);
        Serial.println("It's dark! Turning ON the LEDs.");
    } else {
        digitalWrite(TRANSISTOR_PIN, LOW);
        Serial.println("It's bright! Turning OFF the LEDs.");
    }

    delay(500);
}
