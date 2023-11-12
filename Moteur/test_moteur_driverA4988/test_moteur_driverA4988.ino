//Libraries
#include <math.h> 


const int stepsPerRevolution = 200; //calculated thanks to datasheet -> see moteurs.docx 

// Define pin connections for Motor n°1
const int M1_dirPin = 8;
const int M1_stepPin = 9;

// Define pin connections for Motor n°2
const int M2_dirPin = 2;
const int M2_stepPin = 3;



void setup()
{
  // Declare pins as Outputs for Motor 1
  pinMode(M1_stepPin, OUTPUT);
  pinMode(M1_dirPin, OUTPUT);
  // Declare pins as Outputs for Motor 2
  pinMode(M2_stepPin, OUTPUT);
  pinMode(M2_dirPin, OUTPUT);
}
void loop()
{
  M1_movement(-5);
  delay(10000); // Wait a second
}

//Motor 1 movement
void M1_movement(float X){  //X is the number of Revolution(tour) that will be done by the motor. X can be a negative number
    int i;

    if(X>0){
      digitalWrite(M1_dirPin, HIGH);  //Turning clockwisely
    }else{
      digitalWrite(M1_dirPin, LOW);  //Turning counterclockwisely
    }
    
    for(i=0;i<abs(X)*stepsPerRevolution;i++){
      digitalWrite(M1_stepPin, HIGH);
      delayMicroseconds(4000);
      digitalWrite(M1_stepPin, LOW);
      delayMicroseconds(4000);
    }
}

//Motor 2 movement
void M2_movement(float X){  //X is the number of Revolution(tour) that will be done by the motor. X can be a negative number
    int i;

    if(X>0){
      digitalWrite(M2_dirPin, HIGH);  //Turning clockwisely
    }else{
      digitalWrite(M2_dirPin, LOW);  //Turning counterclockwisely
    }
    
    for(i=0;i<abs(X)*stepsPerRevolution;i++){
      digitalWrite(M2_stepPin, HIGH);
      delayMicroseconds(4000);
      digitalWrite(M2_stepPin, LOW);
      delayMicroseconds(4000);
    }
}


void M1M2_movement(float X, float Y){  //X is the number of Revolution(tour) that will be done by the motor. X can be a negative number
    int i;

    if(X>0){
      digitalWrite(M2_dirPin, HIGH);  //Turning clockwisely
    }else{
      digitalWrite(M2_dirPin, LOW);  //Turning counterclockwisely
    }
    
    if(Y>0){
      digitalWrite(M2_dirPin, HIGH);  //Turning clockwisely
    }else{
      digitalWrite(M2_dirPin, LOW);  //Turning counterclockwisely
    }
    
    for(i=0;i<abs(X)*stepsPerRevolution;i++){
      digitalWrite(M2_stepPin, HIGH);
      delayMicroseconds(4000);
      digitalWrite(M2_stepPin, LOW);
      delayMicroseconds(4000);      
    }
}
