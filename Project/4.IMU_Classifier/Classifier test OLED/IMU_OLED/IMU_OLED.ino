// #include <LSM6DS3.h>
// #include <Wire.h>

//OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// #define CONVERT_G_TO_MS2 9.80665f

// const float accelerationThreshold = 2.5; // threshold of significant in G's
// const int numSamples = 155;

// int samplesRead = numSamples;

// LSM6DS3 myIMU(I2C_MODE, 0x6A);  

// #define NUM_GESTURES (sizeof(GESTURES) / sizeof(GESTURES[0]))

//OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 5000) {}


  // Initialize IMU
  // if (myIMU.begin() != 0) {
  //   if (Serial) Serial.println("Device error");
  // } else {
  //   if (Serial) Serial.println("Device OK!");
  // }


  //OLED
  //SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
   Serial.println(F("SSD1306 allocation failed"));
   for(;;); // Don't proceed, loop forever
  }
  //Clear the buffer
  display.clearDisplay();
  display.display();
}

void loop() {

  // float aX, aY, aZ, gX, gY, gZ;

  //OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(32, 17);
  display.println("HELLO");
  display.display();
  delay(2000);

  // // wait for significant motion
  // while (samplesRead == numSamples) {
  //     // read the acceleration data
  //     aX = myIMU.readFloatAccelX() * CONVERT_G_TO_MS2;
  //     aY = myIMU.readFloatAccelY() * CONVERT_G_TO_MS2;
  //     aZ = myIMU.readFloatAccelZ() * CONVERT_G_TO_MS2;

  //     // sum up the absolutes
  //     float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

  //     // check if it's above the threshold
  //     if (aSum >= accelerationThreshold) {
  //       // reset the sample read count
  //       samplesRead = 0;
  //       break;
  //     }
  // }

  // check if the all the required samples have been read since the last time the significant motion was detected
  // while (samplesRead < numSamples) {
  //   // check if new acceleration AND gyroscope data is available and read the acceleration and gyroscope data
  //     aX = myIMU.readFloatAccelX() * CONVERT_G_TO_MS2;
  //     aY = myIMU.readFloatAccelY() * CONVERT_G_TO_MS2;
  //     aZ = myIMU.readFloatAccelZ() * CONVERT_G_TO_MS2;
  //     gX = myIMU.readFloatGyroX();
  //     gY = myIMU.readFloatGyroY();
  //     gZ = myIMU.readFloatGyroZ();

  //     samplesRead++;

  //     display.clearDisplay();
  //     display.setTextSize(2);
  //     display.setTextColor(WHITE);
  //     display.setCursor(32, 17);
  //     display.println(aX);
  //     display.display();
  //     delay(1000);


  // }
}
