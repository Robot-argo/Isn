// On commence par incule les librairies 

#include <Adafruit_NeoPixel.h> // controle color ring 
#include <SoftwareSerial.h>// controle bluetooth 
#include<Servo.h> // controle du servo moteur 
#include<AFMotor.h>





//********************************************************************************************************
//********************************** Déclaration des pins ************************************************
//********************************************************************************************************

// module ultrason 

char DOUT_TRIGGER = 0; 
char DIN_ECHO = 0;

//moteurs

AF_DCMotor 



// initiallisation de la librairie Neopixel 

#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN            0  // PIN sera remplacé par 2 
#define NUMPIXELS      8  // NUMPIXEL sera remplacé par 8 (nombre de pixel a controler) 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);



// servo 

  Servo servo_m; // Déclaration du servo qu'on nomme servo_m 
  int position_du_servo = 0;  // variable position du servo 
  const int pin_servo = 0; 


// BLUETOOTH

SoftwareSerial HC06(8,9);
String message;





//********************************************************************************************************
//********************************** Fonctions e/r ultrason  *********************************************
//********************************************************************************************************

float mesurer() {
  float distance; 
  
  digitalWrite(DOUT_TRIGGER, LOW); //On met le pin TRIGGER en LOW
  delayMicroseconds(2); // on attend 2 microsecondes
  digitalWrite(DOUT_TRIGGER, HIGH); //On met le pin TRIGGER en HIGH 
  delayMicroseconds(10); //on attend 10 microsecondes 
  digitalWrite(DOUT_TRIGGER, LOW); //retours à LOW

// On mesure la duréé de l'impulsion sur ECHO et on la converti en cm 
  distance = pulseIn(DIN_ECHO, HIGH) / 58.0; 

  return distance; 
  }


//********************************************************************************************************
//********************************** Fonctions pour le servo *********************************************
//********************************************************************************************************


//fonction pour faire tourner le servo 0 a gauche et 1 a droite; 
void servo_tourner(int variable){
  if (variable == 0){
    for(position_du_servo = 0; position_du_servo< 180; position_du_servo++){
      servo_m.write(position_du_servo); 
      delay(1); 
      
    }
  }

  else {
        for(position_du_servo = 180; position_du_servo>=0; position_du_servo--){
      servo_m.write(position_du_servo); 
      delay(1); }
      }
       }



//********************************************************************************************************
//********************************** Fonctions de detection  *********************************************
//********************************************************************************************************

// fonction pour voir si il y a un obstacle 0 a gauche et 1 a droite 
// la fonction renvoie 0 si il n'y a rien et 1 si il y a un obstacle 


int obstacle(int sens){

  int distance_min = 15; 

  if (sens == 0){
     regard_tourne(0); 
  servo_tourner(0); 
  delay(100); 

  if (mesurer <= distance_min){
    return 1;  }
    
    else {
    return 0; 
  }
 }

  else{

     regard_tourne(1); 
  servo_tourner(1); 
  delay(100); 

  if (mesurer <= distance_min){
    return 1;  }
    
    else {
    return 0; 
  }
    
  }
  }

//********************************************************************************************************
//**********************************     Fonctions NEOPIXEL    *******************************************
//********************************************************************************************************
    
// fonction pour allumer un pixel pix d'une certaine couleur (melange rgb) 
void allumer_pixel(int pix, int red, int green, int blue){

  pixels.setPixelColor(pix, pixels.Color(red, green, blue)); 
   pixels.show();// allume le pixel 
  
}



// fonction pour allumer tout le led ring

void allumer_ring(int red, int green, int blue){

//boucle avec la fonction allumer pixel 
// NUMPIXEL est le nombre de pixel sur un led ring 
 for(int i = 0; i < NUMPIXELS; i++){
   allumer_pixel(i, red, green, blue); 
  }
}


// fonction pour eteindre 
void eteindre(){
  allumer_ring(0, 0 , 0); // allume la led ring en 0 
  
}

void couleur_hasard(){
// on choisis des nombres au hasar qui vont correspondre a une couleur 
  int red = random(0, 255); 
  int blue = random(0, 255); 
  int green = random (0, 255);

  allumer_ring(red, green, blue);
}



void setup() {
//********************************************************************************************************
//***************************************** Initialisation************************************************
//********************************************************************************************************

pinMode(DOUT_TRIGGER, OUTPUT); // initialisé en tant que sortie
pinMode(DIN_ECHO, INPUT); // initialiisé en tant qu'entrée 


//--------------------------------------




#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin(); 
    Serial.begin(9600);
  HC06.begin(9600);  
  pinMode(DOUT_LED, OUTPUT);
  digitalWrite(DOUT_LED, LOW);


  // Servo moteur 

servo_m.attach(pin_servo);
servo_m.write(position_du_servo); 

}





void loop() {

  while(HC06.available()) {

    delay(3); 
    char c = HC06.read(); 
    message+= c; }

    if(message.length() > 0){
      Serial.println(message); 
      if (message == "LED")
      {
  }

}
