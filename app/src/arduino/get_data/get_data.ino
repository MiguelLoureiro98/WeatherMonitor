#include <Arduino.h>
#include "DHT11.h"

uint8_t humidity_pin = 4;
uint8_t light_pin = A2;

double Ts = 2.0 * 1000.0;
double time = 0.0;

DHT11 sensor(humidity_pin);

void setup() {

  Serial.begin(9600);
  //Serial.println("Light (lux)");

  pinMode(humidity_pin, INPUT);

}

void loop() {
  
  double current_time = millis();

  if(current_time - time >= Ts){

    int temperature = 0;
    int humidity = 0;

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    int result = sensor.readTemperatureHumidity(temperature, humidity);

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (result == 0) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    } else {
        // Print error message based on the error code.
        Serial.println(DHT11::getErrorString(result));
    }

    //temperature = analogRead(A0);
    //temperature = sensor.readTemperature();
    //Serial.print("Temperature: ");
    //Serial.print(temperature);
    //Serial.println(" °C");

    time = current_time;

  }

}
