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



/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces
#define domino_drop 1000


/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void ligne_droite(){
  
}

void asservissement_intervalle(int dist)
{
  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);

  while (ENCODER_Read(0) < dist)
  {

  float vd = 0.3, vgi = 0.35;
  float vg = vgi;
  float CE;
  #define kp  0.0001;
  #define ki  0.00002;

  MOTOR_SetSpeed(1, vd);
  MOTOR_SetSpeed(0, vg);
  delay(100);

  CE = ENCODER_Read(1) - ENCODER_Read(0);

  vg = vg + CE*kp;

  MOTOR_SetSpeed(1, 0);
  MOTOR_SetSpeed(0, 0);
  delay(domino_drop);
 }
}


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
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(10);// Delais pour décharger le CPU
}