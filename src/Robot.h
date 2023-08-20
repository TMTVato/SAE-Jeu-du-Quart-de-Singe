#ifndef ROBOT_H
#define ROBOT_H

/**
* @file Robot.h
* @brief Projet Sa� S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composants pour les choix du robot
* @date Semestre 1 P�riode B
*/

#include <cstdlib>
#include <ctime>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "Jeu.h"


/**
* @brief Renvoie le choix du robot selon l'�tat de la partie
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @return char : une lettre ou "?" pour appeller bluff
*/
char robot_choix(Jeu& jeu, Dico& dico);


/**
* @brief Renvoie un caract�re selon le nombre de mots que l'on peut former avec le mot du jeu
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @return char, un caract�re
*/
char verif_robot(Jeu& jeu, Dico& dico);


/**
* @brief Renvoie le choix du robot lorsqu'il se fait bluff
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @param[in] unsigned int y, position du joueur pr�c�dent
* @return char*, le mot trouv� dans le dico ou "!" si le robot ne trouve rien
*/
char* robot_choix_bluff(Jeu& jeu, Dico& dico, unsigned int y);


#endif