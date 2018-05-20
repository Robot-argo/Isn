#include<Servo.h> // controle du servo moteur 
#include <SoftwareSerial.h>// controle bluetooth 



// BLUETOOTH

SoftwareSerial HC06(12,11);
String message;


Servo servo_m; // Déclaration du servo qu'on nomme servo_m 
  int position_du_servo = 90;  // variable position du servo 
  const int pin_servo = 10; 
  
  int buzzer = 4;
int bouton_led = 6; 
int led_reservoir = 5;

  //fonction pour faire tourner le servo 0 a gauche et 1 a droite; 
void tourner(int variable){
  if (variable == 0){
    for(position_du_servo = 0; position_du_servo< 180; position_du_servo++){
      servo_m.write(position_du_servo); 
      delay(4); 
      
    }
  }

  else {
        for(position_du_servo = 180; position_du_servo>=0; position_du_servo--){
      servo_m.write(position_du_servo); 
      delay(4); }
      }
       }

       
void allumage(){

digitalWrite(led_reservoir, HIGH); 
digitalWrite(bouton_led, HIGH); 
tone (buzzer, 1090, 250);
delay(80); 
digitalWrite(bouton_led, LOW); 
delay(80); 
digitalWrite(bouton_led, HIGH); 
tone (buzzer, 1800, 250);

delay(1000); 



for(int i = 100; i< 200; i++){
  tone(buzzer, i, i-(i/2));
  delay(10);
  
}
delay(500);

tone (buzzer, 1090, 250);
digitalWrite(bouton_led, LOW); 
delay(80); 
digitalWrite(bouton_led, HIGH); 
tone (buzzer, 1800, 250);
digitalWrite(led_reservoir, LOW); 
}
void setup() {
pinMode(3,OUTPUT); 
pinMode(4, OUTPUT); 
pinMode(5, OUTPUT); 
pinMode(8, OUTPUT); 

 Serial.begin(9600);
  HC06.begin(9600); 




allumage();

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
        
digitalWrite(led_reservoir, HIGH); 

     }
      }

      

  
tourner (1);

delay(2000);


tourner(0);


delay(2000);
}
