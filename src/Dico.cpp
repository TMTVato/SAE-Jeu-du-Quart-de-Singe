/**
* @file Dico.cpp
* @brief Projet Saé S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composant de dictionnaire et recherche dichotomique
* @date Semestre 1 Période B
*/

#include "Dico.h"

/**
* @brief Initialise le dictionnaire en ajoutant tous les mots du fichier
* @param[in-out] Dico& dico, référence du dico
* @return void
*/
void init_dico(Dico& dico) {
	dico.dico = new Mot[dico.capacite];
	ifstream in("ods4.txt"); // on ouvre le fichier
	if (!in) {
		cout << "le dictionnaire n'a pu etre ouvert" << endl;
		exit(2);
	}
	const int MAX = ALPHABET;
	char mot[ALPHABET];
	unsigned int i = 0;
	in >> setw(MAX) >> mot; // on lit le premier mot

	// on utilise l'allocation dynamique pour étendre la taille du dico autant que nécessaire
	while (in) {
		if (i >= dico.capacite) {
			/* Stratégie de réallocation proportionnelle au pas d'extension :
			 * initialisez la nouvelle taille du conteneur (newTaille)
			 * à i * c.pasExtension */
			unsigned int newTaille = i * dico.pasExtension;

			/* Allouez en mémoire dynamique un nouveau tableau (newT)
			 * à cette nouvelle taille*/
			Mot* newT = new Mot[newTaille];

			/* Recopiez les items déjà stockés dans le conteneur */
			for (unsigned int j = 0; j < dico.capacite; ++j)
				newT[j] = dico.dico[j];

			/* Désallouez l'ancien tableau */
			delete[] dico.dico;

			/* Actualiser la mise à jour du conteneur en mémoire dynamique
			* Faites pointer le tableau support du conteneur
			* sur le nouveau tableau en mémoire dynamique */
			dico.dico = newT;

			/* Actualisez la taille du conteneur */
			dico.capacite = newTaille;
		}
		++dico.nbMot;
		strcpy_s(dico.dico[i].mot, mot); //on copie le mot dans le dico
		in >> setw(MAX) >> mot; // on lit le mot suivant
		++i;
	}
	in.close(); // on ferme le fichier
}


/**
* @brief Réalise une recherche dichotomique dans le dico avec un mot à trouver
* @param[in-out] Dico& dico, référence du dico
* @param[in] int taille, taille du mot
* @param[in] char mot[ALPHABET], le mot à trouver
* @return bool , true si le mot existe dans le dico , false sinon
*/
bool verif_dichotomique(Dico& dico, int taille, char mot[ALPHABET]) {
	int debut = 0; // indice de debut
	int fin = taille - 1; // indice de fin

	while (debut <= fin) // boucle de recherche
	{
		int milieu = (debut + fin) / 2; // indice du milieu 
		int resultat = strcmp(dico.dico[milieu].mot, mot); //permet de comparer deux chaînes de caractères et de savoir si la première est inférieure, égale ou supérieure à la seconde
		//ce qui permet de rechercher si le mot se trouve dans la première moitié du dico ou seconde moitié
		if (resultat == 0 && strlen(dico.dico[milieu].mot) > TAILLE_MINIMALE) //si le mot existe et que la taille du mot est supérieure à deux lettres
		{
			return true; //le mot existe dans le dico
		}
		else if (resultat < 0) { //si le mot du milieu est inférieure au mot recherché, 
			//l'indice de debut devient l'indice de milieu, ainsi l'intervalle de recherche est restreint 
			debut = milieu + 1;
		}
		else {//si le mot du milieu est supérieur au mot recherché, 
			//l'indice de fin devient l'indice de milieu, ainsi l'intervalle de recherche est restreint 
			fin = milieu - 1;
		}
	}
	return false; //le mot n'existe pas dans le dico
}