// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN A4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 80

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10;

//light
int loop_count_l = 0;
float light_value;
float light_sum = 0;
float light_smoothed = 0;
const int size_light = 10;
float light_readings[size_light];

//temp
int loop_count_t = 0;
float temp_value;
float temp_sum = 0;
float temp_smoothed = 0;
const int size_temp = 30;
float temp_readings[size_temp];


int count = 1;


//values
int r, g, b, bri;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  pixels.begin(); // This initializes the NeoPixel library.

  r = 255 ;
  g = 255;
  b = 255;
  bri = 255;

  //sensors
  for (int i = 0; i < size_light; i++) {
    light_readings[i] = 0;
    temp_readings[i] = 0;
  }
}

void loop() {


  //sensors
  //temperature
  temp_sum = temp_sum - temp_readings[loop_count_t];
  temp_readings[loop_count_t] = CircuitPlayground.temperature();
  temp_sum = temp_sum + temp_readings[loop_count_t];
  loop_count_t ++;

  if (loop_count_t >= size_temp) {
    loop_count_t = 0;
  }
  temp_smoothed = temp_sum / size_temp;

  //light
  light_sum = light_sum - light_readings[loop_count_l];
  light_readings[loop_count_l] = CircuitPlayground.lightSensor();
  light_sum = light_sum + light_readings[loop_count_l];
  loop_count_l ++;

  if (loop_count_l >= size_light) {
    loop_count_l = 0;
  }
  light_smoothed = light_sum / size_light;


  //brightness based on light sensor
  bri = map(light_smoothed, 0, 70, 255, 0);
  //rgb value from the cyan to orange
  r = map(temp_smoothed, 15, 38, 36, 217);
  g = map(temp_smoothed, 15, 38, 84, 81);
  b = map(temp_smoothed, 15, 38, 237, 19);



  for (int i = 0; i < NUMPIXELS; i++) {

    
    pixels.setPixelColor(i, pixels.Color(r, g, b));
    pixels.setBrightness(bri);
    
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  count ++;
}
