/*
Projet: parcours domino
Equipe: P20
Auteurs: Etienne, Victo, Kat
Description: Programmation des parcours suivies par le robot
Date: 03-11-18
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <arduino.h>


/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces
#define domino_drop 1000
const float distance_dominos_reelle = 2;
const float circonferenceRoue = 24.19;

const float circonferenceCercleUneRoue = 116.43;  
const float circonferenceCercleDeuxRoues = 58.119;
const float distance_2Roues = 18.5;
const long pulses = 3200;
#define buttonPin1 53
#define buttonPin2 54
#define buttonPin3 55
#define GoPin 56

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */

void ligne_droite(float dominos){ // nombre de dominos a placer

  long distance_dominos_encodeur = (distance_dominos_reelle)/circonferenceRoue * pulses; // distance entre 2 dominos
  long distance_parcours = distance_dominos_reelle; // compteur pour la ligne
  float vd = 0.2, vg = 0.2; // vitesses initiales
  while (distance_parcours <= (dominos*5)){ //boucle pour compteur de dominos -> distance totale
    ENCODER_ReadReset(0);
    ENCODER_ReadReset(1);
    while (ENCODER_Read(0) < distance_dominos_encodeur){  //boucle entre 2 dominos (asservissement)

      MOTOR_SetSpeed(1, vd);
      MOTOR_SetSpeed(0, vg);
      delay(20);
      
      void tourner2(float degre){
        double distance = degre/360 * circonferenceCercleDeuxRoues;
        double pulses = distance/circonferenceRoue * Encodeur_roue;
        if (pulses<0){
          pulses *= -1;
        }
        ENCODER_Reset(1);
        ENCODER_Reset(0);
        if (distance>0){
        MOTOR_SetSpeed(0, -vitesseVirageT);
        MOTOR_SetSpeed(1, vitesseVirageT);
        asservissementT(pulses, -vitesseVirageT, vitesseVirageT);
        }
        if (distance<0){
        MOTOR_SetSpeed(0, vitesseVirageT);
        MOTOR_SetSpeed(1, -vitesseVirageT);
        asservissementT(pulses, vitesseVirageT, -vitesseVirageT);
        }
        
      void asservissementT(double pulses, float vitesseG, float vitesseD){
        bool activationDesRoues=true;
        delay(50);
        while (activationDesRoues){
          long pulsesG = ENCODER_Read(0);
          long pulsesD = ENCODER_Read(1);
          if (pulsesG<0){
            pulsesG = pulsesG * -1;
          }
          if (pulsesD<0){
            pulsesD = pulsesD * -1;
          }
          if (pulsesG >= pulses || pulsesD >= pulses){
            activationDesRoues = false;
          }
          float ratio = (pulsesG/pulsesD);
          float vitesseDcorrigee = vitesseD*ratio;
          MOTOR_SetSpeed(1, vitesseDcorrigee);
          MOTOR_SetSpeed(0, vitesseG);
          if (ROBUS_IsBumper(2)){
            activationDesRoues = false;
          }
        }
  MOTOR_SetSpeed(1, 0);
  MOTOR_SetSpeed(0, 0);
}
    
      long pulsesG = ENCODER_Read(0);
      long pulsesD = ENCODER_Read(1);
      long erreur = (pulsesD - pulsesG)*0.0001;

      float vg = (vg + erreur);
      MOTOR_SetSpeed(1, vd);
      MOTOR_SetSpeed(0, vg);

    }
    MOTOR_SetSpeed(1, 0);
    MOTOR_SetSpeed(0, 0);
    delay(domino_drop);    // temps pour placer les dominos
    distance_parcours += distance_dominos_reelle;
  }
}

/*void parcours(int deplacement[6]){    // fonction qui fait le parcours inventé par l'utilisateur
  int x = 0;
  while (x<5){        // un maximum de 5 déplacements de suite
    if (deplacement[x] == 0)
      return 0;
    if (deplacement[x] == 1){
      ligne_droite(20);
    }
    if (deplacement[x] == 2){
      tourner_droite(******);
    }
    if (deplacement[x] == 3){
      tourner_gauche(******);
    }
    x++;
  }
}*/

/*void parcours_spirale_carree(){
    delay(1000);
    ligne_droite(76.9375);
    tourner(90,0);
  
    for (int dominos=3, dominos<=300 || dominos*distance_dominos_reelle<160 , dominos+3){
        ligne_droite(dominos);
        tourner(90,0);  
        ligne_droite(dominos);
        tourner(90,0);  
    }*/

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();
}


/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  int x = 0;
  int deplacement[6]={0,0,0,0,0};
  if (button2 == 1) {
    int go = 0;
    for (int i=0; i<10; i++){
      go = i;
    }
    if (go == 10){
      while (x<5){          // un maximum de 5 déplacements de suite
        int button1 = digitalRead(buttonPin1);    //bouton ligne droite
        int button2 = digitalRead(buttonPin2);    //bouton tourner droite
        int button3 = digitalRead(buttonPin3);    //bouton tourner gauche

        if (button1 == 1) {
          int go = 0;
          for (int i=0; i<10; i++){
            go = i;
          }
          if (go == 10){
            deplacement[x] = 1;
            Serial.println("LIGNE");
            x += 1;
          }
        }
        if (button2 == 1) {
          int go = 0;
          for (int i=0; i<10; i++){
            go = i;
          }
          if (go == 10){
            deplacement[x] = 2;
            Serial.println("DROITE");
            x += 1;
          }
        }
        if (button3 == 1) {
          int go = 0;
          for (int i=0; i<10; i++){
            go = i;
          }
          if (go == 10){
            deplacement[x] = 3;
            Serial.println("GAUCHE");
            x += 1;
          }
        }
        if (GoPin == 1){       // pour commencer le parcours avec moins de 5 déplacements
          int go = 0;
          for (int i=0; i<10; i++){
            go = i;
          }
          if (go == 10){
            //parcours(deplacement);
            Serial.println("GOOOOOO");
          }
        }
      }
    }
  Serial.println("//////////////////");
  int y = 0;
  while (y<5){
    Serial.println(deplacement[y]);
    y += 1;
  }
  if (GoPin == 1){       // pour commencer le parcours avec 5 déplacements
      //parcours(deplacement);
      Serial.println("GOOOOOO");
    }
}
