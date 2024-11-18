#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

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

int16_t counter = 1;  // Initialize a counter variable

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(32, 20);
  display.println(counter);

  display.display();


  Serial.print("Displaying counter: "); // For debugging
  Serial.println(counter);              // Print the counter value in serial monitor

  counter++;                            // Increment the counter


  delay(1000);                          // Delay for 1 second (1000ms) before the next update
}
