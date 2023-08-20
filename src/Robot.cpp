/**
* @file Robot.cpp
* @brief Projet Saé S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composants pour les choix du robot
* @date Semestre 1 Période B
*/

#include "Robot.h"
#pragma warning(disable: 4996);

/**
* @brief Renvoie le choix du robot selon l'état de la partie
* @param[in-out] Jeu& jeu, Dico& dico, référence du jeu et du dico
* @return char : une lettre ou "?" pour appeller bluff
*/
char robot_choix(Jeu& jeu, Dico& dico) {
	if (jeu.nbLettre == 0) { //si c'est le robot qui doit mettre la première lettre
		return 'A' + rand() % ('Z' - 'A' + 1); //renvoie une lettre aléatoire
	}
	char result = verif_robot(jeu, dico); //appel fonction verif_robot(jeu, dico) pour avoir le choix du robot
	if (isalpha(result)) { //si le caractère est une lettre 
		return result; // renvoie la lettre
	}
	else { //sinon si le caractère renvoyé n'est pas une lettre
		return '?'; //renvoie "?" pour que le robot bluff
	}


}

/**
* @brief Renvoie un caractère selon le nombre de mots que l'on peut former avec le mot du jeu
* @param[in-out] Jeu& jeu, Dico& dico, référence du jeu et du dico
* @return char, un caractère
*/
char verif_robot(Jeu& jeu, Dico& dico) {
	//Un tableau de 26 entiers, un pour chaque lettre de l'alphabet 
	int lettreCount[ALPHABET] = { 0 };
	int max_lettre = lettreCount[0];
	int taille = strlen(jeu.mot); //pour avoir la taille du préfixe du mot dans le jeu
	for (unsigned int i = 0; i < dico.nbMot; ++i) {
		if (strncmp(dico.dico[i].mot, jeu.mot, taille) == 0) { //permet de comparer deux chaînes de caractères et de savoir si la première est égale à la seconde selon une taille précise 
			char c = dico.dico[i].mot[taille]; //lettre juste après la taille du préfixe
			lettreCount[c - 'A']++; //plus un à la position du tableau de la lettre trouvée
		}
	}
	//On cherche la lettre avec le plus d'occurrence
	for (int i = 0; i < ALPHABET; i++) {
		if (max_lettre < lettreCount[i]) {
			max_lettre = lettreCount[i];
		}
	}
	//le compteur vérifie s'il y a une lettre ou plus dans le tableau
	int cpt = 0;
	for (int i = 0; i < ALPHABET; i++) {
		if (lettreCount[i] > 0)
			cpt++;
	}
	//si le cpt est égal à 0 ou 1, on ne pourra former un mot avec qu'une seule lettre

	if (max_lettre > SEUIL) { // le seuil à laquel le robot "?" ou pas 
		for (int i = 0; i < ALPHABET; i++) {

			if (max_lettre == lettreCount[i]) { //le robot essaie de renvoyer la lettre avec le plus d'occurrence
				char result[ALPHABET] = "";
				strcpy(result, jeu.mot);
				result[jeu.nbLettre] = char('A' + i); //forme le mot du jeu avec la lettre 
				if (verif_dichotomique(dico, dico.nbMot, result) == false || cpt <= 1) //vérifie si le mot formé existe ou pas et que l'on peut former un mot avec plus qu'une seule lettre
					return char('A' + i); //renvoie la lettre avec le plus d'occurrence

				else { //sinon le robot essaie de renvoyer une lettre aléatoire avec une occurrence non nulle

					int j = rand() % ALPHABET + 1; // position de la lettre choisie aléatoirement...
					int cpt1 = 0;
					while (verif_dichotomique(dico, dico.nbMot, result) == true) { //vérifie, tant que le mot formé existe, on utilise une lettre différente 
						if (lettreCount[j] > 0) { //si la lettre a au moins une occurrence
							result[jeu.nbLettre] = char('A' + j); //teste la lettre dans le mot formé
							cpt1++;// compte le nombre de tour de boucle 
						}
						else {
							j = rand() % ALPHABET + 1; // position d'une lettre aléatoire
						}
						if (cpt1 >= SEUIL) { // rand n'est pas complétement aléatoire donc 
							//cela pose un problème quand le programme ne tombe jamais sur une lettre avec au moins une occurrence
							//on arrête selon un seuil le choix semi-aléatoire et on parcours juste le tableau jusqu'à tomber sur une lettre avec au moins une occurrence
							for (unsigned int j = 0; j < ALPHABET; ++j) {
								if (lettreCount[j] > 0) {
									result[jeu.nbLettre] = char('A' + j);
									if (verif_dichotomique(dico, dico.nbMot, result) == false) {//vérifie si le mot formé existe ou pas 
										char resulta = char('A' + j);
										j = 0;
										return resulta;//renvoie la première lettre trouvée avec au moins une occurrence
									}

								}
							}
						}
					}
					char resulta = char('A' + j);
					j = 0;
					return resulta; //renvoie la lettre aléatoirement trouvée
				}
			}
		}
	}
	else {
		return char(max_lettre); // renvoie un caractère, préférablement qui n'est pas une lettre 
	}
}



/**
* @brief Renvoie le choix du robot lorsqu'il se fait bluff
* @param[in-out] Jeu& jeu, Dico& dico, référence du jeu et du dico
* @param[in] unsigned int y, position du joueur précédent
* @return char*, le mot trouvé dans le dico ou "!" si le robot ne trouve rien
*/
char* robot_choix_bluff(Jeu& jeu, Dico& dico, unsigned int y) {
	int taille = strlen(jeu.mot);
	for (unsigned int i = 0; i < dico.nbMot; ++i) {
		//permet de comparer deux chaînes de caractères et de savoir si la première est égale à la seconde selon une taille précise 
		//si un mot existe avec ce préfixe (= le mot du jeu) et que la taille du mot est supérieure à deux lettres
		if (strncmp(dico.dico[i].mot, jeu.mot, taille) == 0 && strlen(dico.dico[i].mot) > TAILLE_MINIMALE) {
			return dico.dico[i].mot; //renvoie le mot trouvé dans le dico
		}
	}
	char str[] = "!";
	return str; //renvoie "!" pour abandonner si le robot ne trouve rien 
}