#include <Stepper.h> 

const int stepsPerRevolution = 200; //result calculated in 

// initialize the stepper library on pins 3 and 4:
Stepper Motor1(stepsPerRevolution, 3, 4);

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4; 

void setup() {
  // initialize the serial port:
  Serial.begin(9600);

  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
   
  // set the speed at 60 rpm: Revolutions(=tours) per minute
  angular_velocity(2*PI);

}

void loop() {
  movement(0.5);
  delay(5000);

}




void movement(float X){  //X is the number of Revolution(tour) that will be done by the motor. X can be a negative number
  float nb_steps;
  nb_steps=X*200; //nb_steps=X*200/360; same formula but with X in degrees (360°= 1 Revolution)
  Motor1.step(round(nb_steps));
}

void angular_velocity(float X){ //X is the value of the angular velocity in rad/s
  float rpm;
  rpm=X*30/PI; //formule pour passer de vitesse à tr/min
  Motor1.setSpeed(round(rpm));
}
