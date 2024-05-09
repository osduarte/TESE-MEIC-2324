// XIAO BLE Sense LSM6DS3 Accelerometer Raw Data 

#include "LSM6DS3.h"
#include "Wire.h"

//Create a instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);  //I2C device address 0x6A

//gravity
#define CONVERT_G_TO_MS2 9.80665f

// to be investigated
#define FREQUENCY_HZ 50

// to be investigated
#define INTERVAL_MS (1000 / (FREQUENCY_HZ + 1))

static unsigned long last_interval_ms = 0;

float accX, accY, accZ;
float accAngleX, accAngleY = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;

  if (myIMU.begin() != 0) {
    Serial.println("Device error");
  } else {
    Serial.println("Device OK!");
  }
}



void loop() {
  // if (millis() > last_interval_ms + INTERVAL_MS) {
  //   last_interval_ms = millis();
    
    //4 decimals
    /*Serial.print(myIMU.readFloatAccelX() * CONVERT_G_TO_MS2, 4);
    Serial.print('\t');
    Serial.print(myIMU.readFloatAccelY() * CONVERT_G_TO_MS2, 4);
    Serial.print('\t');
    Serial.println(myIMU.readFloatAccelZ() * CONVERT_G_TO_MS2, 4);
    */

    accX = myIMU.readFloatAccelX() / 61; //Divide by 61 as per datasheet (Table 3)
    accY = myIMU.readFloatAccelY() / 61; //Divide by 61 as per datasheet (Table 3)
    accZ = myIMU.readFloatAccelZ() / 61; //Divide by 61 as per datasheet (Table 3)

    // Calculating Roll and Pitch from the accelerometer data
    accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI);
    accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI);

    // Print the values on the serial monitor
    Serial.print(accAngleX);
    Serial.print("/");
    Serial.print(accAngleY);

  //}
}