#include "ROBOT_BarmanV2.h"
#include "HX711V2.h"
#include "ecranV2.h"

long int previousTime;

//__________BALANCE________________________________________________________________________________________________
HX711 scale(6, 5);

float calibration_factor = -375;       // à determiner avec le programme de Meissa annexe
float units;


//__________ECRAN________________________________________________________________________________________________
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

char pageIndex = 0;
boolean loopRead = 1;

int* X_Y;

int index_Deroulant = 0;
int index_Alcool = 0;
char alcool_trouve[3];

char n=0;

char nbBoutSelec = 0;
char prop[8];
bool validCock = 0;
char nom[MAX_BOISSON_SIZE] = "VODICUL";

char indiceBout;

bool bouteilleVide = 0;

//__________DONNEES COCKTAIL / BOUTEILLES________________________________________________________________________________________________
cocktail list_cocktail[NB_MAX_COCK];
char Favorite_Cock[20];
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

char Test_add_cock;


void setup() {

  Serial.begin(9600);

//__________BALANCE______________________________________________________________________________________________
  scale.set_scale(calibration_factor);  
  scale.tare();

//__________COCKTAIL  et  BASE DE DONNEE DES BOUTEILLES__________________________________________________________
  init_cocktail(&bdd_bouteilles,list_cocktail);
  init_BDD_Bouteille(&bdd_bouteilles, boissons, duree_conservation);

  //TEST :
  add_bouteille(&bdd_bouteilles, "LE TEST1", 300902);
  add_bouteille(&bdd_bouteilles, "LE TEST2", 300902);
  add_bouteille(&bdd_bouteilles, "LE TEST3", 300902);
  add_bouteille(&bdd_bouteilles, "LE TEST4", 300902);

//__________ECRAN________________________________________________________________________________________________
  tft.begin();
    
  tft.fillScreen(ILI9341_LIGHTGREY);
  // origin = left,top landscape (USB left upper)
  tft.setRotation(1); 
  tft.setScrollMargins(200,200);
  
}


void afficheBDD()
{
  for(int i=0; i<bdd_bouteilles.nb_cocktailActuel; i++)
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
}


void loop() {
 /*
 // Balance  .......    MEISSA
  Serial.print("Reading:");

  scale.mesure_masse(&units);
  
  Serial.print(units);
  Serial.println(" grams");
*/

  
 //___________________________Test remplissage BDD______________________
  afficheBDD();
  



  switch(pageIndex)
  {
    //___________________________Accueil_________________________________
    case 0:                              
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
      
 //___________________________Service_________________________________      
    case 1:                             
      service(&tft);

      
      while(loopRead)
      {
        
        X_Y = coordTactile(&tft, &ts);
        
        if((X_Y[0] > 15) && (X_Y[0] < 45))         //Back button
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

        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Avec alcool
        {
          if((X_Y[1] > 72) && (X_Y[1] < 112))
          {
            pageIndex = 4;
            loopRead = 0;
          }        
        }

        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Sans alcool
        {
          if((X_Y[1] > 128) && (X_Y[1] < 168))
          {
            pageIndex = 5;
            loopRead = 0;
          }        
        }
        
        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Personnalisable
        {
          if((X_Y[1] > 184) && (X_Y[1] < 224))
          {
            pageIndex = 6;
            loopRead = 0;
          }        
        }
        
      }
      
      loopRead = 1;
      break;
      
 //___________________________Réglages_________________________________  
    case 2:                                    
      reglages(&tft);

      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))       //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
          }        
        }
        
        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Nouvel Alcool
        {
          if((X_Y[1] > 40) && (X_Y[1] < 80))
          {
            pageIndex = 7;
            loopRead = 0;            
          }
        }

        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Changement de bouteille
        {
          if((X_Y[1] > 100) && (X_Y[1] < 140))
          {
            pageIndex = 8;
            loopRead = 0;            
          }
        }

        if((X_Y[0] > 55) && (X_Y[0] < 305))       //Bouteille vide
        {
          if((X_Y[1] > 160) && (X_Y[1] < 200))
          {
            pageIndex = 8;
            bouteilleVide = 1;
            loopRead = 0;            
          }
        }
      }
      
      loopRead = 1;
      break;

 //___________________________Favoris_________________________________
    case 3:  

      if(nb_Favorite_Cock == 0)
      {
        menuDeroulant(&tft,"","","",0);
      }
      else if(nb_Favorite_Cock == 1)
      {
        menuDeroulant(&tft,list_cocktail[Favorite_Cock[0]].nom,"","",0);
      }
      
      else if(nb_Favorite_Cock == 2)
      {
        menuDeroulant(&tft,list_cocktail[Favorite_Cock[0]].nom,list_cocktail[Favorite_Cock[1]].nom,"",0);
      }


      else
      {
        menuDeroulant(&tft,list_cocktail[Favorite_Cock[0]].nom,list_cocktail[Favorite_Cock[1]].nom,list_cocktail[Favorite_Cock[2]].nom,0);
      }
      
      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))            //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 1;
            loopRead = 0;
            index_Deroulant = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))         //Exit button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
            index_Deroulant = 0;
          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll up
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            if(index_Deroulant > 0 )
            {
              index_Deroulant--;
              menuDeroulant(&tft,list_cocktail[Favorite_Cock[index_Deroulant]].nom,list_cocktail[Favorite_Cock[index_Deroulant+1]].nom,list_cocktail[Favorite_Cock[index_Deroulant+2]].nom, (float)index_Deroulant / (nb_Favorite_Cock-3) );
            }
          }
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll down
        {
          if((X_Y[1] > 200) && (X_Y[1] < 230))
          {
            if(index_Deroulant < (nb_Favorite_Cock-3) )
            {
              index_Deroulant++;
              menuDeroulant(&tft,list_cocktail[Favorite_Cock[index_Deroulant]].nom,list_cocktail[Favorite_Cock[index_Deroulant+1]].nom,list_cocktail[Favorite_Cock[index_Deroulant+2]].nom, (float)index_Deroulant / (nb_Favorite_Cock-3) );
            }
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                           
        {
          if((X_Y[1] > 50) && (X_Y[1] < 90))
          { 
            if(nb_Favorite_Cock >= 1)
            {
              appui_supprCock(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, index_Deroulant);
            }

            loopRead = 0;
            index_Deroulant = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                           
        {
          if((X_Y[1] > 100) && (X_Y[1] < 140))
          { 
            if(nb_Favorite_Cock >= 2)
            {
              appui_supprCock(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, index_Deroulant+1);
            }
            
            loopRead = 0;
            index_Deroulant = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                           
        {
          if((X_Y[1] > 150) && (X_Y[1] < 190))
          { 
            if(nb_Favorite_Cock >= 3)
            {
              appui_supprCock(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, index_Deroulant+2);
            }
            
            loopRead = 0;
            index_Deroulant = 0;
          }
        }
      }

      loopRead = 1;
      
      break; 

 //___________________________Avec alcool_________________________________
    case 4:    
                                      
      n=0;

      while(n<3)
      {
        if(list_cocktail[index_Deroulant].Alcolise == 1 && (list_cocktail[index_Deroulant].nom)[0] != 0 )
        { 
          alcool_trouve[n] = index_Deroulant;
          n++;
        }
        index_Deroulant++;
      }
      index_Deroulant = alcool_trouve[1]-1;
      menuDeroulant(&tft,list_cocktail[alcool_trouve[0]].nom,list_cocktail[alcool_trouve[1]].nom,list_cocktail[alcool_trouve[2]].nom, 0);       
      
      while(loopRead)
      {

        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))               //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 1;
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))         //Exit button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll up
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            
            if(index_Alcool <= (bdd_bouteilles.nb_cock_alc-3) && index_Alcool > 0)
            {
              index_Deroulant++;
              index_Alcool--;
              n=0;
              
              while(n<3)
              {
                if(list_cocktail[index_Deroulant].Alcolise == 1 && (list_cocktail[index_Deroulant].nom)[0] != 0 )
                { 
                  alcool_trouve[2-n] = index_Deroulant;
                  n++;
                }
                index_Deroulant--;
              }
              index_Deroulant = alcool_trouve[1]-1;
              menuDeroulant(&tft,list_cocktail[alcool_trouve[0]].nom,list_cocktail[alcool_trouve[1]].nom,list_cocktail[alcool_trouve[2]].nom, (float)index_Alcool / (bdd_bouteilles.nb_cock_alc-3));            
            }

          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll down
        {
          if((X_Y[1] > 200) && (X_Y[1] < 230))
          {
            if(index_Alcool < (bdd_bouteilles.nb_cock_alc-3) )
            {
              index_Deroulant++;
              index_Alcool++;
              n=0;
              
              while(n<3)
              {
                if(list_cocktail[index_Deroulant].Alcolise == 1 && (list_cocktail[index_Deroulant].nom)[0] != 0 )
                { 
                  alcool_trouve[n] = index_Deroulant;
                  n++;
                }
                index_Deroulant++;
              }
              index_Deroulant = alcool_trouve[1]-1;
              menuDeroulant(&tft,list_cocktail[alcool_trouve[0]].nom,list_cocktail[alcool_trouve[1]].nom,list_cocktail[alcool_trouve[2]].nom, (float)index_Alcool / (bdd_bouteilles.nb_cock_alc-3) );            
            }
          }        
        }

//_____________________________________touche 1;2;3 : 
        if((X_Y[0] > 20) && (X_Y[0] < 270))                        
        {
          if((X_Y[1] > 50) && (X_Y[1] < 90))
          { 
            
            selection_alc(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, alcool_trouve[0]);
            
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                        
        {
          if((X_Y[1] > 100) && (X_Y[1] < 140))
          { 
            
            selection_alc(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, alcool_trouve[1]);
            
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                        
        {
          if((X_Y[1] > 150) && (X_Y[1] < 190))
          { 
            
            selection_alc(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, alcool_trouve[2]);
            
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }
        }

        
      }
    
      loopRead = 1;

      break;
      
//___________________________Sans alcool_________________________________
     case 5:    
                                      
      n=0;

      while(n<3)
      {
        if(list_cocktail[index_Deroulant].Alcolise == 0 && (list_cocktail[index_Deroulant].nom)[0] != 0 )
        { 
          alcool_trouve[n] = index_Deroulant;
          n++;
        }

        index_Deroulant++;
      }
      index_Deroulant = alcool_trouve[1]-1;
      menuDeroulant(&tft,list_cocktail[alcool_trouve[0]].nom,list_cocktail[alcool_trouve[1]].nom,list_cocktail[alcool_trouve[2]].nom, 0);       
      
      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))           //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 1;
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))         //Exit button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll up
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            if(index_Alcool <= (bdd_bouteilles.nb_cocktailActuel-bdd_bouteilles.nb_cock_alc-3) && index_Alcool > 0)
            {
              index_Deroulant++;
              index_Alcool--;
              n=0;
              
              while(n<3)
              {
                if(list_cocktail[index_Deroulant].Alcolise == 0 && (list_cocktail[index_Deroulant].nom)[0] != 0 )
                { 
                  alcool_trouve[2-n] = index_Deroulant;
                  n++;
                }
                index_Deroulant--;
              }
              index_Deroulant = alcool_trouve[1]-1;
              menuDeroulant(&tft,list_cocktail[alcool_trouve[0]].nom,list_cocktail[alcool_trouve[1]].nom,list_cocktail[alcool_trouve[2]].nom, (float)index_Alcool / (bdd_bouteilles.nb_cocktailActuel-bdd_bouteilles.nb_cock_alc-3));            
            }

          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll down
        {
          if((X_Y[1] > 200) && (X_Y[1] < 230))
          {
            if(index_Alcool < (bdd_bouteilles.nb_cocktailActuel-bdd_bouteilles.nb_cock_alc-3) )
            {
              index_Deroulant++;
              index_Alcool++;
              char n=0;
              
              while(n<3)
              {
                if(list_cocktail[index_Deroulant].Alcolise == 0 && (list_cocktail[index_Deroulant].nom)[0] != 0 )
                { 
                  alcool_trouve[n] = index_Deroulant;
                  n++;
                }
                index_Deroulant++;
              }
              index_Deroulant = alcool_trouve[1]-1;
              menuDeroulant(&tft,list_cocktail[alcool_trouve[0]].nom,list_cocktail[alcool_trouve[1]].nom,list_cocktail[alcool_trouve[2]].nom, (float)index_Alcool / (bdd_bouteilles.nb_cocktailActuel-bdd_bouteilles.nb_cock_alc-3) );            
            }
          }        
        }

//_____________________________________touche 1;2;3 :
        if((X_Y[0] > 20) && (X_Y[0] < 270))                           
        {
          if((X_Y[1] > 50) && (X_Y[1] < 90))
          { 
            selection_NON_alc(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, alcool_trouve[0]);

            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }
        }
        
        if((X_Y[0] > 20) && (X_Y[0] < 270))                      
        {
          if((X_Y[1] > 100) && (X_Y[1] < 140))
          { 
            selection_NON_alc(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, alcool_trouve[1]);

            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                      
        {
          if((X_Y[1] > 150) && (X_Y[1] < 190))
          { 
            selection_NON_alc(&tft, &ts, &nb_Favorite_Cock, Favorite_Cock, alcool_trouve[2]);

            loopRead = 0;
            index_Deroulant = 0;
            index_Alcool = 0;
          }
        }
      }  
    
      loopRead = 1;

      break;

//___________________________Personnalisable_________________________________
    case 6:    
    
      if(nbBoutSelec>=4 || (validCock && nbBoutSelec>=1) )     //  action Valider new cocktail :
      {
        char retourClavier = clavier(&tft, &ts, nom);
        
        if(retourClavier)
        {
          int sum = 0;
          for(int i=0; i<nbBoutSelec; i++)
          {
            sum += prop[2*i+1];
          }
      
          float rapport = 100/(float)sum;
          
          sum = 0;
          
          for(int i=0; i<nbBoutSelec; i++)
          {
            prop[2*i+1] = (float)prop[2*i+1] * rapport;
            sum += prop[2*i+1];
          }
          
          prop[1] += (100-sum);                                               // éviter d'avoir une somme des ratio boissons = 99 on veut 100 
          
          tft.fillScreen(ILI9341_LIGHTGREY);
          drawBtn1(&tft, 20, 40, 280, 70, ILI9341_WHITE, ILI9341_BLACK, "Alcoolise ?");
          OUI_NON(&tft); 

          while(loopRead)
          {
            X_Y = coordTactile(&tft, &ts);

            if((X_Y[0] > 40) && (X_Y[0] < 150))                           // OUI alcoolisé
            {
              if((X_Y[1] > 140) && (X_Y[1] < 210))
              {
                add_cocktail(&bdd_bouteilles, list_cocktail, nom, prop, nbBoutSelec*2, 1);
                loopRead = 0;
              }
            }
        
            if((X_Y[0] > 170) && (X_Y[0] < 280))                           // PAS alcoolisé
            {
              if((X_Y[1] > 140) && (X_Y[1] < 210))
              {
                add_cocktail(&bdd_bouteilles, list_cocktail, nom, prop, nbBoutSelec*2, 0);       
                loopRead = 0;
              }
            }
          }
        }      

        pageIndex = 1;
        loopRead = 0;
        index_Deroulant = 0;
        validCock = 0;
        nbBoutSelec = 0;
      }


      if(index_Deroulant >= NB_BOIS_INIT)
      {
        menuDeroulant(&tft,bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT +1],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT +2], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );
      }
      else if(index_Deroulant == NB_BOIS_INIT-1)
      {
        menuDeroulant(&tft,boissons[index_Deroulant],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT+1],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT+2], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );                
      }
      else if(index_Deroulant == NB_BOIS_INIT-2)
      {
        menuDeroulant(&tft,boissons[index_Deroulant],boissons[1+index_Deroulant],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT+2], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );                                
      }
      else
      {
        menuDeroulant(&tft,boissons[index_Deroulant],boissons[1+index_Deroulant],boissons[2+index_Deroulant], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );                
      }
      
      compteur_perso(&tft, nbBoutSelec);
      Enter(&tft,275,10);


      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);
        
        if((X_Y[0] > 15) && (X_Y[0] < 45))            //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 1;
            loopRead = 0;
            index_Deroulant = 0;
            nbBoutSelec = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))         //Valid button           !! Penser a mettre celui de swan !!
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            validCock = 1;
            loopRead = 0;
            index_Deroulant = 0;
          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll up
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            if(index_Deroulant > 0 )
            {
              index_Deroulant--;
              loopRead = 0;
            }
          }
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll down
        {
          if((X_Y[1] > 200) && (X_Y[1] < 230))
          {
            if(index_Deroulant < (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) )
            {
              index_Deroulant++;
              loopRead = 0;
            }
          }
        }

//_____________________________________touche 1;2;3 :
        if((X_Y[0] > 20) && (X_Y[0] < 270))                           
        {
          if((X_Y[1] > 50) && (X_Y[1] < 90))
          {            
            selection_prerso(&tft, &ts, 0, &nbBoutSelec, index_Deroulant, prop);
            X_Y[0] = -1;
            X_Y[1] = -1;
            loopRead = 0;
          }
        }
        
        if((X_Y[0] > 20) && (X_Y[0] < 270))                      
        {
          if((X_Y[1] > 100) && (X_Y[1] < 140))
          {  
            selection_prerso(&tft, &ts, 1, &nbBoutSelec, index_Deroulant, prop);
            X_Y[0] = -1;
            X_Y[1] = -1;
            loopRead = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                      
        {
          if((X_Y[1] > 150) && (X_Y[1] < 190))
          { 
            selection_prerso(&tft, &ts, 2, &nbBoutSelec, index_Deroulant, prop);
            X_Y[0] = -1;
            X_Y[1] = -1;
            loopRead = 0;
          }
        }
        
        
      }
      
      loopRead = 1;
      
      break;

//___________________________Nouvel alcool_________________________________
    case 7:
      
      break;
      
//___________________________Changement de bouteille / Bouteille Vide_________________________________
    case 8:
      changement_bout(&tft);

      if(bouteilleVide == 1)
      {
        tft.fillRect(53, 24, 218, 60, ILI9341_LIGHTGREY);
        tft.setCursor(82,25);
        tft.setTextColor(ILI9341_BLACK);
        tft.setTextSize(3);
        tft.println("Supprimer");
        tft.setCursor(82,55);
        tft.println("bouteille");
      }
      
      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);

        if((X_Y[0] > 15) && (X_Y[0] < 45))            //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 2;
            loopRead = 0;
            index_Deroulant = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))         //Exit button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
          }        
        }

        if((X_Y[0] > 33) && (X_Y[0] < 73))         //Bouteille 1
        {
          if((X_Y[1] > 110) && (X_Y[1] < 150))
          {
            if(bouteilleVide == 1)
            {
              bdd_bouteilles.indice_type_boisson[0] = -1;
              bdd_bouteilles.Etat_bouteille[0] = 0;
              
              bouteilleVide = 0;
              pageIndex = 2;
            }

            else
            {
              indiceBout = 0;
              pageIndex = 10;
            }
            loopRead = 0;
          }
        }

        if((X_Y[0] > 140) && (X_Y[0] < 180))         //Bouteille 2
        {
          if((X_Y[1] > 110) && (X_Y[1] < 150))
          {
            if(bouteilleVide == 1)
            {
              bdd_bouteilles.indice_type_boisson[1] = -1;
              bdd_bouteilles.Etat_bouteille[1] = 0;
              
              bouteilleVide = 0;
              pageIndex = 2;
            }

            else
            {
              indiceBout = 1;
              pageIndex = 10;
            }
            loopRead = 0;
          }
        }

        if((X_Y[0] > 247) && (X_Y[0] < 287))         //Bouteille 3
        {
          if((X_Y[1] > 110) && (X_Y[1] < 150))
          {
            if(bouteilleVide == 1)
            {
              bdd_bouteilles.indice_type_boisson[2] = -1;
              bdd_bouteilles.Etat_bouteille[2] = 0;
              
              bouteilleVide = 0;
              pageIndex = 2;
            }

            else
            {
              indiceBout = 2;
              pageIndex = 10;
            }
            loopRead = 0;
          }
        }

        if((X_Y[0] > 86) && (X_Y[0] < 126))         //Bouteille 4
        {
          if((X_Y[1] > 180) && (X_Y[1] < 220))
          {
            if(bouteilleVide == 1)
            {
              bdd_bouteilles.indice_type_boisson[3] = -1;
              bdd_bouteilles.Etat_bouteille[3] = 0;
              
              bouteilleVide = 0;
              pageIndex = 2;
            }

            else
            {
              indiceBout = 3;
              pageIndex = 10;
            }
            loopRead = 0;
          }
        }

        if((X_Y[0] > 190) && (X_Y[0] < 230))         //Bouteille 5
        {
          if((X_Y[1] > 180) && (X_Y[1] < 220))
          {
            if(bouteilleVide == 1)
            {
              bdd_bouteilles.indice_type_boisson[4] = -1;
              bdd_bouteilles.Etat_bouteille[4] = 0;
              
              bouteilleVide = 0;
              pageIndex = 2;
            }

            else
            {
              indiceBout = 4;
              pageIndex = 10;
            }
            loopRead = 0;         
          }
        }
      }

      loopRead = 1;
      
      break;
      
//___________________________Bouteille vide_________________________________
    case 9:
      
      break;

//___________________________Menu deroulant changement de bouteille_________________________________
    case 10:
      if(index_Deroulant >= NB_BOIS_INIT)
      {
        menuDeroulant(&tft,bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT +1],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT +2], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );
      }
      else if(index_Deroulant == NB_BOIS_INIT-1)
      {
        menuDeroulant(&tft,boissons[index_Deroulant],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT+1],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT+2], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );                
      }
      else if(index_Deroulant == NB_BOIS_INIT-2)
      {
        menuDeroulant(&tft,boissons[index_Deroulant],boissons[1+index_Deroulant],bdd_bouteilles.new_boisson[index_Deroulant-NB_BOIS_INIT+2], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );                                
      }
      else
      {
        menuDeroulant(&tft,boissons[index_Deroulant],boissons[1+index_Deroulant],boissons[2+index_Deroulant], (float)index_Deroulant / (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) );                
      }


      while(loopRead)
      {
        X_Y = coordTactile(&tft, &ts);
        
        if((X_Y[0] > 15) && (X_Y[0] < 45))            //Back button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 8;
            loopRead = 0;
            index_Deroulant = 0;
          }        
        }

        if((X_Y[0] > 275) && (X_Y[0] < 305))         //Exit button
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            pageIndex = 0;
            loopRead = 0;
            index_Deroulant = 0;
          }        
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll up
        {
          if((X_Y[1] > 10) && (X_Y[1] < 40))
          {
            if(index_Deroulant > 0 )
            {
              index_Deroulant--;
              loopRead = 0;
            }
          }
        }

        if((X_Y[0] > 145) && (X_Y[0] < 175))                            // Scroll down
        {
          if((X_Y[1] > 200) && (X_Y[1] < 230))
          {
            if(index_Deroulant < (NB_BOIS_INIT + bdd_bouteilles.nb_boutAdd -3) )
            {
              index_Deroulant++;
              loopRead = 0;
            }
          }
        }

//_____________________________________touche 1;2;3 :
        if((X_Y[0] > 20) && (X_Y[0] < 270))                           
        {
          if((X_Y[1] > 50) && (X_Y[1] < 90))
          {            
            bdd_bouteilles.indice_type_boisson[indiceBout] = index_Deroulant;
            bdd_bouteilles.Etat_bouteille[indiceBout] = 1;
            
            pageIndex = 8;
            loopRead = 0;
            index_Deroulant = 0;
          }
        }
        
        if((X_Y[0] > 20) && (X_Y[0] < 270))                      
        {
          if((X_Y[1] > 100) && (X_Y[1] < 140))
          { 
            bdd_bouteilles.indice_type_boisson[indiceBout] = index_Deroulant+1;
            bdd_bouteilles.Etat_bouteille[indiceBout] = 1; 

            pageIndex = 8;
            loopRead = 0;
            index_Deroulant = 0;
          }
        }

        if((X_Y[0] > 20) && (X_Y[0] < 270))                      
        {
          if((X_Y[1] > 150) && (X_Y[1] < 190))
          { 
            bdd_bouteilles.indice_type_boisson[indiceBout] = index_Deroulant+2;
            bdd_bouteilles.Etat_bouteille[indiceBout] = 1; 
            
            pageIndex = 8;
            loopRead = 0;
            index_Deroulant = 0;
          }
        }            
      }      
  }
}
