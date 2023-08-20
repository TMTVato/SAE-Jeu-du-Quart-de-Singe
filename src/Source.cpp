/**
* @file Source.cpp
* @brief Projet Sa� S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @date Semestre 1 P�riode B
*/

#include "Jeu.h"
#include "Robot.h"


/**
* @brief Lit � partir d'une entr�e standard puis fait l'appel des fonctions entr�es. Doit produire des r�sultats en sortie
* prend comme param�tres argc et argv
*/
int main(int argc, char** argv) {
	char b; // le caract�re stock�
	Jeu jeu;
	Dico dico;
	init_dico(dico);
	initialiser(jeu, argv);
	srand(time(NULL)); //initialise un g�n�rateur de nombres al�atoires
	do {
		for (unsigned int i = 0; i < jeu.nbJoueur; ++i) {
			if (eliminer(jeu) == true) { //si un joueur a �t� �limin� pour avoir obtenu 4 quarts de singe
				delete[] jeu.mot; //quand la partie se finit, on peut d�sallouer le mot de la manche, le dico et les joueurs
				jeu.mot = NULL;
				delete[] dico.dico;
				delete[] jeu.joueurs;
				jeu.joueurs = NULL;
				return 0; //fin de partie
			}
			afficher(jeu, i);
			if (jeu.joueurs[i].type == 'H') { //si le type du joueur est humain on lit � partir d'une entr�e standard 
				cin >> b;
				cin.ignore(INT_MAX, '\n'); // pour prendre en compte que le premier caract�re
			}
			else {//si le type du joueur est robot on appelle la fonction robot_choix(jeu,dico)
				b = robot_choix(jeu, dico);
			}
			b = toupper(b); // met en majuscules le caract�re

			if (b == '!') { // si le caract�re est "!" alors on appelle surrend(jeu, jeu.joueurs, i) pour abandonner la manche
				surrend(jeu, jeu.joueurs, i);
				--i;
			}
			else if (b == '?') { // si le caract�re est "?" alors on appelle bluff(jeu, i, dico) pour bluff le mot 
				bluff(jeu, i, dico);
				--i;
			}
			else { // si le caract�re est une lettre ou autre 
				jeu.mot[jeu.nbLettre] = b; // ajoute le caract�re au mot de la manche
				++jeu.nbLettre;
				Copie(jeu.mot, jeu.nbLettre);
				if (verif_dichotomique(dico, dico.nbMot, jeu.mot)) { //v�rifie que le mot de la manche n'existe pas dans le dico
					trouver(jeu, i); //si true , appel la fonction trouver(jeu, i) car le mot a �t� trouv�
					i = i - 1;
				}
			}
		}
	} while (1); //tant qu'ancun joueur n'a pas obtenu 4 quarts de singe la partie continue 
}


//TEST UNITAIRE
//int main(int argc, char** argv) {
	 // le caract�re stock�
	//Jeu jeu;
	//Dico dico;
	//init_dico(dico);
	//initialiser(jeu, argv);
	//srand(time(NULL)); //initialise un g�n�rateur de nombres al�atoires
	//char c;
	//for (unsigned int i = 0; i < 4; ++i) {
	//	if (i == 0) {
	//		c = 'a';
	//		jeu.mot[jeu.nbLettre] = c;
	//		++jeu.nbLettre;
	//		Copie(jeu.mot, jeu.nbLettre);
	//		verif_dichotomique(dico, dico.nbMot, jeu.mot);
	//		assert(verif_dichotomique(dico, dico.nbMot, jeu.mot) == false);
	//		char a[6] = "table";
	//		verif_dichotomique(dico, dico.nbMot, a);
	//		assert(verif_dichotomique(dico, dico.nbMot, jeu.mot) == true);
	//	}
	//	if (i == 1) {
	//		c = '?';
	//		float point = 0;
	//		bluff(jeu, i, dico);
	//		assert(jeu.joueurs[i].nbPoint - point == 0.25 || jeu.joueurs[i - 1].nbPoint - point == 0.25);
	//	}
	//	if (i == 2) {
	//		c = '!';
	//		float point = 0;
	//		surrend(jeu, jeu.joueurs, i);
	//		assert(jeu.joueurs[i].nbPoint - point == 0.25);
	//		
	//	}
	//	if (i == 3) {
	//		c = robot_choix(jeu, dico);
	//		assert(isalpha(c));
	//	}
	//}
