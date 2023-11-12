#include "ecranV2.h"


int* coordTactile(Adafruit_ILI9341* tft, TouchScreen* ts)
{
  static int X_Y[2];
  
  X_Y[0] = -1;
  X_Y[1] = -1;
  
  TSPoint p = ts->getPoint();

  int pression  = p.z;
  if (pression > MINPRESSURE && pression < MAXPRESSURE)
  {   
    p.x = map(p.x, TS_MINY, TS_MAXY, 0, tft->height());
    p.y = map(p.y, TS_MINX, TS_MAXX, 0, tft->width());
    X_Y[1] = tft->height() - p.x;               //  C'est la coordonée Y, je sais c'est bizarre
    X_Y[0] = p.y;
  }
  
  return X_Y;
}




//____________________Fonctions élémentaires dessin________________________________________________________
void drawBtn(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char* text)
{ 
  tft->fillRect(X0, Y0, largeur, hauteur, color);
  tft->drawRect(X0, Y0, largeur, hauteur, ILI9341_BLACK);
  
  int decalage = 6*(strlen(text)-1);
  tft->setCursor(X0+120-decalage, Y0+12);
  tft->setTextColor(text_color);
  tft->setTextSize(2);
  tft->println(text);
}

void drawBtn1(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char* text)
{ 
  tft->fillRect(X0, Y0, largeur, hauteur, color);
  tft->drawRect(X0, Y0, largeur, hauteur, ILI9341_BLACK);
  
  int decalage = 6*(strlen(text)-1);
  tft->setCursor(X0+95-decalage, Y0+22);
  tft->setTextColor(text_color);
  tft->setTextSize(3);
  tft->println(text);
}

void drawBtn2(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char* text)
{ 
  tft->fillRect(X0, Y0, largeur, hauteur, color);
  tft->drawRect(X0, Y0, largeur, hauteur, ILI9341_BLACK);
  
  int decalage = 6*(strlen(text)-1);
  tft->setCursor(X0+155-decalage, Y0+12);
  tft->setTextColor(text_color);
  tft->setTextSize(2);
  tft->println(text);
}

void drawBtnClavier(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char text)
{ 
  tft->fillRect(X0, Y0, largeur, hauteur, color);
  tft->drawRect(X0, Y0, largeur, hauteur, ILI9341_BLACK);
  
  tft->setCursor(X0+11, Y0+16);
  tft->setTextColor(text_color);
  tft->setTextSize(2);
  tft->println(text);
}

void drawTexteClavier(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, char* text, int nbLettres)
{ 
  tft->fillRect(X0, Y0, largeur, hauteur, color);
  tft->drawRect(X0, Y0, largeur, hauteur, ILI9341_BLACK);
  int decalage;
   for(int i=0; i<nbLettres; i++)
   {
     decalage = 12*(nbLettres-i-1);
     tft->setCursor(X0+(114+12*nbLettres/2)-decalage, Y0+12); //décalage à droite et à gauche du centre du rectangle
     tft->setTextColor(text_color);
     tft->setTextSize(2);
     tft->print(text[i]);
   }
}

//////FIN BOUTONS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void drawBack(Adafruit_ILI9341* tft)
{
  tft->drawRect(15, 10, 30, 30, ILI9341_BLACK);
  tft->fillRect(30, 22, 10, 6, ILI9341_BLACK);
  tft->fillTriangle(20,25,30,15,30,35,ILI9341_BLACK);
}

void scrollUp(Adafruit_ILI9341* tft)
{
  tft->drawRect(145, 10, 30, 30, ILI9341_BLACK);
  tft->fillTriangle(160,15,150,30,170,30,ILI9341_BLACK);
}

void scrollDown(Adafruit_ILI9341* tft)
{
  tft->drawRect(145, 200, 30, 30, ILI9341_BLACK);
  tft->fillTriangle(160,225,150,210,170,210,ILI9341_BLACK);
}

void Exit(Adafruit_ILI9341* tft)
{
  tft->drawRect(275, 10, 30, 30, ILI9341_BLACK);
  for(int i =0; i<5;i++)
  {
    tft->drawLine(280, 12+i, 300, 32+i, ILI9341_RED);
    tft->drawLine(300, 12+i, 280, 32+i, ILI9341_RED);
  }
}

void OUI_NON(Adafruit_ILI9341* tft)
{
  tft->fillRect(40, 140, 110, 70, ILI9341_GREEN);
  tft->drawRect(40, 140, 110, 70, ILI9341_BLACK);
  
  tft->setCursor(63, 160);
  tft->setTextColor(ILI9341_BLACK);
  tft->setTextSize(4);
  tft->println("OUI");

  tft->fillRect(170, 140, 110, 70, ILI9341_RED);
  tft->drawRect(170, 140, 110, 70, ILI9341_BLACK);
  
  tft->setCursor(193, 160);
  tft->setTextColor(ILI9341_BLACK);
  tft->setTextSize(4);
  tft->println("NON");
}

void compteur_perso(Adafruit_ILI9341* tft, char nbSelec)     // cette fonction est vraiment débile j'ai pas réussi à afficher "correctement" le char
{
  const char* caMeSaoule[] = {"0","1","2","3","4"};

  tft->drawRect(20, 200, 65, 85, ILI9341_LIGHTGREY);
  
  for(int i =0; i<5;i++)
  {
    tft->drawLine(50+i, 230, 65+i, 200, ILI9341_BLACK);
  }
  
  tft->setCursor(25, 200);
  tft->setTextColor(ILI9341_BLACK);
  tft->setTextSize(4);
  tft->println(caMeSaoule[nbSelec]); 
  
  tft->setCursor(70,200);
  tft->println("4"); 
}

void Enter(Adafruit_ILI9341* tft,int x,int y)
{
  tft->fillRect(x, y, 30, 30, ILI9341_LIGHTGREY);
  tft->drawRect(x, y, 30, 30, ILI9341_BLACK);
  for(int i =0; i<5;i++)
  {
    tft->drawLine(x+5, y+12+i, x+15, 30+i, ILI9341_GREEN);
    tft->drawLine(x+15, y+20+i, x+25, 15+i, ILI9341_GREEN);
  }
}

void Delete(Adafruit_ILI9341* tft, int x, int y)
{
  tft->fillRect(x, y, 64, 52, ILI9341_WHITE);
  tft->drawRect(x, y, 64, 52, ILI9341_BLACK);
  tft->fillRect(x+15, y+24, 42, 11, ILI9341_RED);
  tft->fillTriangle(x+5,y+29,x+15,y+18,x+15,y+40,ILI9341_RED);
}

void Maj(Adafruit_ILI9341* tft, int x, int y)
{
  tft->fillRect(x, y, 64, 52, ILI9341_WHITE);
  tft->drawRect(x, y, 64, 52, ILI9341_BLACK);
  tft->fillRect(x+20, y+30, 24, 17, ILI9341_BLUE);
  tft->fillTriangle(x+8,y+30,x+32,y+7,x+54,y+30,ILI9341_BLUE); // tft->fillTriangle(x+7,y+30,x+32,y+7,x+54,y+30,ILI9341_BLUE);
}

//____________________Fonctions pages dessin & tactile________________________________________________________
void menuDeroulant(Adafruit_ILI9341* tft, char* text0, char* text1, char* text2, float ratio)                        //ratio entre 0 et 1 (fin deu menu déroulant)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn(tft, 20, 50, 250, 40, ILI9341_WHITE, ILI9341_BLACK, text0);
  drawBtn(tft, 20, 50+50, 250, 40, ILI9341_WHITE, ILI9341_BLACK, text1);
  drawBtn(tft, 20, 50+100, 250, 40, ILI9341_WHITE, ILI9341_BLACK, text2);
  drawBack(tft);
  scrollUp(tft);
  scrollDown(tft);
  Exit(tft);

  tft->drawRect(285, 65, 20, 150, ILI9341_BLACK);
  tft->fillRect(285, 65+(135*ratio), 20, 15, ILI9341_BLACK);
  
}

void ecranAccueil(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn1(tft, 40, 40, 240, 70, ILI9341_WHITE, ILI9341_BLACK, "Service");
  drawBtn1(tft, 40, 120, 240, 70, ILI9341_WHITE, ILI9341_BLACK, "Reglage");
}


void service(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn(tft, 55, 16, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Favoris");
  drawBtn(tft, 55, 72, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Avec Alcool");
  drawBtn(tft, 55, 128, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Sans Alcool");
  drawBtn(tft, 55, 184, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Personnalisable");
  drawBack(tft);
}

void reglages(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn(tft, 55, 40, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Nouvel Alcool");
  drawBtn(tft, 55, 100, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Changement bouteille");
  drawBtn(tft, 55, 160, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Bouteille vide");
  drawBack(tft);
}


void message_err_fav(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn1(tft, 20, 80, 280, 70, ILI9341_RED, ILI9341_BLACK, "Favoris plein!");
  delay(2000);
}

void message_err_fav1(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn1(tft, 20, 80, 280, 70, ILI9341_RED, ILI9341_BLACK, "Deja present");
  delay(2000);
}

char validFavoris(Adafruit_ILI9341* tft, TouchScreen* ts, char nb_Favorite_Cock, char indexAlcool, char* Favorite_Cock)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn1(tft, 20, 40, 280, 70, ILI9341_WHITE, ILI9341_BLACK, "Ajout Favoris");
  OUI_NON(tft);
  
  bool loopRead = 1;
  int* X_Y;
  
  while(loopRead)
  {
    X_Y = coordTactile(tft, ts);
    
    
    if((X_Y[0] > 40) && (X_Y[0] < 150))                           // OUI ajout FAVORIS
    {
      if((X_Y[1] > 140) && (X_Y[1] < 210))
      {
        bool dejaPresent = 0;
        
        if(nb_Favorite_Cock<20)
        {
          for(int i=0; i<nb_Favorite_Cock; i++)
          {
            if(Favorite_Cock[i]==indexAlcool)
            {
              message_err_fav1(tft);
              dejaPresent=1;
            }
          }

                 
          if(!dejaPresent)
          {
            Favorite_Cock[nb_Favorite_Cock] = indexAlcool;

            return 1;
          }

        }
        else
        {
          message_err_fav(tft);
        }
        
        loopRead = 0;
      }
    }

    if((X_Y[0] > 170) && (X_Y[0] < 280))                           // NON ajout FAVORIS
    {
      if((X_Y[1] > 140) && (X_Y[1] < 210))
      {
        loopRead = 0;
      }
    }
  }
  
  return 0;
}


char supprFavoris(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_selec)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn1(tft, 20, 40, 280, 70, ILI9341_WHITE, ILI9341_BLACK, "Supprimer ?");
  OUI_NON(tft); 

  bool loopRead = 1;
  int* X_Y;

  while(loopRead)
  {
    X_Y = coordTactile(tft, ts);
    
    
    if((X_Y[0] > 40) && (X_Y[0] < 150))                           // OUI supprimer
    {
      if((X_Y[1] > 140) && (X_Y[1] < 210))
      {  
          for(alcool_selec; alcool_selec < (*nb_Favorite_Cock)-1; alcool_selec++)
          {
            Favorite_Cock[alcool_selec] = Favorite_Cock[alcool_selec+1];
          }
          
          *nb_Favorite_Cock =  *nb_Favorite_Cock - 1;
          loopRead = 0;
      }
    }

    if((X_Y[0] > 170) && (X_Y[0] < 280))                           // PAS supprimer
    {
      if((X_Y[1] > 140) && (X_Y[1] < 210))
      {
        loopRead = 0;
      }
    }
  }
}


void selection_alc(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_trouve)
{
  TSPoint p = ts->getPoint();

  int TestdeSesMorts = 0;
  bool loopRead = 1;
  unsigned long previousTime = millis();
  
  while(loopRead)
  {
    for(int i=0; i<6; i++)
    {
      TSPoint p = ts->getPoint();
      TestdeSesMorts = TestdeSesMorts + p.z;
    }
    
    if(TestdeSesMorts < 30 || millis()-previousTime > 1000)
    {
      if(millis()-previousTime > 1000)
      {
        (*nb_Favorite_Cock) = (*nb_Favorite_Cock) + validFavoris(tft, ts, (*nb_Favorite_Cock), alcool_trouve, Favorite_Cock);
        
      }

      else
      {
        // Service de la boisson
      }  
      loopRead = 0;          
    }
    TestdeSesMorts = 0;                 
  }  
}


void selection_NON_alc(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_trouve)
{
  TSPoint p = ts->getPoint();
  
  int TestdeSesMorts = 0;
  bool loopRead = 1;
  unsigned long previousTime = millis();
  
  while(loopRead)
  {
    for(int i=0; i<6; i++)
    {
      TSPoint p = ts->getPoint();
      TestdeSesMorts = TestdeSesMorts + p.z;
    }
    
    if(TestdeSesMorts < 30 || millis()-previousTime > 1000)
    {
      if(millis()-previousTime > 1000)
      {
        *nb_Favorite_Cock = *nb_Favorite_Cock + validFavoris(tft, ts, *nb_Favorite_Cock, alcool_trouve, Favorite_Cock);
        
      }
  
      else
      {
        // Service de la boisson
      }
      loopRead = 0;
    }
           
    TestdeSesMorts = 0;
  }  
}


void appui_supprCock(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_selec)
{
  TSPoint p = ts->getPoint();
  
  int TestdeSesMorts = 0;
  bool loopRead = 1;
  unsigned long previousTime = millis();
  
  while(loopRead)
  {
    for(int i=0; i<6; i++)
    {
      TSPoint p = ts->getPoint();
      TestdeSesMorts = TestdeSesMorts + p.z;
    }
    
    if(TestdeSesMorts < 30 || millis()-previousTime > 1000)
    {
      if(millis()-previousTime > 1000)
      {
        supprFavoris(tft, ts, nb_Favorite_Cock, Favorite_Cock, alcool_selec);
      }
  
      else
      {
        // Service de la boisson
      }
      loopRead = 0;
    }
           
    TestdeSesMorts = 0;
  }  
}


char choixProp(Adafruit_ILI9341* tft, TouchScreen* ts, char* lastProp, char nbBoutSelec)
{
  const unsigned int colors[] = {ILI9341_YELLOW,ILI9341_GREENYELLOW,ILI9341_PINK,ILI9341_BLUE};
  
  tft->fillScreen(ILI9341_LIGHTGREY);
  int rapport = 0;
  int lastRapport = 0;
  
  for(int i=0; i<nbBoutSelec; i++)
  {
    rapport = (float)lastProp[2*i+1]*1.7;
    tft->fillRect(100, 230-lastRapport-rapport, 100, rapport, colors[i]);
    lastRapport += rapport;
  }
  
  for(int i=0;i<5;i++)
  {
    tft->drawLine(100, 230+i, 200, 230+i, ILI9341_BLACK);
    tft->drawLine(100+i, 230, 100+i, 60, ILI9341_BLACK);
    tft->drawLine(196+i, 230, 196+i, 60, ILI9341_BLACK);
  }

  tft->drawLine(205, 60, 220, 60, ILI9341_BLACK);
  tft->drawLine(205, 145, 220, 145, ILI9341_BLACK);
  tft->drawLine(205, 230, 220, 230, ILI9341_BLACK);
  
  tft->setCursor(46,10);
  tft->setTextColor(ILI9341_BLACK);
  tft->setTextSize(3);
  tft->println("Proportions :");

  tft->setCursor(230,55);
  tft->setTextSize(2);
  tft->println("100%");

  tft->setCursor(230,140);
  tft->println("50%");

  tft->setCursor(230,225);
  tft->println("0%");

  bool loopRead = 1;
  int* X_Y;
  
  while(loopRead)
  {
    X_Y = coordTactile(tft, ts);

    if((X_Y[0] > 100) && (X_Y[0] < 200)) 
    {
      if((X_Y[1] > 60) && (X_Y[1] < 60+170-lastRapport))
      { 
        lastProp[2*nbBoutSelec+1] = (float)((230-lastRapport)-X_Y[1])/1.7;
        loopRead=0;
      }   
    }
    
  }

}


void selection_prerso(Adafruit_ILI9341* tft, TouchScreen* ts, char num_bouton, char* nbBoutSelec, int index_Deroulant, char* prop)
{
  bool dejaPresent = 0;
  index_Deroulant += num_bouton;
  
  for(int i=0; i<(*nbBoutSelec); i++)
  {
    if(prop[2*i]==index_Deroulant) { dejaPresent=1; }
  }
  
  if(!dejaPresent)
  {
    choixProp(tft, ts, prop, *nbBoutSelec);
    prop[2*(*nbBoutSelec)] = index_Deroulant;
    *nbBoutSelec = *nbBoutSelec + 1 ;
  }
  else
  {
    message_err_fav1(tft);
  }
}


void changement_bout(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBack(tft);
  Exit(tft);
  
  tft->setCursor(71,25);
  tft->setTextColor(ILI9341_BLACK);
  tft->setTextSize(3);
  tft->println("Changement");
  tft->setCursor(54,55);
  tft->println("de bouteille");

  tft->fillRect(33, 110, 40, 40, ILI9341_NAVY);
  tft->drawRect(33, 110, 40, 40, ILI9341_WHITE);
  tft->setTextSize(4);
  tft->setCursor(44, 116);
  tft->setTextColor(ILI9341_WHITE);
  tft->println("1");

  tft->fillRect(140, 110, 40, 40, ILI9341_NAVY);
  tft->drawRect(140, 110, 40, 40, ILI9341_WHITE);
  tft->setCursor(151, 116);
  tft->println("2");

  tft->fillRect(247, 110, 40, 40, ILI9341_NAVY);
  tft->drawRect(247, 110, 40, 40, ILI9341_WHITE);
  tft->setCursor(258, 116);
  tft->println("3");

  tft->fillRect(86, 180, 40, 40, ILI9341_NAVY);
  tft->drawRect(86, 180, 40, 40, ILI9341_WHITE);
  tft->setCursor(97, 186);
  tft->println("4");

  tft->fillRect(190, 180, 40, 40, ILI9341_NAVY);
  tft->drawRect(190, 180, 40, 40, ILI9341_WHITE);
  tft->setCursor(201, 186);
  tft->println("5");
  
}



char clavier(Adafruit_ILI9341* tft, TouchScreen* ts, char* nom) //static char*    OU    mettre entrée char* que l'on change dans la fonction avec un strcpy 
{
  const char lettres[52]={'a','z','e','r','t','y','u','i','o','p','q','s','d','f','g','h','j','k','l','m','w','x','c','v','b','n','A','Z','E','R','T','Y','U','I','O','P','Q','S','D','F','G','H','J','K','L','M','W','X','C','V','B','N'};

  int maj=0,back=0,TEXT_y=42,TEXT_hauteur=40;
  int i,j,aff1=0,nb_lettres=0;
  int* X_Y;
  char new_name_tab[20];
  int pas_hauteur=52, pas_largeur=32;  //largeur des touches (pour rappel on a 320 pixels de largeur)


  //_____________________________________1er affichage_____________________________________//
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBack(tft);
  Enter(tft,275,10);  //(objet,coords)
  
  Delete(tft, 256, 188);
  Maj(tft, 0, 188);



        //INITIALISATION TOUCHES 
        for(j=0;j<3;j++){  //on a 3 lignes
          if(j!=2){
            for(i=0;i<10;i++)  //20 premières lettres = 2 premières lignes
            { 
              drawBtnClavier(tft, i*pas_largeur, j*pas_hauteur+TEXT_y+TEXT_hauteur+2, pas_largeur, pas_hauteur, ILI9341_WHITE, ILI9341_BLACK, lettres[i+10*j]);   //pour i<10:lettres[i+10*j]   //pour i<6:lettres[i+20]
            }    //le +2 (pour j) est présent car c'est le reste de la division euclidienne de la hauteur restante (en dessous du 'TEXT') par 3 (car on veut 3 lignes) <=> pas_hauteur=158/3 = 52p -> 158-52*3=2 (reste)
          }else
          {
            for(i=0;i<6;i++)  //6 dernières lettres
            { 
              drawBtnClavier(tft, (i+2)*pas_largeur, j*pas_hauteur+TEXT_y+TEXT_hauteur+2, pas_largeur, pas_hauteur, ILI9341_WHITE, ILI9341_BLACK, lettres[i+10*j]);    //le "+30" est présent car les bouttons Maj et Delete sont sur les coins inférieurs de l'écran et ont une largeur de 30 pixels    
            } //le +4 est présent car on a 2 touches de moins à gauche et à droite (permet de centrer la ligne)      
          }
        }




//_________________________________________________________________________Boucle Qui Regarde Si Une Action Est Effectuée Par l'Utilisateur_________________________________________________________________________//

  while(1)
  {
    X_Y = coordTactile(tft, ts);

//____________________________________________________________________________________________________________________________________________// LORSQUE L'ON A PAS ENCORE INSÉRER DE LETTRES
    if(nb_lettres==0 && aff1==0)
    {
      drawBtn(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_BLACK, "Nom Nouvelle Boisson");
      aff1=1;
    }


//____________________________________________________________________________________________________________________________________________// BACK
    if((X_Y[0] > 15) && (X_Y[0] < 45))
    {
      if((X_Y[1] > 10) && (X_Y[1] < 40))
      {
        return 0;                                                                                                                                                                                    //on retourne '1'
      }        
    }


//____________________________________________________________________________________________________________________________________________// ENTER
    if((X_Y[0] > 275) && (X_Y[0] < 305))
    {
      if((X_Y[1] > 10) && (X_Y[1] < 40))
      {
        for(i=0;i<nb_lettres;i++)
        {
          nom[i]= new_name_tab[i];
        }

        nom[nb_lettres] = 0;
        
        delay(1000);
        return 1;                                                                                                                                                                                    //on retourne '2'
      }        
    }


//____________________________________________________________________________________________________________________________________________// MAJ -> AFFICHAGE DES NOUVELLES LETTRES
    if((X_Y[0] > 0) && (X_Y[0] < 50))
    {
      if((X_Y[1] > 188) && (X_Y[1] < 240))
      {
        maj=(maj+1)%2;
        //TOUCHES qui changent en fonction de maj
        for(j=0;j<3;j++){  //on a 3 lignes
          if(j!=2){
            for(i=0;i<10;i++)  //20 premières lettres = 2 premières lignes
            { 
              
              drawBtnClavier(tft, i*pas_largeur, j*pas_hauteur+TEXT_y+TEXT_hauteur+2, pas_largeur, pas_hauteur, ILI9341_WHITE, ILI9341_BLACK, lettres[i+10*j+26*maj]);
            }
          }
          
          else
          {
            for(i=0;i<6;i++)  //6 dernières lettres
            { 
              drawBtnClavier(tft, (i+2)*pas_largeur, j*pas_hauteur+TEXT_y+TEXT_hauteur+2, pas_largeur, pas_hauteur, ILI9341_WHITE, ILI9341_BLACK, lettres[i+10*j+26*maj]); 
            }     
          }
        }
      }        
    }
    
//____________________________________________________________________________________________________________________________________________// DELETE -> ON RETIRE UNE LETTRE + AFFICHAGE
    if(nb_lettres>0)
    {
      if((X_Y[0] > 256) && (X_Y[0] < 320))
      {
        if((X_Y[1] > 188) && (X_Y[1] < 240))
        {
          nb_lettres--;
          drawTexteClavier(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_BLACK,  new_name_tab, nb_lettres);
          delay(300);
          
          if(nb_lettres==1)
          {
            aff1=0;   //pour l'affichage du texte "Nom boisson ..."
          }
        }
      }
    }  
//____________________________________________________________________________________________________________________________________________// TOUCHES -> INTERACTION
        if(nb_lettres<20)
        {
          for(j=0;j<3;j++){  //on a 3 lignes
            if(j!=2){
              for(i=0;i<10;i++)  //20 premières lettres = 2 premières lignes
              { 
                if(i!=9)
                {
                  if((X_Y[0] > i*pas_largeur) && (X_Y[0] < (i+1)*pas_largeur))
                  {
                    if((X_Y[1] > j*pas_hauteur+TEXT_y+TEXT_hauteur+2) && (X_Y[1] < (j+1)*pas_hauteur+TEXT_y+TEXT_hauteur+2))
                    {
                      new_name_tab[nb_lettres]= lettres[i+10*j+26*maj];
                      nb_lettres++;
                      drawTexteClavier(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_BLACK,  new_name_tab, nb_lettres);
                      delay(300);
                    }
                  }                
                }else //si i=9 <=> dernière lettre de la ligne (i+1 n'existe pas pour cette lettre, on la traite donc séparémment)
                {
                  if((X_Y[0] > 320-pas_largeur) && (X_Y[0] < 320)) //dernière touche de la ligne
                  {
                    if((X_Y[1] > j*pas_hauteur+TEXT_y+TEXT_hauteur+2) && (X_Y[1] < (j+1)*pas_hauteur+TEXT_y+TEXT_hauteur+2))
                    {
                      new_name_tab[nb_lettres]= lettres[i+10*j+26*maj];
                      nb_lettres++;
                      drawTexteClavier(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_BLACK,  new_name_tab, nb_lettres);
                      delay(300);
                    }                    
                  }
                  
                }

              }
            }
            
            else
            {
              for(i=0;i<6;i++)  //6 dernières lettres -> dernière ligne
              { 
                if(i!=5)  //car i+1 n'existe pas pour i=5
                {
                  if((X_Y[0] > (i+2)*pas_largeur) && (X_Y[0] < ((i+1)+2)*pas_largeur))
                  {
                    if((X_Y[1] > j*pas_hauteur+TEXT_y+TEXT_hauteur+2) && (X_Y[1] < 240))  //car j+1 n'existe pas pour j=2, on prend donc la valeur max possible pour la hauteur (240)
                    {
                      new_name_tab[nb_lettres]= lettres[i+10*j+26*maj];
                      nb_lettres++;
                      drawTexteClavier(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_BLACK,  new_name_tab, nb_lettres);
                      delay(300);
                    }
                  }
                }else{
                  if((X_Y[0] > 320-3*pas_largeur) && (X_Y[0] < 320-2*pas_largeur)) //dernière touche de la ligne
                  {
                    if((X_Y[1] > j*pas_hauteur+TEXT_y+TEXT_hauteur+2) && (X_Y[1] < 240))  //car j+1 n'existe pas pour j=2
                    {
                      new_name_tab[nb_lettres]= lettres[i+10*j+26*maj];
                      nb_lettres++;
                      drawTexteClavier(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_BLACK,  new_name_tab, nb_lettres);
                      delay(300);
                    }
                  }
                }
              }     
            }
          }
        }
  }
}
