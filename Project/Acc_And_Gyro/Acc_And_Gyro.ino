

// XIAO BLE Sense LSM6DS3 Accelerometer Raw Data 

#include "LSM6DS3.h"
#include "Wire.h"

//class LSM6DS3
//I2C communication
LSM6DS3 myIMU(I2C_MODE, 0x6A);  //I2C device address 0x6A

//gravity
//“g” is the value of the earth gravitational force = 9.8 meters per second squared
#define CONVERT_G_TO_MS2 9.80665f

// to be investigated
#define FREQUENCY_HZ 50

// to be investigated
#define INTERVAL_MS (1000 / (FREQUENCY_HZ + 1))

static unsigned long last_interval_ms = 0;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;
float accAngleX, accAngleY;
float gyroAngleX, gyroAngleY, gyroAngleZ;
float elapsedTime, currentTime, previousTime;
float roll, pitch, yaw;
bool debugMode = false;

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

    //ACC
    //Unit of measurement for acceleration is meter per second squared (m/s^2)
    //Acc sensors in “g” or gravity

    accX = myIMU.readFloatAccelX();// / 61; //Divide by 61 as per datasheet (Table 3) -- sensitivity
      if(debugMode) Serial.print("accX:");
      Serial.print(accX);Serial.print(',');
    accY = myIMU.readFloatAccelY(); //* CONVERT_G_TO_MS2;// / 61; //Divide by 61 as per datasheet (Table 3)
      if(debugMode) Serial.print("accY:");
      Serial.print(accY);Serial.print(',');
    accZ = myIMU.readFloatAccelZ();// / 61; //Divide by 61 as per datasheet (Table 3)
      if(debugMode) Serial.print("accZ:");
      Serial.print(accZ);Serial.print('\n');
/*
    // Calculating Roll and Pitch from the accelerometer data
    accAngleX = (atan(accY / sqrt(pow(accX, 2) + pow(accZ, 2))) * 180 / PI);
      if(debugMode) {Serial.print(accAngleX);Serial.print('\n');}
    accAngleY = (atan(-1 * accX / sqrt(pow(accY, 2) + pow(accZ, 2))) * 180 / PI);
      if(debugMode) {Serial.print(accAngleY);Serial.print('\n');}

    //GYRO
    //gyroscope measures rotational velocity or rate of change of the angular position over time, along the X, Y and Z axis
    //Unit of measurement for gyroscope are in degrees per second
    //so in order to get the angular position we just need to integrate the angular velocity.
    previousTime = currentTime;        // Previous time is stored before the actual time read
      if(debugMode) {Serial.print(previousTime);Serial.print('\n');}
    currentTime = millis();            // Current time actual time read
      if(debugMode) {Serial.print(currentTime);Serial.print('\n');}
    elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
      if(debugMode) {Serial.print(elapsedTime);Serial.print('\n');}
    gyroX = myIMU.readFloatGyroX() / 4375; //FS+-125 4375
      if(debugMode) {Serial.print(gyroX);Serial.print('\n');}
    gyroY = myIMU.readFloatGyroY() / 4375;
      if(debugMode) {Serial.print(gyroY);Serial.print('\n');}
    gyroZ = myIMU.readFloatGyroZ() / 4375;
      if(debugMode) {Serial.print(gyroZ);Serial.print('\n');}

    gyroAngleX = gyroAngleX + gyroX * elapsedTime; // deg/s * s = deg
      if(debugMode) {Serial.print(gyroAngleX);Serial.print('\n');}
    gyroAngleY = gyroAngleY + gyroY * elapsedTime;
      if(debugMode) {Serial.print(gyroAngleY);Serial.print('\n');}
    yaw =  yaw + gyroZ * elapsedTime;
      if(debugMode) {Serial.print(yaw);Serial.print('\n');}

    // Complementary filter - combine accelerometer and gyro angle values
    roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
      if(debugMode) {Serial.print(roll);Serial.print('\n');}
    pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
      if(debugMode) {Serial.print(pitch);Serial.print('\n');}

     if(!debugMode) {
      // Print the values on the serial monitor
      Serial.print(roll);
      Serial.print("/");
      Serial.print(pitch);
      Serial.print("/");
      Serial.print('yaw');
      Serial.print("/");
      Serial.print('accY');
    }

  //}
  */
  delay(1000);
}