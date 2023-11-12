#include "HX711.h"

HX711 scale(6, 5);

float calibration_factor = -375;
float units;


void setup()
{
  Serial.begin(9600);
  
  scale.set_scale(calibration_factor);         //Ces deux lignes sont necessairesa mettre dans le setup
  scale.tare();                       
  
  Serial.println("Readings:");
}

void loop()
{
  Serial.print("Reading:");

  scale.mesure_masse(&units);
  
  Serial.print(units);
  Serial.println(" grams");
  delay(1000);
}
