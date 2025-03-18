#define THERMOPIN A0
#define SERIES_RESISTOR 10000  
#define NOMINAL_RESISTANCE 10000 
#define NOMINAL_TEMPERATURE 25.0 + 273.15 
#define BETA_COEFFICIENT 3950 // 
#define SUPPLY_VOLTAGE 5.0
#define ADC_RESOLUTION 1023.0

void setup() {
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(THERMOPIN);
  float voltage = rawValue * SUPPLY_VOLTAGE / ADC_RESOLUTION;

  float resistance = SERIES_RESISTOR * ((1023.0 / rawValue) - 1.0);
  
  float tempK = BETA_COEFFICIENT / (log(resistance / NOMINAL_RESISTANCE) + (BETA_COEFFICIENT / NOMINAL_TEMPERATURE));
  float tempC = tempK - 273.15; 

  Serial.print("Temperature (C): ");
  Serial.println(tempC);

  Serial.print("Tempurature (K): ");
  Serial.println(tempK);
  
  delay(2000); 
}
