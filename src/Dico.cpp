/**
* @file Dico.cpp
* @brief Projet Sa� S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composant de dictionnaire et recherche dichotomique
* @date Semestre 1 P�riode B
*/

#include "Dico.h"

/**
* @brief Initialise le dictionnaire en ajoutant tous les mots du fichier
* @param[in-out] Dico& dico, r�f�rence du dico
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

	// on utilise l'allocation dynamique pour �tendre la taille du dico autant que n�cessaire
	while (in) {
		if (i >= dico.capacite) {
			/* Strat�gie de r�allocation proportionnelle au pas d'extension :
			 * initialisez la nouvelle taille du conteneur (newTaille)
			 * � i * c.pasExtension */
			unsigned int newTaille = i * dico.pasExtension;

			/* Allouez en m�moire dynamique un nouveau tableau (newT)
			 * � cette nouvelle taille*/
			Mot* newT = new Mot[newTaille];

			/* Recopiez les items d�j� stock�s dans le conteneur */
			for (unsigned int j = 0; j < dico.capacite; ++j)
				newT[j] = dico.dico[j];

			/* D�sallouez l'ancien tableau */
			delete[] dico.dico;

			/* Actualiser la mise � jour du conteneur en m�moire dynamique
			* Faites pointer le tableau support du conteneur
			* sur le nouveau tableau en m�moire dynamique */
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
* @brief R�alise une recherche dichotomique dans le dico avec un mot � trouver
* @param[in-out] Dico& dico, r�f�rence du dico
* @param[in] int taille, taille du mot
* @param[in] char mot[ALPHABET], le mot � trouver
* @return bool , true si le mot existe dans le dico , false sinon
*/
bool verif_dichotomique(Dico& dico, int taille, char mot[ALPHABET]) {
	int debut = 0; // indice de debut
	int fin = taille - 1; // indice de fin

	while (debut <= fin) // boucle de recherche
	{
		int milieu = (debut + fin) / 2; // indice du milieu 
		int resultat = strcmp(dico.dico[milieu].mot, mot); //permet de comparer deux cha�nes de caract�res et de savoir si la premi�re est inf�rieure, �gale ou sup�rieure � la seconde
		//ce qui permet de rechercher si le mot se trouve dans la premi�re moiti� du dico ou seconde moiti�
		if (resultat == 0 && strlen(dico.dico[milieu].mot) > TAILLE_MINIMALE) //si le mot existe et que la taille du mot est sup�rieure � deux lettres
		{
			return true; //le mot existe dans le dico
		}
		else if (resultat < 0) { //si le mot du milieu est inf�rieure au mot recherch�, 
			//l'indice de debut devient l'indice de milieu, ainsi l'intervalle de recherche est restreint 
			debut = milieu + 1;
		}
		else {//si le mot du milieu est sup�rieur au mot recherch�, 
			//l'indice de fin devient l'indice de milieu, ainsi l'intervalle de recherche est restreint 
			fin = milieu - 1;
		}
	}
	return false; //le mot n'existe pas dans le dico
}