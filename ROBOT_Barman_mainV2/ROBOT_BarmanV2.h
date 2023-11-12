#ifndef ROBOT_BarmanV2_h
#define  ROBOT_BarmanV2_h

#include <Arduino.h>


#define NB_BOUTEILLES 5

#define NB_BOIS_INIT 49             //  !! dim : tableau concstant du main !! 
#define NB_BOIS_ADD_MAX 20          //  max boissons ajoutées
#define MAX_BOISSON_SIZE 20         //  max caractere boissons ajoutées


#define NB_MAX_COCK 90              //  >=  au nombre de cocktails dans init_cocktail
#define NB_COCK_INIT 9              // penser a modifier

struct bar_data
{
  //________________________________BOISSONS BASE DE DONNEES :____________________________
	char**type_boisson;  
  char new_boisson[NB_BOIS_ADD_MAX][MAX_BOISSON_SIZE];                                                      // new_boisson[i][0] = 0 pas de boisson enregistrée sur i  ->  Flemme de faire une liste chaînée
  char nb_boutAdd;                                          
  unsigned long duree_conservation[NB_BOIS_INIT + NB_BOIS_ADD_MAX];                                         //  !! nb_boissons init du main + NB_BOIS_ADD_MAX !!

  //________________________________COCKATAIL BASE DE DONNEES :____________________________
  char nb_cocktailActuel;
  char nb_cock_alc;
  char new_cock[NB_MAX_COCK-NB_COCK_INIT][MAX_BOISSON_SIZE];                                                // new_cock[i][0] = 0 pas de cocktail enregistrée sur i
  char new_cock_prop[NB_MAX_COCK-NB_COCK_INIT][2*4];                                                        // 2(index+quantité) * 4 boisson 

  //________________________________BOISSONS INSTALLEES  <=  NB_BOUTEILLES :_______________
  char indice_type_boisson[NB_BOUTEILLES];                                                                  //   = -1 signifie pas de bouteilles
  unsigned long duree_miseService[NB_BOUTEILLES]; 
  boolean Etat_bouteille[NB_BOUTEILLES];                                                                    //   = 0 bouteille vide
  
             //   ===>  Il reste position : numeros, coordonées,.. ?
};


struct cocktail{
   char* nom;
   char* prop;
   char dim_prop;
   boolean Alcolise;
};



void init_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail);
void init_BDD_Bouteille(bar_data* bdd_bouteilles, const char**type_boisson, unsigned long* duree_conservation);

char add_bouteille(bar_data* bdd_bouteilles, char* nom, unsigned long duree_conservation);
void suppr_bouteille(bar_data* bdd_bouteilles, char indice);                                                    // Peut être inutile puisque certains cocktails présenteront un problème
char add_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail, char* nom, char* prop, char dim_prop, boolean alcoolise);
char suppr_cocktail(bar_data* bdd_bouteilles, cocktail* list_cocktail, char indice);                            // Peut être inutile puisque certains cocktails sont en favoris

#endif
