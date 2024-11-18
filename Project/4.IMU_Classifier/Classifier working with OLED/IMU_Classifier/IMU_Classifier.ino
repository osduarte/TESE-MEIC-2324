#include <LSM6DS3.h>
#include <Wire.h>
#include <ArduinoBLE.h>

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
//#include <tensorflow/lite/version.h>

//OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "model.h"

#define CONVERT_G_TO_MS2 9.80665f

const float accelerationThreshold = 2.5; // threshold of significant in G's
const int numSamples = 155;

int samplesRead = numSamples;

LSM6DS3 myIMU(I2C_MODE, 0x6A);  

// global variables used for TensorFlow Lite (Micro)
tflite::MicroErrorReporter tflErrorReporter;

// pull in all the TFLM ops, you can remove this line and only pull in the TFLM ops you need, if would like to reduce the compiled size of the sketch.
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Create a static memory buffer for TFLM
constexpr int tensorArenaSize = 8 * 1024;
byte tensorArena[tensorArenaSize] __attribute__((aligned(16)));

// array to map gesture index to a name
const char* GESTURES[] = {
  "Bicepcurl_Correto",
  "Bicepcurl_Errado"//,
  //"Shoulderpress_Correto",
  //"Shoulderpress_Errado"//,
  //"Tricep_Correto",
  //"Tricep_Errado"
};

#define NUM_GESTURES (sizeof(GESTURES) / sizeof(GESTURES[0]))

//OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Create a service and characteristic for the IMU data
BLEService imuService("181A"); // Environmental Sensing service
BLECharacteristic imuCharacteristic("2A58", BLERead | BLEWrite | BLENotify, 40); // Increased length for string data


void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) {}


  // Initialize BLE
  if (!BLE.begin()) {
    if (Serial) Serial.println("Starting BLE failed!");
    while (1);
  } else {
    if (Serial) Serial.println("BLE initialized successfully.");
  }
  BLE.setLocalName("XIAO_IMU_Sense");
  BLE.setAdvertisedService(imuService);
  BLE.setAdvertisedServiceUuid("19B10000-E8F2-537E-4F6C-D104768A1214");
  imuService.addCharacteristic(imuCharacteristic);
  BLE.addService(imuService);
  BLE.advertise();
  if (Serial) Serial.println("Advertising started");
  if (Serial) Serial.println();
  // END: Initialize BLE


  // Initialize IMU
  if (myIMU.begin() != 0) {
    if (Serial) Serial.println("Device error");
  } else {
    if (Serial) Serial.println("Device OK!");
  }

    // get the TFL representation of the model byte array
  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    if (Serial) Serial.println("Model schema mismatch!");
    //while (1);
  }

  // Create an interpreter to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);

  // Allocate memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();
  if (tflInterpreter->AllocateTensors() != kTfLiteOk) {
    if (Serial) Serial.println("AllocateTensors failed!");
  };

  // Get pointers for the model's input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);

  //OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }


  display.clearDisplay();        
  display.setTextSize(1);        
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(32, 10);       
  display.println(F("Welcome Olga")); 
  display.display();             
  delay(2000);  

    // Clear for next message
  display.clearDisplay();        
  display.setCursor(32, 10);       
  display.println(F("TESE-MEIC"));  
  display.display();             
  delay(2000);      


  // Clear for next message
  display.clearDisplay();        
  display.setCursor(32, 10);       
  display.println(F("23-24"));  
  display.display();             
  delay(2000);    

}

void loop() {

  //BLE.poll(); // Ensure BLE tasks are serviced
  
  float aX, aY, aZ, gX, gY, gZ;

  //OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(32, 20);


  // Listen for BLE central connections
  BLEDevice central = BLE.central();

  if (central) {
    // Connected to central
    if (Serial) Serial.print("Connected to central: ");
    if (Serial) Serial.println(central.address());
  }

  if(central.connected()) {
    imuCharacteristic.writeValue((byte)0x00);
  }

  // wait for significant motion
  while (samplesRead == numSamples) {
      // read the acceleration data
      aX = myIMU.readFloatAccelX() * CONVERT_G_TO_MS2;
      aY = myIMU.readFloatAccelY() * CONVERT_G_TO_MS2;
      aZ = myIMU.readFloatAccelZ() * CONVERT_G_TO_MS2;

      // sum up the absolutes
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
        samplesRead = 0;
        break;
      }
  }

  // check if the all the required samples have been read since
  // the last time the significant motion was detected
  while (samplesRead < numSamples) {
    // check if new acceleration AND gyroscope data is available and read the acceleration and gyroscope data
      aX = myIMU.readFloatAccelX() * CONVERT_G_TO_MS2;
      aY = myIMU.readFloatAccelY() * CONVERT_G_TO_MS2;
      aZ = myIMU.readFloatAccelZ() * CONVERT_G_TO_MS2;
      gX = myIMU.readFloatGyroX();
      gY = myIMU.readFloatGyroY();
      gZ = myIMU.readFloatGyroZ();

      // normalize the IMU data between 0 to 1 and store in the model's
      // input tensor
      tflInputTensor->data.f[samplesRead * 6 + 0] = (aX + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 1] = (aY + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 2] = (aZ + 4.0) / 8.0;
      tflInputTensor->data.f[samplesRead * 6 + 3] = (gX + 2000.0) / 4000.0;
      tflInputTensor->data.f[samplesRead * 6 + 4] = (gY + 2000.0) / 4000.0;
      tflInputTensor->data.f[samplesRead * 6 + 5] = (gZ + 2000.0) / 4000.0;

      samplesRead++;

      if (samplesRead == numSamples) {
        // Run inferencing
        TfLiteStatus invokeStatus = tflInterpreter->Invoke();
        if (invokeStatus != kTfLiteOk) {
          if (Serial) Serial.println("Invoke failed!");
          while (1);
          return;
        }

        //Loop through the output tensor values from the model
        for (int i = 0; i < NUM_GESTURES; i++) {
          if (Serial) Serial.print(GESTURES[i]);
          if (Serial) Serial.print(": ");
          if (Serial) Serial.println(tflOutputTensor->data.f[i], 6);
          delay(1000);
          if(strcmp(GESTURES[i], GESTURES[0]) == 0 && tflOutputTensor->data.f[i] > 0.5){ digitalWrite(LED_RED, HIGH);   digitalWrite(LED_GREEN, LOW); imuCharacteristic.writeValue((byte)0x01); display.println(GESTURES[i]); display.display();}
          if(strcmp(GESTURES[i], GESTURES[1]) == 0 && tflOutputTensor->data.f[i] > 0.5){ digitalWrite(LED_GREEN, HIGH); digitalWrite(LED_RED, LOW);   imuCharacteristic.writeValue((byte)0x02); display.println(GESTURES[i]); display.display();}
        }
        Serial.println();
      }
  }
}
