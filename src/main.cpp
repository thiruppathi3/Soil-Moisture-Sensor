#include <Arduino.h>

//Analog sensor pins for Soil Moisture Sensor inputs
const int MOISTURE_SENSOR_PIN1 = A1;
const int MOISTURE_SENSOR_PIN2 = A2;
const int MOISTURE_SENSOR_PIN3 = A3;
const int RELAY_PIN = PIN7;

//Soil Moisture Threshold - Tweak it based on the sensors min and max values
const int MIN_SOIL_MOISTURE_THRESHOLD = 1020;
const int MAX_SOIL_MOISTURE_THRESHOLD = 270;

//Threshold to water the plants
const int WATER_THRESHOLD = 50;

static bool isWatering = false;

int soilMoisturePercentage(int moistureSensorPin) {
  int sensorValue = analogRead(moistureSensorPin);
  return map(sensorValue, MIN_SOIL_MOISTURE_THRESHOLD, MAX_SOIL_MOISTURE_THRESHOLD, 0, 100);
}

bool isDry(int moisture1, int moisture2, int moisture3) {
   return moisture1 < WATER_THRESHOLD && moisture2 < WATER_THRESHOLD && moisture3 < WATER_THRESHOLD;
}

void waterPlants() {
   Serial.println("Water the plants");
   digitalWrite(RELAY_PIN, LOW);
   isWatering = true;
   Serial.println("Started watering");
}

void stopWater() {
   Serial.println("Stopping watering");
   digitalWrite(RELAY_PIN, HIGH);
   isWatering = false;
   Serial.println("Stopped watering");
}

void setup() {

   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");
   pinMode(RELAY_PIN, OUTPUT);

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
     if (!isWatering) {
      waterPlants();
     } else {
        Serial.println("Watering is already in progress");
     }
  } else {
     if (isWatering) {
        stopWater();
     } else {
        Serial.println("Watering stopped already");
     }
  }

   delay(1000);
}