#ifndef ROBOT_Barman_h
#define  ROBOT_Barman_h

#include <Arduino.h>


#define NB_BOUTEILLES 7

#define NB_BOIS_INIT 50
#define NB_BOIS_ADD_MAX 20          //  max boissons ajoutées
#define MAX_BOISSON_SIZE 20          //  max caractere boissons ajoutées


#define NB_MAX_COCK 90              //  >=  au nombre de cocktails dans init_cocktail
#define NB_COCK_INIT 6              // penser a modifier

struct bar_data
{
  //________________________________BOISSONS BASE DE DONNEES :____________________________
	char nb_boissonsInit;
	char**type_boisson;  
  char new_boisson[NB_BOIS_ADD_MAX][MAX_BOISSON_SIZE];                                                  // new_boisson[i][0] = 0 pas de boisson enregistrée sur i  ->  Flemme de faire une liste chaînée
                                            
  unsigned long duree_conservation[NB_BOIS_INIT + NB_BOIS_ADD_MAX];                                               //  !! nb_boissons init du main + NB_BOIS_ADD_MAX !!

  //________________________________COCKATAIL BASE DE DONNEES :____________________________
  char nb_cocktailActuel;
  char new_cock[NB_MAX_COCK-NB_COCK_INIT][MAX_BOISSON_SIZE];

  //________________________________BOISSONS INSTALLEES  <=  NB_BOUTEILLES :_______________
  char indice_type_boisson[NB_BOUTEILLES];               //   =-1 signifie pas de bouteilles
  unsigned long duree_miseService[NB_BOUTEILLES]; 
  boolean Etat_bouteille[NB_BOUTEILLES];
  
  // indice type_boisson ; durée ; Position ; Etat(rempli/vide)    ===>  Il reste position : numeros, coordonées,.. ?
};




struct cocktail{
   char* nom;
   char* prop;
   char dim_prop;
   boolean Alcolise;
};





void init_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail);
void init_BDD_Bouteille(bar_data* bdd_bouteilles, const char**type_boisson, unsigned long* duree_conservation);

char add_bouteille(bar_data* bdd_bouteilles, const char* nom, unsigned long duree_conservation);
void suppr_bouteille(bar_data* bdd_bouteilles, char indice);

char add_cocktail(cocktail* list_cocktail, const char* nom, char* prop, char dim_prop);
char suppr_cocktail(cocktail* list_cocktail, char indice);

#endif
