#include "ROBOT_BarmanV2.h"

  //______________________INITIALISATION BDD COCKTAILS  &  BDD BOUTEILLES :_________________________________________

void init_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail)
{ 
  bdd_bouteilles->nb_cocktailActuel = NB_COCK_INIT;   
  bdd_bouteilles->nb_cock_alc = NB_COCK_INIT - 4;             // !! Penser à modifier !!


  for(char i=0; i<(NB_MAX_COCK-NB_COCK_INIT); i++)
  {
    bdd_bouteilles->new_cock[i][0] = 0;
  }

  
  list_cocktail[0].nom = "Ricard";
  static char prop0[] = { 8,35,48,65 };
  list_cocktail[0].prop = prop0;
  list_cocktail[0].dim_prop = 4;
  list_cocktail[0].Alcolise = 1;

  list_cocktail[1].nom = "Alexandra";
  static char prop1[] = { 40,33,13,67};
  list_cocktail[1].prop = prop1;
  list_cocktail[1].dim_prop = 4;
  list_cocktail[1].Alcolise = 1;

  list_cocktail[2].nom = "Americano";
  static char prop2[] = { 9,17, 11,33, 10,50};
  list_cocktail[2].prop = prop2;
  list_cocktail[2].dim_prop = 6;
  list_cocktail[2].Alcolise = 1;

  list_cocktail[3].nom = "Apotheke";
  static char prop3[] = { 13,40, 37,30, 38,30};
  list_cocktail[3].prop = prop3;
  list_cocktail[3].dim_prop = 6;
  list_cocktail[3].Alcolise = 1;

  list_cocktail[4].nom = "Sirop Menthe";
  static char prop4[] = { 13,50, 39,50};
  list_cocktail[4].prop = prop4;
  list_cocktail[4].dim_prop = 4;
  list_cocktail[4].Alcolise = 0;

  list_cocktail[5].nom = "Bellini";
  static char prop5[] = { 32,10, 48,90};
  list_cocktail[5].prop = prop5;
  list_cocktail[5].dim_prop = 4;
  list_cocktail[5].Alcolise = 1;


  list_cocktail[6].nom = "Eau";
  static char prop6[] = {48,100};
  list_cocktail[6].prop = prop6;
  list_cocktail[6].dim_prop = 2;
  list_cocktail[6].Alcolise = 0;

  list_cocktail[7].nom = "Limonade";
  static char prop7[] = {21, 100};
  list_cocktail[7].prop = prop7;
  list_cocktail[7].dim_prop = 2;
  list_cocktail[7].Alcolise = 0;

  list_cocktail[8].nom = "PampleGaz";
  static char prop8[] = {20,50, 22,50};
  list_cocktail[8].prop = prop8;
  list_cocktail[8].dim_prop = 4;
  list_cocktail[8].Alcolise = 0;
/*
  list_cocktail[9].nom = "";
  static char prop9[] = { };
  list_cocktail[9].prop = prop9;
  list_cocktail[9].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[10].nom = "";
  static char prop10[] = { };
  list_cocktail[10].prop = prop10;
  list_cocktail[10].dim_prop = ;       //////  PENSER A METTRE :    list_cocktail[].Alcolise = ;
  list_cocktail[].Alcolise = ;
  
  list_cocktail[11].nom = "";
  static char prop11[] = { };
  list_cocktail[11].prop = prop11;
  list_cocktail[11].dim_prop = ;
  list_cocktail[].Alcolise = ;
  
  list_cocktail[12].nom = "";
  static char prop12[] = { };
  list_cocktail[12].prop = prop12;
  list_cocktail[12].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[13].nom = "";
  static char prop13[] = { };
  list_cocktail[13].prop = prop13;
  list_cocktail[13].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[14].nom = "";
  static char prop14[] = { };
  list_cocktail[14].prop = prop14;
  list_cocktail[14].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[15].nom = "";
  static char prop15[] = { };
  list_cocktail[15].prop = prop15;
  list_cocktail[15].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[16].nom = "";
  static char prop16[] = { };
  list_cocktail[16].prop = prop16;
  list_cocktail[16].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[17].nom = "";
  static char prop17[] = { };
  list_cocktail[17].prop = prop17;
  list_cocktail[17].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[18].nom = "";
  static char prop18[] = { };
  list_cocktail[18].prop = prop18;
  list_cocktail[18].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[19].nom = "";
  static char prop19[] = { };
  list_cocktail[19].prop = prop19;
  list_cocktail[19].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[20].nom = "";
  static char prop20[] = { };
  list_cocktail[20].prop = prop20;
  list_cocktail[20].dim_prop = ;
  list_cocktail[].Alcolise = ;
  
  list_cocktail[21].nom = "";
  static char prop21[] = { };
  list_cocktail[21].prop = prop21;
  list_cocktail[21].dim_prop = ;
  list_cocktail[].Alcolise = ;
  
  list_cocktail[22].nom = "";  
  static char prop22[] = { };
  list_cocktail[22].prop = prop22;
  list_cocktail[22].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[23].nom = "";
  static char prop23[] = { };
  list_cocktail[23].prop = prop23;
  list_cocktail[23].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[24].nom = "";
  static char prop24[] = { };
  list_cocktail[24].prop = prop24;
  list_cocktail[24].dim_prop = ;
  list_cocktail[].Alcolise = ;

  list_cocktail[25].nom = "";
  static char prop25[] = { };
  list_cocktail[25].prop = prop25;
  list_cocktail[25].dim_prop = ;
  list_cocktail[].Alcolise = ;
  */
}

void init_BDD_Bouteille(bar_data* bdd_bouteilles, const char**type_boisson, unsigned long* duree_conservation)
{
  bdd_bouteilles->type_boisson = type_boisson;
  for(char i=0; i<NB_BOUTEILLES; i++)
  {
    bdd_bouteilles->indice_type_boisson[i] = -1;
    bdd_bouteilles->duree_miseService[i] = 0;
    bdd_bouteilles->Etat_bouteille[i] = 0;
  }

  for(char i=0; i<NB_BOIS_ADD_MAX; i++)
  {
    bdd_bouteilles->new_boisson[i][0] = 0;
    bdd_bouteilles->duree_conservation[i] = duree_conservation[i];
  }

  bdd_bouteilles->nb_boutAdd = 0;
}


//______________________FONCTIONS BASIQUES GESTION BDD BOUTEILLE :_________________________________________

char add_bouteille(bar_data* bdd_bouteilles, char* nom, unsigned long duree_conservation)
{
  char out = 0;
  char nb_boutActuel = 0; 

  if(strlen(nom)<=MAX_BOISSON_SIZE)       // verifier cette ligne
  {
    for(char i=0; i<NB_BOIS_ADD_MAX; i++)
    {
      if(bdd_bouteilles->new_boisson[i][0] == 0)
      {  
        strcpy(bdd_bouteilles->new_boisson[i],nom);
        bdd_bouteilles->duree_conservation[NB_BOIS_INIT + i] = duree_conservation;
        bdd_bouteilles->nb_boutAdd += 1;
        break;
      }
      else
      {
        nb_boutActuel ++;
      }
    }

    if(nb_boutActuel>=NB_BOIS_ADD_MAX)
    {
      out = 1;
    }
  }    

  else
  {
    out = 2;
  }

  return out;
}       

void suppr_bouteille(bar_data* bdd_bouteilles, char indice)
{
  if(indice < NB_BOIS_ADD_MAX && indice >=0)
  {
    if(bdd_bouteilles->new_boisson[indice][0] != 0)
    {
      bdd_bouteilles->new_boisson[indice][0] = 0;
      bdd_bouteilles->nb_boutAdd -= 1;
    }
  }
}


//______________________FONCTIONS BASIQUES GESTION BDD COCKTAIL :_________________________________________


char add_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail, char* nom, char* prop, char dim_prop, boolean alcoolise)
{
  char out = 0;
  
  if(strlen(nom)<=MAX_BOISSON_SIZE)      
  {
    char nb_Cock = bdd_bouteilles->nb_cocktailActuel;
    
    if( bdd_bouteilles->nb_cocktailActuel < NB_MAX_COCK)
    {
      for(char i=0; i<(NB_MAX_COCK-NB_COCK_INIT); i++)
      {
        if(bdd_bouteilles->new_cock[i][0] == 0)
        { 
          strcpy(bdd_bouteilles->new_cock[i], nom);
          list_cocktail[NB_COCK_INIT + i].nom = bdd_bouteilles->new_cock[i];
          
          for(int j=0; j<dim_prop; j++)
          {
            bdd_bouteilles->new_cock_prop[i][j]= prop[j];
          }
          list_cocktail[NB_COCK_INIT + i].prop = bdd_bouteilles->new_cock_prop[i];
          list_cocktail[NB_COCK_INIT + i].dim_prop = dim_prop;
          list_cocktail[NB_COCK_INIT + i].Alcolise = alcoolise;
          break;
        }
      }
     
      (bdd_bouteilles->nb_cocktailActuel)++;  
      bdd_bouteilles->nb_cock_alc += alcoolise;   
      out = 0;
    }
    else
    {
      out = 1;
    }
  }    

  else
  {
    out = 2;
  }

  return out;   
}


char suppr_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail, char indice)
{
  if(indice < NB_MAX_COCK-NB_COCK_INIT && indice >=0)
  {    
    bdd_bouteilles->new_cock[indice][0] = 0;
    bdd_bouteilles->nb_cock_alc -= list_cocktail[NB_COCK_INIT+indice].Alcolise;  
    (bdd_bouteilles->nb_cocktailActuel)--; 
  }
}




    
