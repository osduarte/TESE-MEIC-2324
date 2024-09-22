#include <Wire.h>
#include <ArduinoBLE.h>


// Create a service and characteristic for the IMU data
BLEService imuService("181A"); // Environmental Sensing service
BLECharacteristic imuCharacteristic("2A58", BLERead | BLEWrite, 40); // Increased length for string data

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) {}

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Starting BLE failed!");
    while (1);
  } else {
    Serial.println("BLE initialized successfully.");
  }

  BLE.setLocalName("XIAO_IMU_Sense");
  BLE.setAdvertisedService(imuService);
  BLE.setAdvertisedServiceUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
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

        imuCharacteristic.writeValue((byte)0x01);

        //delay(100); // Adjust the delay as needed
    
    }

    // Disconnected from central
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}