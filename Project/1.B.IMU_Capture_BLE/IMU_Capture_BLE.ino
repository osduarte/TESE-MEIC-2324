#include <Wire.h>
#include <LSM6DS3.h>
#include <ArduinoBLE.h>

// Create an LSM6DS3 object
LSM6DS3 myIMU(I2C_MODE, 0x6A); // I2C address is 0x6A

#define CONVERT_G_TO_MS2 9.80665f
#define FREQUENCY_HZ 50
//This constant represents the desired interval between actions in milliseconds.
#define INTERVAL_MS (1000 / (FREQUENCY_HZ + 1))

//This variable is used to keep track of the last time an action was performed.
static unsigned long last_interval_ms = 0;

float aX, aY, aZ, gX, gY, gZ;

// Create a service and characteristic for the IMU data
BLEService imuService("181A"); // Environmental Sensing service
BLECharacteristic imuCharacteristic("2A58", BLERead | BLENotify, 40); // Increased length for string data

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize IMU
  if (myIMU.begin() != 0) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  } else {
    Serial.println("IMU initialized successfully.");
  }

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  } else {
    Serial.println("BLE initialized successfully.");
  }

  BLE.setLocalName("XIAO_IMU_Sense");
  BLE.setAdvertisedService(imuService);

  imuService.addCharacteristic(imuCharacteristic);
  BLE.addService(imuService);

  BLE.advertise();

  Serial.println("Advertising started");
}

void loop() {
  // Listen for BLE central connections
  BLEDevice central = BLE.central();

  if (central) {
    // Connected to central
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    // Check if the IMU data is available
    while (central.connected()) {
      if (millis() > last_interval_ms + INTERVAL_MS) {

        //This function returns the number of milliseconds since the Arduino board began running the current program. It's essentially a timer that keeps increasing.
        last_interval_ms = millis();
        
        aX = myIMU.readFloatAccelX() * CONVERT_G_TO_MS2;
        aY = myIMU.readFloatAccelY() * CONVERT_G_TO_MS2;
        aZ = myIMU.readFloatAccelZ() * CONVERT_G_TO_MS2;
        gX = myIMU.readFloatGyroX();
        gY = myIMU.readFloatGyroX();
        gZ = myIMU.readFloatGyroX();

        // Format IMU data as a string
        char imuDataStr[50];
        //snprintf(imuDataStr, sizeof(imuDataStr), "%.2f,%.2f,%.2f\r\n", aX, aY, aZ);
        snprintf(imuDataStr, sizeof(imuDataStr), "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\r\n", aX ,aY, aZ, gX, gY, gZ);
        imuCharacteristic.writeValue(imuDataStr);

        // Debug print IMU data
        Serial.println(imuDataStr);

        //delay(100); // Adjust the delay as needed
      }
    }

    // Disconnected from central
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}