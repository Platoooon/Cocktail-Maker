#include <AccelStepper.h>



#define Vmax 150 //Vitesse Max = 1402 trouvee en testant à la main   //Modifiable a souhait par l'utilisateur

/*    ARDUINO MEGA */
AccelStepper Xaxis(1, 3, 2);  //le 1 pour utilisation de drivers, (si 2 on aurait un pont en H, 3 transistors, ...)
AccelStepper Yaxis(1, 9, 8);  //3,2 et 9,8 = step,dir pins

//Define pin connections for the Buttons and Buttons state
const char Rb=53;  //Blue wires button
char Bb_etat=LOW;
const char Bb=52;  //Red wires button
char Rb_etat=LOW;

const char Leftb=22;  //Directionnal Left button
char Leftb_etat=LOW;
const char Rightb=24;  //Directionnal Right button
char Rightb_etat=LOW;
const char Validationb=26;  //Validation button
char Validationb_etat=LOW;


char MotPosInit=0;  //Variable qui détermine si l'initialisation est à effectuer -> 0 elle est à effectuer , 1 elle n'est pas à effectuer
char Calib=0;  //Variable qui détermine si la calibration est à effectuer -> 0 elle est à effectuer , 1 elle n'est pas à effectuer




void setup() {
     
    // Paramétrage des Moteurs avec setMaxSpeed
    Xaxis.setMaxSpeed(Vmax);
    Yaxis.setMaxSpeed(Vmax);

    // on met les boutons en mode entrée
    pinMode(Bb, INPUT);
    pinMode(Rb, INPUT);
    pinMode(Rightb, INPUT);
    pinMode(Leftb, INPUT);
    pinMode(Validationb, INPUT);
    
    // on active la résistance de pull-down en mettant les broches à l'état bas
    digitalWrite(Bb, LOW);
    digitalWrite(Rb, LOW);
    digitalWrite(Rightb, LOW);
    digitalWrite(Leftb, LOW);
    digitalWrite(Validationb, LOW);

    Serial.begin(9600);

    
}
 
void loop() {

  if(MotPosInit==0)
  {
    MotPosInit=Init_Moteurs();
  }
  
  if(Calib==0)
  {
    Calib=Calibration();
  }
  
  
  
  //Movement(10,200);
  delay(2000);
}










void Movement(int DeltaX, int DeltaY) //(DeltaX,DeltaY) are Actual position(X,Y) - Targeted Position(X,Y) avec DeltaX et DeltaY en steps  //https://cpp.hotexamples.com/examples/-/AccelStepper/distanceToGo/cpp-accelstepper-distancetogo-method-examples.html
{
    float ratio;
    char arret_Bb=0, arret_Rb=0;
    int signDeltaX;
    int signDeltaY;
    
    if(DeltaX!=0)
    {
      signDeltaX=DeltaX/abs(DeltaX);
    }else
    {
      signDeltaX=1;
    }

    if(DeltaY!=0)
    {
      signDeltaY=DeltaY/abs(DeltaY);
    }else
    {
      signDeltaY=1;
    }
    
    Xaxis.moveTo(Xaxis.currentPosition()+DeltaX);
    Yaxis.moveTo(Yaxis.currentPosition()+DeltaY);
    
    if(abs(DeltaX)>abs(DeltaY))
    {
       ratio=float(abs(DeltaY))/float(abs(DeltaX));
       Xaxis.setSpeed(Vmax*signDeltaX);
       Yaxis.setSpeed(Vmax*ratio*signDeltaY);
    }else{
       ratio=float(abs(DeltaX))/float(abs(DeltaY));
       Yaxis.setSpeed(Vmax*signDeltaY);
       Xaxis.setSpeed(round(Vmax*ratio*signDeltaX));
    }
    
    while ((Xaxis.distanceToGo()!=0) && (Yaxis.distanceToGo()!=0))
    {
       Bb_etat = digitalRead(Bb);
       Rb_etat = digitalRead(Rb);
       
       if((Rb_etat == LOW) && (arret_Rb==0))   // le bouton rouge n'a jamais été appuyé -> ici c'est une sécurité
       {
         Xaxis.runSpeedToPosition();
       }else
       {
         arret_Rb=1;
       }
       
       if((Bb_etat == LOW) && (arret_Bb==0))   // le bouton bleu n'a jamais été appuyé -> ici c'est une sécurité
       {
         Yaxis.runSpeedToPosition();
       }else
       {
         arret_Bb=1;
       }
    }
}




char Init_Moteurs()
{
  char arret_Bb=0, arret_Rb=0;
  
  Xaxis.setSpeed(Vmax);
  Yaxis.setSpeed(Vmax);
  
  while(arret_Rb==0 || arret_Bb==0)
  {
         Rb_etat = digitalRead(Rb);
         Bb_etat = digitalRead(Bb);

         
         if((Rb_etat == LOW) && (arret_Rb==0))   // le bouton rouge n'a jamais été appuyé -> ici c'est une nécessité
         {
           Xaxis.runSpeed();
         }else
         {
           arret_Rb=1;
         }

         if((Bb_etat == LOW) && (arret_Bb==0))   // le bouton bleu n'a jamais été appuyé -> ici c'est une nécessité
         {
           Yaxis.runSpeed();
         }else
         {
           arret_Bb=1;
         }
         
  }

  return 1;
}




char Calibration()
{
  char Rightb_etat=0, Leftb_etat=0;
  int PosX,PosY;
  
  Xaxis.setSpeed(-Vmax);
  Yaxis.setSpeed(-Vmax);

  //Endroit où l'on se situe initialement
  PosX=Xaxis.currentPosition();
  PosY=Yaxis.currentPosition();

  while(Validationb_etat==LOW)
  {
    Validationb_etat = digitalRead(Validationb);
    //Serial.print((int)Validationb_etat);
    Rightb_etat = digitalRead(Rightb);
    //Serial.print((int)Rightb_etat);
    Leftb_etat = digitalRead(Leftb);
    //Serial.println((int)Leftb_etat);
    
    //Serial.println("None");

    if((Rightb_etat == HIGH) && (Leftb_etat == HIGH))   // Bouton Droit et Gauche appuyé
    {
      Xaxis.runSpeed();
      Yaxis.runSpeed();
      //Serial.println("Both");
    }else if((Rightb_etat == HIGH) && (Leftb_etat == LOW))  // Bouton Droit appuyé
    {
      Xaxis.runSpeed();
      //Serial.println("Left");
    }else if((Rightb_etat == LOW) && (Leftb_etat == HIGH))  // Bouton Gauche appuyé
    {
      Yaxis.runSpeed();
      //Serial.println("Right");
    }
    
  }

  //Distance parcourue (en Steps je pense)
  Serial.print("Déplace selon l'axe X:   ");
  Serial.println(Xaxis.currentPosition()-PosX);
  Serial.print("Déplace selon l'axe Y:   ");
  Serial.println(Yaxis.currentPosition()-PosY);

  return 1;
}
