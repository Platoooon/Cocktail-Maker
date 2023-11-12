#include "ROBOT_Barman.h"
#include "HX711.h"
#include "ecran.h"

long int previousTime;

//__________BALANCE________________________________________________________________________________________________
HX711 scale(6, 5);

float calibration_factor = -375;       // à determiner avec le programme de Meissa annexe
float units;


//__________ECRAN________________________________________________________________________________________________
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

char pageIndex = 7;
boolean loopRead = 1;

int* X_Y;

const char** OUI;  // seulement pour le test

//__________DONNEES COCKTAIL / BOUTEILLES________________________________________________________________________________________________
cocktail list_cocktail[NB_MAX_COCK];
char Favorite_Cock [20];
char nb_Favorite_Cock = 0;

bar_data bdd_bouteilles;


const char* boissons[NB_BOIS_INIT] = {
                      "Tequila",
                      "Vodka",
                      "Scotch whisky",
                      "Bourbon",
                      "Rhum blanc",
                      "Rhum ambre",                      
                      "Cointreau",
                      "Gin",
                      "Ricard",
                                          
                      "Martini dry",
                      "Martini rouge",
                      "Bitter campari",
                      "Benedictine",
                      "Cognac",
                     
                      "Jus de peche",
                      "Jus de tomate",
                      "Jus de citron",
                      "Lime juice cordial",
                      "Jus d'orange",
                      "Jus d'ananas",
                      "Jus pamplemousse",
                      "Limonade",
                      "Eau gazeuse",

                      "Vermouth blanc",
                      "Vermouh rouge",
                      "Vermouth doux", 
                      "Vermouth dry", 
                      
                      "Champagne",
                      "Vin blanc sec",
                      "Vin blanc moelleux",
                      "Vin rouge",
                      "Porto",
                      
                      "Sirop granadine",
                      "Sirop de canne",
                      "Curacao",          
                         
                      "Amaretto",
                      "Creme de casis",
                      "Creme de menthe",
                      "Fernet Branca",
                      "Creme de banane",
                      "Creme cacao blanche",
                      "Liquore galliano",
                      "Liqueur de cafe",    
                      "Apricot brandy",
                      "Sherry brandy",
                      "Kirsh",
                      "Drambuie",
                      "Advokaat",     
                                            
                      "Eau",   
                     };
                     

unsigned long duree_conservation[NB_BOIS_INIT + NB_BOIS_ADD_MAX] = {1111,2222,3333,4444};




void setup() {

  Serial.begin(9600);

//__________BALANCE______________________________________________________________________________________________
  scale.set_scale(calibration_factor);  
  scale.tare();

//__________COCKTAIL  et  BASE DE DONNEE DES BOUTEILLES__________________________________________________________
  init_cocktail(&bdd_bouteilles,list_cocktail);
  init_BDD_Bouteille(&bdd_bouteilles, boissons, duree_conservation);

//__________ECRAN________________________________________________________________________________________________
  tft.begin();

  tft.fillScreen(ILI9341_LIGHTGREY);
  // origin = left,top landscape (USB left upper)
  tft.setRotation(1); 
  tft.setScrollMargins(200,200);

  // _______test :________  

 // menuDeroulant(&tft,boissons,0);
 // ecranAccueil(&tft);
 // service(&tft);
 // reglages(&tft);
}




void loop() {
 /*
 // Balance  .......    MEISSA
  Serial.print("Reading:");

  scale.mesure_masse(&units);
  
  Serial.print(units);
  Serial.println(" grams");
  
 //___________________________Test remplissage BDD______________________
  for(int i=0; i<8; i++)
  {
    Serial.print(list_cocktail[i].nom);
    Serial.print("   ");

    int sum = 0;
    for(int j=0; j<list_cocktail[i].dim_prop; j++)
    {
      if(j%2 == 0)
      {
        Serial.print(boissons[list_cocktail[i].prop[j]]);
        Serial.print("  |  ");
      }
      else
      {
        Serial.print(int(list_cocktail[i].prop[j]));
        Serial.print("  |  ");
        sum += list_cocktail[i].prop[j];
      }
    }

    Serial.print("  |  ");
    Serial.println(sum);
    
  }
  
  for(char i=0; i<NB_BOUTEILLES; i++)
    {
      Serial.println(bdd_bouteilles.new_boisson[i]);      
    }

*/

  switch(pageIndex)
  {
    case 0:                               // Accueil
      ecranAccueil(&tft);
      
      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 40) && (X_Y[0] < 280))
        {
          if((X_Y[1] > 40) && (X_Y[1] < 110))
          {
            pageIndex = 1;
            loopRead = 0;
          }        
        }

        if((X_Y[0] > 40) && (X_Y[0] < 280))
        {
          if((X_Y[1] > 120) && (X_Y[1] < 190))
          {
            pageIndex = 2;
            loopRead = 0;
          }        
        }     
      }
      
      loopRead = 1;
      break;
      
    case 1:                               // Service
      service(&tft);
      
      while(loopRead)
      {
        
        X_Y = coordTactile(&tft, &ts);
        
        if((X_Y[0] > 15) && (X_Y[0] < 45))
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
          }        
        }
      
        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Favoris
        {
          if((X_Y[1] > 30) && (X_Y[1] < 70))
          {
            pageIndex = 3;
            loopRead = 0;
          }        
        }
        
      }
      
      loopRead = 1;
      break;
      
    case 2:                                      // Réglages
      reglages(&tft);

      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))       //Back
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
          }        
        }
//_______________________________________________________________//
        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Nouvel Alcool
        {
          if((X_Y[1] > 40) && (X_Y[1] < 80))
          {
            pageIndex = 7;
            loopRead = 0;
          }        
        }
        
      }
      
      loopRead = 1;
      break;

    case 3:                                       //Favoris
      
      menuDeroulant(&tft,boissons[0],boissons[1],boissons[2],0.9);    
      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 1;
            loopRead = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
          }        
        }
      }

      loopRead = 1;
      
      break; 

      //_________________________________________________________//
     case 7:                                       //Nouvel Alcool
      char clav='0';
      char new_name[20];
      
      clav=clavier(&tft,&ts, new_name);
      while(loopRead)
      {

        if(clav=='1' || clav=='2')
        {
          pageIndex = 2;
          loopRead = 0;
        }        
      }
      
      loopRead = 1;
      
      break; 
  }

}


/*
      loopRead = 1;
      
      TSPoint p = ts.getPoint();

      int TestdeSesMorts = 0;
      previousTime = millis();
      
      while(loopRead)
      {
        for(int i=0; i<6; i++)
        {
          TSPoint p = ts.getPoint();
          TestdeSesMorts = TestdeSesMorts + p.z;
        }
        
        if(TestdeSesMorts < 30 )
        {
          loopRead = 0;
        }
        
        Serial.println(TestdeSesMorts);
        //Serial.println(p.z);
        
        TestdeSesMorts = 0;
      }

      // delay(30);
 
*/
