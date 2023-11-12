#include "ecran.h"


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

void Enter(Adafruit_ILI9341* tft,int x,int y)
{
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
  drawBtn(tft, 55, 30, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Favoris");
  drawBtn(tft, 55, 100, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Avec Alcool");
  drawBtn(tft, 55, 170, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Personnalisable");
  drawBack(tft);
}

void reglages(Adafruit_ILI9341* tft)
{
  tft->fillScreen(ILI9341_LIGHTGREY);
  drawBtn(tft, 55, 40, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Nouvel Alcool");
  drawBtn(tft, 55, 100, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Changement bouteille");
  drawBtn(tft, 55, 170, 250, 40, ILI9341_WHITE, ILI9341_BLACK, "Bouteille vide");
  drawBack(tft);
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
        return '0';                                                                                                                                                                                    //on retourne '1'
      }        
    }


//____________________________________________________________________________________________________________________________________________// ENTER
    if((X_Y[0] > 275) && (X_Y[0] < 305))
    {
      if((X_Y[1] > 10) && (X_Y[1] < 40))
      {
        drawBtn(tft, 35, TEXT_y, 250, TEXT_hauteur, ILI9341_WHITE, ILI9341_GREEN, "Validation du Nom");
  //      strcpy(nom,new_name_tab);
        for(i=0;i<nb_lettres;i++)
        {
          Serial.print(new_name_tab[i]);
          nom[i]= new_name_tab[i];
        }

        nom[nb_lettres] = 0;
        
        delay(1000);
        return '1';                                                                                                                                                                                    //on retourne '2'
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
          }else
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
            }else
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
