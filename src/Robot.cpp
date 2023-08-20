/**
* @file Robot.cpp
* @brief Projet Sa� S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composants pour les choix du robot
* @date Semestre 1 P�riode B
*/

#include "Robot.h"
#pragma warning(disable: 4996);

/**
* @brief Renvoie le choix du robot selon l'�tat de la partie
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @return char : une lettre ou "?" pour appeller bluff
*/
char robot_choix(Jeu& jeu, Dico& dico) {
	if (jeu.nbLettre == 0) { //si c'est le robot qui doit mettre la premi�re lettre
		return 'A' + rand() % ('Z' - 'A' + 1); //renvoie une lettre al�atoire
	}
	char result = verif_robot(jeu, dico); //appel fonction verif_robot(jeu, dico) pour avoir le choix du robot
	if (isalpha(result)) { //si le caract�re est une lettre 
		return result; // renvoie la lettre
	}
	else { //sinon si le caract�re renvoy� n'est pas une lettre
		return '?'; //renvoie "?" pour que le robot bluff
	}


}

/**
* @brief Renvoie un caract�re selon le nombre de mots que l'on peut former avec le mot du jeu
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @return char, un caract�re
*/
char verif_robot(Jeu& jeu, Dico& dico) {
	//Un tableau de 26 entiers, un pour chaque lettre de l'alphabet 
	int lettreCount[ALPHABET] = { 0 };
	int max_lettre = lettreCount[0];
	int taille = strlen(jeu.mot); //pour avoir la taille du pr�fixe du mot dans le jeu
	for (unsigned int i = 0; i < dico.nbMot; ++i) {
		if (strncmp(dico.dico[i].mot, jeu.mot, taille) == 0) { //permet de comparer deux cha�nes de caract�res et de savoir si la premi�re est �gale � la seconde selon une taille pr�cise 
			char c = dico.dico[i].mot[taille]; //lettre juste apr�s la taille du pr�fixe
			lettreCount[c - 'A']++; //plus un � la position du tableau de la lettre trouv�e
		}
	}
	//On cherche la lettre avec le plus d'occurrence
	for (int i = 0; i < ALPHABET; i++) {
		if (max_lettre < lettreCount[i]) {
			max_lettre = lettreCount[i];
		}
	}
	//le compteur v�rifie s'il y a une lettre ou plus dans le tableau
	int cpt = 0;
	for (int i = 0; i < ALPHABET; i++) {
		if (lettreCount[i] > 0)
			cpt++;
	}
	//si le cpt est �gal � 0 ou 1, on ne pourra former un mot avec qu'une seule lettre

	if (max_lettre > SEUIL) { // le seuil � laquel le robot "?" ou pas 
		for (int i = 0; i < ALPHABET; i++) {

			if (max_lettre == lettreCount[i]) { //le robot essaie de renvoyer la lettre avec le plus d'occurrence
				char result[ALPHABET] = "";
				strcpy(result, jeu.mot);
				result[jeu.nbLettre] = char('A' + i); //forme le mot du jeu avec la lettre 
				if (verif_dichotomique(dico, dico.nbMot, result) == false || cpt <= 1) //v�rifie si le mot form� existe ou pas et que l'on peut former un mot avec plus qu'une seule lettre
					return char('A' + i); //renvoie la lettre avec le plus d'occurrence

				else { //sinon le robot essaie de renvoyer une lettre al�atoire avec une occurrence non nulle

					int j = rand() % ALPHABET + 1; // position de la lettre choisie al�atoirement...
					int cpt1 = 0;
					while (verif_dichotomique(dico, dico.nbMot, result) == true) { //v�rifie, tant que le mot form� existe, on utilise une lettre diff�rente 
						if (lettreCount[j] > 0) { //si la lettre a au moins une occurrence
							result[jeu.nbLettre] = char('A' + j); //teste la lettre dans le mot form�
							cpt1++;// compte le nombre de tour de boucle 
						}
						else {
							j = rand() % ALPHABET + 1; // position d'une lettre al�atoire
						}
						if (cpt1 >= SEUIL) { // rand n'est pas compl�tement al�atoire donc 
							//cela pose un probl�me quand le programme ne tombe jamais sur une lettre avec au moins une occurrence
							//on arr�te selon un seuil le choix semi-al�atoire et on parcours juste le tableau jusqu'� tomber sur une lettre avec au moins une occurrence
							for (unsigned int j = 0; j < ALPHABET; ++j) {
								if (lettreCount[j] > 0) {
									result[jeu.nbLettre] = char('A' + j);
									if (verif_dichotomique(dico, dico.nbMot, result) == false) {//v�rifie si le mot form� existe ou pas 
										char resulta = char('A' + j);
										j = 0;
										return resulta;//renvoie la premi�re lettre trouv�e avec au moins une occurrence
									}

								}
							}
						}
					}
					char resulta = char('A' + j);
					j = 0;
					return resulta; //renvoie la lettre al�atoirement trouv�e
				}
			}
		}
	}
	else {
		return char(max_lettre); // renvoie un caract�re, pr�f�rablement qui n'est pas une lettre 
	}
}



/**
* @brief Renvoie le choix du robot lorsqu'il se fait bluff
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @param[in] unsigned int y, position du joueur pr�c�dent
* @return char*, le mot trouv� dans le dico ou "!" si le robot ne trouve rien
*/
char* robot_choix_bluff(Jeu& jeu, Dico& dico, unsigned int y) {
	int taille = strlen(jeu.mot);
	for (unsigned int i = 0; i < dico.nbMot; ++i) {
		//permet de comparer deux cha�nes de caract�res et de savoir si la premi�re est �gale � la seconde selon une taille pr�cise 
		//si un mot existe avec ce pr�fixe (= le mot du jeu) et que la taille du mot est sup�rieure � deux lettres
		if (strncmp(dico.dico[i].mot, jeu.mot, taille) == 0 && strlen(dico.dico[i].mot) > TAILLE_MINIMALE) {
			return dico.dico[i].mot; //renvoie le mot trouv� dans le dico
		}
	}
	char str[] = "!";
	return str; //renvoie "!" pour abandonner si le robot ne trouve rien 
}