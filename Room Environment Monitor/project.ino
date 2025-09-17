

#include "DHT.h" // Requires the DHT library to be installed in your Arduino IDE

#include <LiquidCrystal.h>

// The pin to which the DHT11 data pin is connected
#define DHTPIN 2


#define DHTTYPE DHT11

// PWM pins connected to the RBG of the diode
#define BLUE 3
#define GREEN 5
#define RED 6

// Initializing the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

// The numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);



void setup() {
  // Serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("DHT11 Humidity and Temperature Sensor");

  // nitializations
  dht.begin();
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);

  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD to test
  lcd.print("Hello, World!");
}

void loop() {
  // Waiting a few seconds between measurements
  delay(5000);

  // Read humidity and temperature
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again)
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print temperature and humidity to the serial monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");

  // Different LED color based on the temperature
  if (t > 23.89){
    if (t > 25.56){
        analogWrite(RED, 255);
    } else {
      analogWrite(RED, 255);
      analogWrite(GREEN, 255);
    }
  } else {
    analogWrite(GREEN, 255);
  }

  // Display Temperature in C
  lcd.setCursor(0, 0);
  lcd.print("Temp         C  ");
  lcd.setCursor(6, 0);
  // Display Temperature in C
  lcd.print(t);


}
