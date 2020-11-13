///////////////////////////////////////////////////////////////////////////////
// Circuit Playground Slouch Detector v3
//
// Push button(s) to set a target angle.
// Compute current angle using accelerometer and compare
// to preset slouch angle. Sound alarm if slouching after
// a preset period of time.
//
// Author: Carter Nelson
// MIT License (https://opensource.org/licenses/MIT)

float doo = 261.626;
float rei = 293.665;
float mi = 329.628;
float fa = 349.228;
float so = 391.995;
float la = 440.0;
float xi = 493.883;
float doo1 = 523.251;
float right[2] = {doo, mi};
float wrong[2] = {rei, rei};
#include <Adafruit_CircuitPlayground.h>

#define SLOUCH_ANGLE        10.0      // allowable slouch angle (deg)
#define SLOUCH_TIME         3000      // allowable slouch time (secs) 
#define GRAVITY             9.80665   // standard gravity (m/s^s)
#define RAD2DEG             52.29578  // convert radians to degrees

float currentAngle;
float targetAngle;
unsigned long slouchStartTime;
bool slouching;
bool state;

///////////////////////////////////////////////////////////////////////////////
void setup() {
  // Initialize Circuit Playground
  CircuitPlayground.begin();
  state = false;
  // Initialize target angle to zero.
  targetAngle = 0;
}

///////////////////////////////////////////////////////////////////////////////
void loop() {
  // Compute current angle
  currentAngle = RAD2DEG * asin(-CircuitPlayground.motionZ() / GRAVITY);

  // Set target angle on button press
  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
    CircuitPlayground.playTone(900, 100);
    delay(100);
    CircuitPlayground.playTone(900, 100);
    delay(100);
  }

  // Check for slouching
  if (currentAngle - targetAngle > SLOUCH_ANGLE) {
    if (!slouching) slouchStartTime = millis();
    slouching = true;
  } else {
    slouching = false;
  }

  // If we are slouching
  if (slouching) {
    // Check how long we've been slouching
    
    if (millis() - slouchStartTime > SLOUCH_TIME) {
      // Play a tone
      for (int i = 0; i < 2; i++) {
        CircuitPlayground.playTone(wrong[i], 200);
      }
      for (int i = 0; i < 10; i++) {
        CircuitPlayground.setPixelColor(i, 200, 15, 15);
      }
      state = true;
    }
  } else {
    
    if (state == true) {
      for (int i = 0; i < 2; i++) {
        CircuitPlayground.playTone(right[i], 100);
      }
      state = false;
    }
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, 0, 50, 0);
    }
  }
}
