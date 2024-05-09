/* accelerometer test
 arduino nano 328p + adxl335

*/

#define ACCL_X_PIN A0                  // x-axis of the accelerometer
#define ACCL_Y_PIN A1                  // y-axis
#define ACCL_Z_PIN A2                  // z-axis (only on 3-axis models)

#define UPDATE_TIME 10

class ADXL35 {
  private:
    int xpin, ypin, zpin;
    int xval, yval, zval;
    int xval_old, yval_old, zval_old;    
  public:
    ADXL35() { xpin = ACCL_X_PIN; ypin = ACCL_Y_PIN; zpin = ACCL_Z_PIN; }
    void getSample() {
      xval = analogRead(ACCL_X_PIN);
      yval = analogRead(ACCL_Y_PIN);
      zval = analogRead(ACCL_Z_PIN);
#if 1
      xval = (xval + xval_old) / 2;
      yval = (yval + yval_old) / 2;
      zval = (zval + zval_old) / 2;
      xval_old = xval;
      yval_old = yval;
      zval_old = zval;
#endif
    }
    int getX() { return xval; }
    int getY() { return yval; }
    int getZ() { return zval; }
} accl;

char buf[80];


void setup() {
  // initialize the serial communications:
  Serial.begin(115200);
  while(!Serial);
}

void loop() {
  // read sensor values for 3 axis
  accl.getSample();
  
  sprintf(buf, "%d,%d,%d\n", accl.getX(), accl.getY(), accl.getZ()); // print comma separated values
  Serial.print(buf);


  // delay before next reading:
  delay(UPDATE_TIME);
}