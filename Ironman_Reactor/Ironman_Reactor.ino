#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#define CLICKTHRESHHOLD 120
boolean light;
double y,x;
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();

  CircuitPlayground.setAccelRange(LIS3DH_RANGE_2_G);
  CircuitPlayground.setAccelTap(1, CLICKTHRESHHOLD);
  attachInterrupt(digitalPinToInterrupt(CPLAY_LIS3DH_INTERRUPT), tapTime, FALLING);
  light = false;
  y=1;
  x=0;
}

void tapTime(void) {
  //do something :)
  //Serial.print("Tap! ");
  //Serial.println(millis()); // the time
  if (light == true)light = false;
  else light = true;
  Serial.print(light);
}

void loop() {
  y=exp(4.5*x);
  if (light == true) {
    
    x+=0.0050;
    
    if(x>1.231392){
      x+=0.035;
      y-100;
      
    }
    //    for (int i = 0; i < 255; i++) {
    //      for (int j = 0; j < 10; j++) {
    //        CircuitPlayground.setPixelColor(j, i, i, i);
    //      }
    //    }
    //    while (light = true) {
    //      for (int j = 0; j < 10; j++) {
    //        CircuitPlayground.setPixelColor(j, 255, 255, 255);
    //      }
    //    }
  } else {
    x=0;
  }
  for (int j = 0; j < 10; j++) {
      CircuitPlayground.setPixelColor(j, y, y, y);
    }
    Serial.print(y);

}
