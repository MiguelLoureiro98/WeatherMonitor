#include <Arduino.h>
#include <stdint.h>
#include <math.h>
#include "DHT11.h"

double adc_res = 5.0 / 1024.0;

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
  int temperature = 0;
  int humidity = 0;
  int result = 0;
  uint8_t adc_reading = 0;
  double Vout = 0;
  double RL = 0;
  double lux = 0;

  if(current_time - time >= Ts){

    // Attempt to read the temperature and humidity values from the DHT11 sensor.
    result = sensor.readTemperatureHumidity(temperature, humidity);

    adc_reading = analogRead(light_pin);
    Vout = static_cast<double>(adc_reading) * adc_res;
    RL = 10.0 * (5.0 / Vout - 1.0);
    lux = pow(10.0, 1.6 / 0.6 - 1.0 / 0.6 * log10(RL));

    Serial.print("Light: ");
    Serial.print(lux);
    Serial.print(" lux");

    // Check the results of the readings.
    // If the reading is successful, print the temperature and humidity values.
    // If there are errors, print the appropriate error messages.
    if (result == 0) {
        Serial.print("\tTemperature: ");
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
