#ifndef JEU_H
#define JEU_H

/**
* @file Jeu.h
* @brief Projet Saé S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composants pour le déroulement du jeu
* @date Semestre 1 Période B
*/

#include <ctype.h>
#include <cctype>
#include <iostream>
#include <cstring>
#include "Dico.h"
#include "Joueur.h"
using namespace std;



struct Jeu {
	unsigned int nbLettre = 0;
	char* mot;
	unsigned int nbJoueur;
	Joueur* joueurs;
};


/**
* @brief Initialise la partie et les joueurs
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] char** argv, pour obtenir le nombre de joueurs
* @return void
*/
void initialiser(Jeu& jeu, char** argv);


/**
* @brief Initialise la partie et les joueurs
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] char** argv, pour obtenir le nombre de joueurs
* @return void
*/
void initialiser(Jeu& jeu, char** argv);


/**
* @brief Entrez le mot à saisir et affiche si le mot existe ou pas ou si le mot commence par les mêmes lettres
* @param[in-out] Jeu& jeu, Dico& dico, référence du jeu et du dico
* @param[in] unsigned int& i, position du joueur
* @return int, 0 pour sortir de la fonction
*/
void bluff(Jeu& jeu, unsigned int& i, Dico& dico);


/**
* @brief Affiche que le mot existe s'il a été trouvé
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] unsigned int& i, position du joueur
* @return void
*/
void trouver(Jeu& jeu, unsigned int i);


/**
* @brief Vérifie si un joueur à 4 quart de singe
* @param[in-out] Jeu& jeu, référence du jeu
* @return bool, true si un joueur à 4 quarts de singe et false sinon
*/
bool eliminer(Jeu& jeu);


/**
* @brief Affiche que le joueur abandonne la manche
* @param[in-out] Jeu& jeu, référence du jeu, Joueur* joueurs, pointeur sur les joueurs
* @param[in] unsigned int i, position du joueur
* @return void
*/
void surrend(Jeu& jeu, Joueur* joueurs, unsigned int i);

/**
* @brief Affiche la situation actuelle de la partie avec le mot et le joueur courant
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] unsigned int i, la position du joueur
* @return void
*/
void afficher(Jeu& jeu, unsigned int i);

/**
* @brief Affiche la situation actuelle de la partie avec le nombre de points des joueurs
* @param[in-out] Jeu& jeu, référence du jeu
* @return void
*/
void afficher_manche(Jeu& jeu);

/**
* @brief Devient le joueur précédent
* @param[in-out] Jeu& jeu, référence du jeu, unsigned int& i, position du joueur
* @return void
*/
void joueurPrecedent(Jeu& jeu, unsigned int& i);


/**
* @brief Vérifie si un joueur à 4 quart de singe
* @param[in-out] Jeu& jeu, référence du jeu
* @return bool, true si un joueur à 4 quarts de singe et false sinon
*/
bool eliminer(Jeu& jeu);

/**
* @brief Réalise une copie du mot de la manche
* @param[in-out] char*& mot, référence du mot de la manche
* @param[in] int taille, taille du mot
* @return void
*/
void Copie(char*& mot, int taille);


/**
* @brief Vérifie si le mot rentré à bien les mêmes lettres que le mot de la manche
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] char mot[ALPHABET], le mot rentré
* @return bool , true si le mot commence par les mêmes lettres , false sinon
*/
bool verif2(char mot[ALPHABET], Jeu& jeu);


/**
* @brief Réinitialise le mot de la manche
* @param[in-out] Jeu& jeu, référence du jeu
* @return void
*/
void reset_mot(Jeu& jeu);

#endif