#include <Wire.h>
#include <Adafruit_BMP280.h>

#define BIT_VALUE 8

Adafruit_BMP280 bmp280;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(100);  // Wait for serial port to connect - needed for Leonardo only
  }

  if (!bmp280.begin()) {  // Initialize BMP280
    Serial.println("BMP280 sensor initialization failed!");
    while (1);  // Halt execution if sensor fails to initialize
  }
  Serial.println("Setup complete, device is ready.");
}

int generateTrueRandomNumber() {
  long L1 = analogRead(A1); // Read light sensor
  long L2 = analogRead(A2); // Read wire sensor
  long L3 = (long)bmp280.readPressure(); // Read pressure from BMP280
  long S1 = analogRead(A0); // Read sound sensor

  // Check if any sensor value seems abnormal
  if (L1 < 5 || L2 < 5 || S1 < 5 || L3 == 0) {
    Serial.println("Error: One or more sensor values are out of expected range.");
    return 2;  // Returning 0 to indicate error in random number generation
  }

  if (S1 == 0) {
    S1 = 1;  // Prevent division/modulo by zero
  }

  long Z1 = (L1 * L2) % S1;
  long Z2 = (L2 * L3) % S1;
  long Z3 = (L3 * L1) % S1;

  int Y1 = (Z1 > Z2) ? 1 : 0;
  int Y2 = (Z2 > Z3) ? 1 : 0;

  return Y1 ^ Y2; // Return the XOR of Y1 and Y2
}

int generateNbitNum(int bits) {
  int result = 0;
  for (int i = 0; i < bits; i++) {
    int bit = generateTrueRandomNumber();
    if (bit == 2 && !Serial.available()) {  // Improvised error checking
      Serial.println("Failed to generate random bit due to sensor error.");
      return -1;  // Indicate an error occurred
    }
    result = (result << 1) | bit;
  }
  return result;
}

void loop() {
  if (Serial.available() > 0) {  // Check if there is data available to read
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();  // Clean any whitespace or newline characters

    if (inputString == "number") {
      int randomNumber = generateNbitNum(BIT_VALUE);
      if (randomNumber == -1) {
        Serial.println("Error: Failed to generate valid number.");
      } else {
        // Print the binary format
        Serial.print("Binary: ");
        for (int i = BIT_VALUE - 1; i >= 0; i--) {
          Serial.print((randomNumber >> i) & 1);  // Extract each bit and print
        }

        // Print the decimal equivalent
        Serial.print(" | Decimal: ");
        Serial.println(randomNumber);
      }
    }
  }
}
