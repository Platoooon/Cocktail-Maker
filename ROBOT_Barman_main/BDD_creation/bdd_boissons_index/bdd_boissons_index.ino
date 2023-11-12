
String boissons[80] = {
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
                      "Jus de pamplemousse",
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
                      
                      "Sirop de granadine",
                      "Sirop de canne",
                      "Curacao",          
                         
                      "Amaretto",
                      "Creme de casis",
                      "Creme de menthe",
                      "Fernet Branca",
                      "Creme de banane",
                      "Creme de cacao blanche",
                      "Liquore galliano",
                      "Liqueur de cafe",    
                      "Apricot brandy",
                      "Sherry brandy",
                      "Kirsh",
                      "Drambuie",
                      "Advokaat",  
                      
                      "Eau",                         
                     };
                     
void setup() {
  Serial.begin(9600);
  for(int i=0; i<48; i++)
  {
    Serial.print(1%2);
    Serial.print("   ");
    Serial.println(boissons[i]);
  }
}

void loop() {


}
