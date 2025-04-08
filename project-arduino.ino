#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with I2C address 0x27 (common for I2C LCDs)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the sensor pin
const int sensorPin = A4; // Analog pin for the air quality sensor

void setup() {
  // Initialize the LCD
  lcd.begin(16,2);
  lcd.backlight(); // Turn on the backlight
  Serial.begin(9600); // Start serial communication
}

void loop() {
  // Read the sensor value
  int sensorValue = analogRead(sensorPin);
  
  // Convert the sensor value to PPM (this is a placeholder; adjust as needed)
  int ppmValue = map(sensorValue, 0, 1023, 0, 500); // Example mapping
  
  // Determine air quality index
  String airQualityIndex = getAirQualityIndex(ppmValue);
  
  // Display the values on the LCD
  lcd.clear(); // Clear the LCD
  lcd.setCursor(0, 0); // Set cursor to the first line
  lcd.print("AQI: " + airQualityIndex); // Display air quality index
  lcd.setCursor(0, 1); // Set cursor to the second line
  lcd.print("PPM: " + String(ppmValue)); // Display PPM value
  
  // Print to Serial Monitor for debugging
  Serial.print("Air Quality: ");
  Serial.print(airQualityIndex);
  Serial.print(" | PPM: ");
  Serial.println(ppmValue);
  
  // Wait for 5 seconds before the next reading
  delay(5000);
}

String getAirQualityIndex(int sensorValue) {
  if (sensorValue < 50) {
    return "Good";
  } else if (sensorValue < 150) {
    return "Moderate";
  } else if (sensorValue < 250) {
    return "Unhealthy";
  } else {
    return "Hazardous";
  }
}