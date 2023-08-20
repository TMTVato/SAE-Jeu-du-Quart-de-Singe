#ifndef DICO_H
#define DICO_H

/**
* @file Dico.h
* @brief Projet Saé S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composant de dictionnaire et recherche dichotomique
* @date Semestre 1 Période B
*/

#include <ctype.h>
#include <cctype>
#include <iostream>
#include <cstring>
#include <fstream> // pour ifstream
#include <iomanip>
#include "Enum.h"
using namespace std;

struct Mot {
	char mot[ALPHABET];
};

struct Dico {
	Mot* dico;
	unsigned int nbMot = 0;
	unsigned int capacite = 1;
	unsigned int pasExtension = PAS;
};



/**
* @brief Initialise le dictionnaire en ajoutant tous les mots du fichier
* @param[in-out] Dico& dico, référence du dico
* @return void
*/
void init_dico(Dico& dico);


/**
* @brief Réalise une recherche dichotomique dans le dico avec un mot à trouver
* @param[in-out] Dico& dico, référence du dico
* @param[in] int taille, taille du mot
* @param[in] char mot[ALPHABET], le mot à trouver
* @return bool , true si le mot existe dans le dico , false sinon
*/
bool verif_dichotomique(Dico& dico, int taille, char mot[ALPHABET]);


#endif