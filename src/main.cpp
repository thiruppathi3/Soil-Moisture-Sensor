#include <Arduino.h>

//Analog sensor pins for Soil Moisture Sensor inputs
const int MOISTURE_SENSOR_PIN1 = A1;
const int MOISTURE_SENSOR_PIN2 = A2;
const int MOISTURE_SENSOR_PIN3 = A3;

//Soil Moisture Threshold - Tweak it based on the sensors min and max values
const int MIN_SOIL_MOISTURE_THRESHOLD = 1020;
const int MAX_SOIL_MOISTURE_THRESHOLD = 270;

//Threshold to water the plants
const int WATER_THRESHOLD = 50;

int soilMoisturePercentage(int moistureSensorPin) {
  int sensorValue = analogRead(moistureSensorPin);
  return map(sensorValue,MIN_SOIL_MOISTURE_THRESHOLD, MAX_SOIL_MOISTURE_THRESHOLD, 0, 100);
}

bool isDry(int moisture1, int moisture2, int moisture3) {
   return moisture1 < 50 && moisture2 < 50 && moisture3 < 50;
}

void waterPlants() {
   Serial.println("Water the plants");
}

void setup() {

   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   delay(2000);

}

void loop() {

   int moistureSensor1, moistureSensor2, moistureSensor3;

   moistureSensor1 = soilMoisturePercentage(MOISTURE_SENSOR_PIN1);
   Serial.print("Mositure1 : ");
   Serial.println(moistureSensor1);

   delay(500);

   moistureSensor2= soilMoisturePercentage(MOISTURE_SENSOR_PIN2);
   Serial.print("Mositure2 : ");
   Serial.println(moistureSensor2);

   delay(500);

   moistureSensor3= soilMoisturePercentage(MOISTURE_SENSOR_PIN3);
   Serial.print("Mositure3 : ");
   Serial.println(moistureSensor3);
   
   delay(500);

  if(isDry(moistureSensor1, moistureSensor2, moistureSensor3)) {
     waterPlants();
  }

   delay(1000);
}