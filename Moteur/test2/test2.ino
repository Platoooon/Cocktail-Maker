#include <AccelStepper.h>

AccelStepper Xaxis(1, 3, 2); 
AccelStepper Yaxis(1, 9, 8); 

#define Vmax 500 //Vitesse Max = 1402 trouvee en testant à la main   //Modifiable a souhait par l'utilisateur

//Define pin connections for the Buttons and Buttons state
const int Rb=53;  //Blue wires button
int Bb_etat=LOW;
const int Bb=52;  //Red wires button
int Rb_etat=LOW;

char MotPosInit='0';  //Variable qui détermine si l'initialisation a bien été effectuée





void setup() {
     
    // Paramétrage des Moteurs avec setMaxSpeed
    Xaxis.setMaxSpeed(Vmax);
    Yaxis.setMaxSpeed(Vmax);

    // on met les boutons en mode entrée
    pinMode(Bb, INPUT);
    pinMode(Rb, INPUT);
    // on active la résistance de pull-down en mettant les broches à l'état bas
    digitalWrite(Bb, LOW);
    digitalWrite(Rb, LOW);

    Serial.begin(9600);

    
}
 
void loop() {
  int X=30000;
  int Y=0;
  int* DeltaPos;
  char affich='0';   //a changer en fonction de si l'on veut afficher le déplacement effectué ou non

  //DeltaPos=Movement(X,Y);

  if(MotPosInit=='0')
  {
    MotPosInit=Init_Moteurs();
  }
  
  
  if(affich=='1')
  {
    Serial.print("Parcours:   ");
    Serial.print(DeltaPos[0]);  //Position X
    Serial.print(" ");
    Serial.println(DeltaPos[1]);  //Position Y
    Serial.println("");
  }


}







int* Movement(int X, int Y) //(X,Y) are the position coordinates where we wanna go (not considering the start position)
{  
    float ratio;
    int i;
    int signX=X/abs(X);
    int signY=Y/abs(Y);
    int Pos[2];
    
    Pos[0]=-Xaxis.currentPosition();
    Pos[1]=-Yaxis.currentPosition();
    
    if(abs(X)>abs(Y))
    {
       ratio=float(abs(Y))/float(abs(X));
       Xaxis.setSpeed(Vmax*signX);
       Yaxis.setSpeed(Vmax*ratio*signY);
       
       for(i=0;i<abs(X);i++)
       {
         Bb_etat = digitalRead(Bb);
         Rb_etat = digitalRead(Rb);
         if(Bb_etat == LOW){   // le bouton bleu n'est pas appuyé
           Xaxis.runSpeed();
         }
         if(Rb_etat == LOW){   // le bouton rouge n'est pas appuyé
           Yaxis.runSpeed();
         }
       }
       
    }else
    {
       ratio=float(abs(X))/float(abs(Y));
       Yaxis.setSpeed(Vmax*signY);
       Xaxis.setSpeed(round(Vmax*ratio*signX));
       
       for(i=0;i<abs(Y);i++)
       {
         Rb_etat = digitalRead(Rb);
         Bb_etat = digitalRead(Bb);
         if(Rb_etat == LOW)   // le bouton rouge n'est pas appuyé
         {
           Xaxis.runSpeed();
         }
         if(Rb_etat == LOW)   // le bouton bleu n'est pas appuyé
         {
           Yaxis.runSpeed();
         }
       }
       
    }
    
    Pos[0]+=Xaxis.currentPosition();
    Pos[1]+=Yaxis.currentPosition();
    return Pos;
}


char Init_Moteurs()
{
  char arret_Bb='1', arret_Rb='0';   //a mettre à '0' lorsque les 2 moteurs seront branchés
  
  Xaxis.setSpeed(Vmax);
  Yaxis.setSpeed(Vmax);
  
  while(arret_Rb=='0' || arret_Bb=='0')
  {
         Rb_etat = digitalRead(Rb);
         Bb_etat = digitalRead(Bb);

         
         if((Rb_etat == LOW) && (arret_Rb=='0'))   // le bouton rouge n'a jamais été appuyé
         {
           Xaxis.runSpeed();
         }else
         {
           arret_Rb='1';
         }

//         if((Bb_etat == LOW) && (arret_Bb=='0'))   // le bouton bleu n'a jamais été appuyé
//         {
//           Yaxis.runSpeed();
//         }else
//         {
//           arret_Bb=='1';
//         }
         
  }

  return '1';
}
