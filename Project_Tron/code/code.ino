#include <Adafruit_CircuitPlayground.h>
int left = 6, right = 9;
double y, x;
bool light;
bool left_turn = true;
bool right_turn = true;
bool start = true;
bool left_state = false;
bool right_state = false;
int loop_count = 0;

#define TILT_ANGLE  20.0
#define TILT_TIME   1500
#define GRAVITY     9.80665
#define RAD2DEG     52.29578

float currentAngle;
float targetAngle;
unsigned long tiltStartTime;
bool tilting;
bool tilt_state;

void setup() {
  CircuitPlayground.begin();

  //initial values
  light = false;
  y = 1;
  x = 0;

  //pins
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
}

void loop() {

  if (CircuitPlayground.slideSwitch()) { //turn on

    //light effect when turn on
    Serial.println("turn on");
    y = exp(4.5 * x);
    x += 0.0050;
    if (x > 1.231392) {
      x += 0.035;
      y - 100;
    }
    for (int j = 0; j < 10; j++) {
      CircuitPlayground.setPixelColor(j, y, y, y);
    }
    if (left_turn) {

      if (loop_count % 80 == 0) {
        digitalWrite(left, left_state);
        left_state = !left_state;
      }
    } else {
      digitalWrite(left, 1);
    }
    if (right_turn) {
      if (loop_count % 80 == 0) {
        digitalWrite(right, right_state);
        right_state = !right_state;
      }
    } else {
      digitalWrite(right, 1);
    }

  } else  {
    Serial.println("turn off");
    //turn off
    y = 0;
    for (int j = 0; j < 10; j++) {
      CircuitPlayground.setPixelColor(j, y, y, y);
    }
    y = 1;
    x = 0;
    digitalWrite(left, 0);
    digitalWrite(right, 0);
  }


  loop_count++;
  Serial.println(loop_count);

  //tilt detection
  currentAngle = RAD2DEG * asin(-CircuitPlayground.motionX() / GRAVITY);

  if ((CircuitPlayground.leftButton()) || (CircuitPlayground.rightButton())) {
    targetAngle = currentAngle;
  }

  if ((currentAngle - targetAngle > 10) || (currentAngle - targetAngle < -10)) {
    if (!tilting) tiltStartTime = millis();
    tilting = true;
  } else {
    tilting = false;
    left_turn = false;
    right_turn = false;
  }
  if (tilting) {
    if (millis() - tiltStartTime > TILT_TIME) {
      if (currentAngle - targetAngle > TILT_ANGLE) {
        // Sound alarm
        //CircuitPlayground.playTone(600, 500);
        left_turn = true;
      }
      if (currentAngle - targetAngle < -TILT_ANGLE) {
        // Sound alarm
        // CircuitPlayground.playTone(800, 500);
        right_turn = true;
      }
    }
  }





}
