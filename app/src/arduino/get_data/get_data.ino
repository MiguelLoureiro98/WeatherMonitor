#include <Arduino.h>
#include "LM35IC.h"

uint8_t temperature_pin = A0;
uint8_t humidity_pin = A1;
uint8_t light_pin = A2;

double Ts = 1.0 * 1000.0;
double time = 0.0;

using LM35::LM35IC;

LM35IC temperature_sensor = LM35IC(temperature_pin);

void setup() {

  Serial.begin(9600);
  //Serial.print("Humidity (%)");
  //Serial.println("Light (lux)");

  pinMode(temperature_pin, INPUT);

}

void loop() {
  
  double current_time = millis();
  double temperature = 0.0;

  if(current_time - time >= Ts){

    temperature = temperature_sensor.readTemp();
    //temperature = analogRead(temperature_pin);
    Serial.print("Temperature:");
    Serial.println(temperature);

    time = current_time;

  }

}
