#include <Adafruit_CircuitPlayground.h>

int vals[8] = {3, 2, 0, 1, 6, 9, 10, 12};
float doo = 261.626;
float rei = 293.665;
float mi = 329.628;
float fa = 349.228;
float so = 391.995;
float la = 440.0;
float xi = 493.883;
float doo1 = 523.251;
float on[4] = {doo, mi, so, doo1};
float off[4] = {doo1, so, mi, doo};
float mario[7] = { mi, mi, mi, doo, mi, so};
bool light;
double x, y;
void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  light = false;
}

void loop() {
  y = exp(4.5 * x);
  if (light == true) {
    x += 0.0050;
  } else {
    x = 0;
  }
  if (CircuitPlayground.readCap(3) > 800 && light == false) {
    light = true;
    //playtone
    for (int i = 0; i < 4; i++) {
      CircuitPlayground.playTone(on[i], 150);
      if (i == 2) {
        for (int j = 0; j < 10; j++) {
          CircuitPlayground.setPixelColor(j, 100, 100, 100);
        }
      }
    }


  }
  delay(100);

  if (CircuitPlayground.readCap(2) > 800 && light == true) {
    //playtone

    for (int i = 0; i < 4; i++) {
      CircuitPlayground.playTone(off[i], 150);
      if (i == 2) {
        for (int j = 0; j < 10; j++) {
          CircuitPlayground.setPixelColor(j, 0, 0, 0);
        }
      }
    }

    light = false;
  }
  delay(100);

  if (CircuitPlayground.readCap(0) > 800 && light == true) {
    //playtone
    for (int j = 0; j < 10; j++) {
     
      if (j % 2 == 0) {
        for (int k = 0; k < 10; k++) {
          CircuitPlayground.setPixelColor(j, 255, 50, 50);
        }
      } else {
        for (int k = 0; k < 10; k++) {
          CircuitPlayground.setPixelColor(j, 55, 50, 250);
        }
      }
    }


  }
  delay(100);

}
