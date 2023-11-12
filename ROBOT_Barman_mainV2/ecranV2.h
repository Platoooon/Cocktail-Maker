#ifndef ecranV2_h
#define  ecranV2_h

#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ILI9341.h>
#include <TouchScreen.h>

//Touchscreen X+ X- Y+ Y- pins
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 22  // can be a digital pin
#define XP 24  // can be a digital pin

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 100
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 50
#define MAXPRESSURE 100000

// DIMENSIONS X = 320 & Y = 240 


#define TFT_CS 28
#define TFT_DC 26

int* coordTactile(Adafruit_ILI9341* tft, TouchScreen* ts);

//____________________Fonctions élémentaires________________________________________________________
void drawBtn(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char* text);
void drawBtn1(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char* text);
void drawBtnClavier(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char text);
void drawTexteClavier(Adafruit_ILI9341* tft, int X0, int Y0, int largeur, int hauteur, int color, int text_color, char* text, int nbLettres);

void drawBack(Adafruit_ILI9341* tft);

void scrollUp(Adafruit_ILI9341* tft);

void scrollDown(Adafruit_ILI9341* tft);

void Exit(Adafruit_ILI9341* tft);

void Enter(Adafruit_ILI9341* tft, int x, int y);

void Delete(Adafruit_ILI9341* tft, int x, int y);

void Maj(Adafruit_ILI9341* tft, int x, int y);

void OUI_NON(Adafruit_ILI9341* tft);

void compteur_perso(Adafruit_ILI9341* tft, char nbSelec);

//____________________Fonctions dessin pages________________________________________________________
void menuDeroulant(Adafruit_ILI9341* tft, char* text0, char* text1, char* text2, float ratio);

void ecranAccueil(Adafruit_ILI9341* tft);

void service(Adafruit_ILI9341* tft);
void reglages(Adafruit_ILI9341* tft);

void message_err_fav(Adafruit_ILI9341* tft);
void message_err_fav1(Adafruit_ILI9341* tft);

char validFavoris(Adafruit_ILI9341* tft, TouchScreen* ts, char nb_Favorite_Cock, char indexAlcool, char* Favorite_Cock);
char supprFavoris(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_selec);

void selection_alc(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_trouve);
void selection_NON_alc(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_trouve);

void appui_supprCock(Adafruit_ILI9341* tft, TouchScreen* ts, char* nb_Favorite_Cock, char* Favorite_Cock, char alcool_selec);

char choixProp(Adafruit_ILI9341* tft, TouchScreen* ts, char* lastProp, char nbBoutSelec);
void selection_prerso(Adafruit_ILI9341* tft, TouchScreen* ts, char num_bouton, char* nbBoutSelec, int index_Deroulant, char* prop);

void changement_bout(Adafruit_ILI9341* tft);

char clavier(Adafruit_ILI9341* tft, TouchScreen* ts, char* nom);

#endif
