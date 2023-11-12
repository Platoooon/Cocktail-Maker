// !!!!  Penser à inclure les librairies sur le PC (dernières versions)  !!!!

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
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


#define TFT_CS 28
#define TFT_DC 26
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

//size screen(320,240);

int X0 = 20;
int Y0 = 50;
int largeur = 250;
int hauteur = 40;
int color = ILI9341_WHITE;
int text_color = ILI9341_BLACK;



void drawBtn(int X0, int Y0, int largeur, int hauteur, int color, int text_color, const char* text)
{ 
  tft.fillRect(X0, Y0, largeur, hauteur, color);
  tft.drawRect(X0, Y0, largeur, hauteur, ILI9341_BLACK);
  
  int decalage = 6*(strlen(text)-1);
  tft.setCursor(X0+120-decalage, Y0+12);
  tft.setTextColor(text_color);
  tft.setTextSize(2);
  tft.println(text);
}

void drawBack()
{
  tft.drawRect(15, 10, 30, 30, ILI9341_BLACK);
  tft.fillRect(30, 22, 10, 6, ILI9341_BLACK);
  tft.fillTriangle(20,25,30,15,30,35,ILI9341_BLACK);
}

//  !!  ici on passe par un pointeur pour tester !!

void scrollUp(Adafruit_ILI9341* Test)
{
  Test->drawRect(145, 10, 30, 30, ILI9341_BLACK);
  Test->fillTriangle(160,15,150,30,170,30,ILI9341_BLACK);
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



void menuDeroulant()
{
  drawBtn(X0, Y0, largeur, hauteur, color, text_color, "Creme cacao blanche");
  drawBtn(X0, Y0+50, largeur, hauteur, color, text_color, "Meissa Seck");
  drawBtn(X0, Y0+100, largeur, hauteur, color, text_color, "SECK");
  drawBack();
  scrollUp(&tft);
  scrollDown(&tft);
  Exit(&tft);
}

void setup(void)
{
  Serial.begin(9600);
  tft.begin();

  tft.fillScreen(ILI9341_LIGHTGREY);
  // origin = left,top landscape (USB left upper)
  tft.setRotation(1); 
  tft.setScrollMargins(200,200);

  // _______test :______________________________________________________________________   
  menuDeroulant();

}

void loop()
{
 
}
