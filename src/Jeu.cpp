/**
* @file Jeu.cpp
* @brief Projet Sa� S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composants pour le d�roulement du jeu 
* @date Semestre 1 P�riode B
*/



#include "Jeu.h"
#include "Robot.h"

/**
* @brief Initialise la partie et les joueurs
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @param[in] char** argv, pour obtenir le nombre de joueurs
* @return void
*/
void initialiser(Jeu& jeu, char** argv) {
	jeu.mot = NULL; //Initialise le mot pour la partie de jeu
	jeu.mot = new char[jeu.nbLettre + 1]; //Initialise dynamiquement le mot � une taille d'une lettre
	jeu.nbJoueur = strlen(argv[1]); //Initialise le nombre de joueurs
	jeu.joueurs = new Joueur[jeu.nbJoueur]; //Initialise dynamiquement le nombre de joueurs 
	// attribue aux joueurs leur type, leur num�ro, leur nombre de points 
	for (unsigned int i = 0; i < jeu.nbJoueur; ++i) {
		jeu.joueurs[i].type = argv[1][i];
		jeu.joueurs[i].NumJoueur = i + 1;
		jeu.joueurs[i].nbPoint = 0;
	}
}


/**
* @brief Entrez le mot � saisir et affiche si le mot existe ou pas ou si le mot commence par les m�mes lettres
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @param[in] unsigned int& i, position du joueur
* @return int, 0 pour sortir de la fonction
*/
/**
* @brief Entrez le mot � saisir et affiche si le mot existe ou pas ou si le mot commence par les m�mes lettres
* @param[in-out] Jeu& jeu, Dico& dico, r�f�rence du jeu et du dico
* @param[in] unsigned int& i, position du joueur
* @return void
*/
void bluff(Jeu& jeu, unsigned int& i, Dico& dico) {
	unsigned int y = i;
	joueurPrecedent(jeu, y);
	cout << jeu.joueurs[y].NumJoueur << jeu.joueurs[y].type << ",  saisir le mot > ";
	char* tmp = new char[ALPHABET];
	if (jeu.joueurs[y].type == 'H') { //si le type du joueur est humain on fait un cin
		cin >> tmp;
		cin.ignore(INT_MAX, '\n');
	}
	else { //si le type du joueur est robot , on appelle la fonction robot_choix_bluff(jeu, dico,y)
		tmp = robot_choix_bluff(jeu, dico, y); // tmp est �gal au mot trouv�
		//si le robot ne trouve pas de mots dans le dico, il renvoie "!" pour signifier sa d�faite 

	}

	for (unsigned int y = 0; y < strlen(tmp); ++y)
		tmp[y] = toupper(tmp[y]); // met en majuscule 
	if (verif2(tmp, jeu)) { //si le mot commence par les m�mes lettres que le mot du jeu 
		if (verif_dichotomique(dico, dico.nbMot, tmp)) { // et si le mot existe dans le dico, on affiche le message correspondant
			cout << "le mot " << tmp << " existe, " << jeu.joueurs[i].NumJoueur << jeu.joueurs[i].type << " prend un quart de singe" << endl;
			jeu.joueurs[i].nbPoint += 0.25; // ajoute au joueur courant un quart de singe
		}
		else {
			cout << "le mot " << tmp << " n existe pas, " << jeu.joueurs[y].NumJoueur << jeu.joueurs[y].type << " prend un quart de singe" << endl;
			jeu.joueurs[y].nbPoint += 0.25; // ajoute au joueur pr�c�dent un quart de singe
			i = y; // la position du joueur repart du joueur pr�c�dent
		}
	}
	else {//si le mot ne commence pas par les m�mes lettres que le mot du jeu 
		cout << "le mot " << tmp << " ne commence pas par les lettres attendues, " << jeu.joueurs[y].NumJoueur << jeu.joueurs[y].type << " prend un quart de singe" << endl;
		jeu.joueurs[y].nbPoint += 0.25;// ajoute au joueur pr�c�dent un quart de singe
		i = y;// la position du joueur repart du joueur pr�c�dent
	}
	//fin de la manche quand un joueur se prend un quart de singe
	afficher_manche(jeu); //appel la fonction afficher_manche(jeu) pour afficher la situation actuelle de la partie avec le nombre de points des joueurs
}



/**
* @brief Affiche que le mot existe s'il a �t� trouv�
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @param[in] unsigned int& i, position du joueur
* @return void
*/
void trouver(Jeu& jeu, unsigned int i) {
	cout << "le mot " << jeu.mot << " existe, " << jeu.joueurs[i].NumJoueur << jeu.joueurs[i].type << " prend un quart de singe" << endl;
	jeu.joueurs[i].nbPoint += 0.25; // ajoute au joueur courant un quart de singe
	//fin de la manche quand un joueur se prend un quart de singe
	afficher_manche(jeu);//appel la fonction afficher_manche(jeu) pour afficher la situation actuelle de la partie avec le nombre de points des joueurs
}



/**
* @brief Affiche que le joueur abandonne la manche
* @param[in-out] Jeu& jeu, r�f�rence du jeu, Joueur* joueurs, pointeur sur les joueurs
* @param[in] unsigned int i, position du joueur
* @return void
*/
void surrend(Jeu& jeu, Joueur* joueurs, unsigned int i) {
	cout << "le joueur " << joueurs[i].NumJoueur << joueurs[i].type << " abandonne la manche et prend un quart de singe" << endl;
	joueurs[i].nbPoint += 0.25;
	//fin de la manche quand un joueur se prend un quart de singe
	afficher_manche(jeu);//appel la fonction afficher_manche(jeu) pour afficher la situation actuelle de la partie avec le nombre de points des joueurs
}

/**
* @brief Affiche la situation actuelle de la partie avec le mot et le joueur courant
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @param[in] unsigned int i, la position du joueur
* @return void
*/
void afficher(Jeu& jeu, unsigned int i) {
	if (jeu.mot == NULL) //si le mot est vide, affiche en d�but de partie ou r�initialisation du mot
		cout << jeu.joueurs[i].NumJoueur << jeu.joueurs[i].type << ", ( ) > ";
	else //sinon affiche le mot de la manche et le joueur courant
	{
		cout << jeu.joueurs[i].NumJoueur << jeu.joueurs[i].type << ", (";
		for (unsigned int y = 0; y < jeu.nbLettre; ++y) {
			cout << jeu.mot[y];
		}
		cout << ") > ";
	}
}


/**
* @brief Affiche la situation actuelle de la partie avec le nombre de points des joueurs
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @return void
*/
void afficher_manche(Jeu& jeu) {
	const char* virgule = "";
	//affiche les joueurs et leur nombre de points
	for (unsigned int i = 0; i < jeu.nbJoueur; ++i) {
		cout << virgule << jeu.joueurs[i].NumJoueur << jeu.joueurs[i].type << " : " << jeu.joueurs[i].nbPoint;
		virgule = "; ";
	}
	cout << endl;
	reset_mot(jeu); //r�initialise le mot de la manche
}

/**
* @brief R�alise une copie du mot de la manche
* @param[in-out] char*& mot, r�f�rence du mot de la manche
* @param[in] int taille, taille du mot
* @return void
*/
void Copie(char*& mot, int taille) {
	/* Alloue en m�moire dynamique un nouveau tableau
	* � cette taille*/
	char* copie = new char[taille + 1];
	// copie le mot dans le nouveau tableau copie
	for (int i = 0; i < taille; i++)
		copie[i] = mot[i];
	copie[taille] = '\0'; //rajout� pour pouvoir comparer avec les mots du dico
	delete[] mot; //d�salloue l'ancien tableau pour le mot 

	/* Actualise la mise � jour du conteneur en m�moire dynamique
	* Faites pointer le tableau support du conteneur
	* sur le nouveau tableau en m�moire dynamique */
	mot = copie;
}


/**
* @brief V�rifie si le mot rentr� � bien les m�mes lettres que le mot de la manche
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @param[in] char mot[ALPHABET], le mot rentr�
* @return bool , true si le mot commence par les m�mes lettres , false sinon
*/
bool verif2(char mot[ALPHABET], Jeu& jeu) {
	for (unsigned int i = 0; i < jeu.nbLettre; ++i) {
		if (mot[i] != jeu.mot[i]) { //v�rifie si pour chaque position du mot rentr� et du mot de la manche, on a bien les m�mes lettres
			return false; //le mot ne commence pas par les m�mes lettres
		}
	}
	return true; //le mot commence par les m�mes lettres
}


/**
* @brief R�initialise le mot de la manche
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @return void
*/
void reset_mot(Jeu& jeu) {
	delete[] jeu.mot; // d�salloue le tableau du mot de la manche
	//initialise le mot de la manche et le nombre de lettres � 0
	jeu.mot = NULL;
	jeu.nbLettre = 0;
	jeu.mot = new char[jeu.nbLettre + 1]; //Initialise dynamiquement le mot � une taille d'une lettre
}

/**
* @brief Devient le joueur pr�c�dent
* @param[in-out] Jeu& jeu, r�f�rence du jeu, unsigned int& i, position du joueur
* @return void
*/
void joueurPrecedent(Jeu& jeu, unsigned int& i) {
	if (i == 0) //si on est � la position du premier joueur
		i = jeu.nbJoueur - 1; // la position du joueur devient le dernier
	else
		--i; //sinon la position du joueur devient celle du pr�c�dent
}


/**
* @brief V�rifie si un joueur � 4 quart de singe
* @param[in-out] Jeu& jeu, r�f�rence du jeu
* @return bool, true si un joueur � 4 quarts de singe et false sinon
*/
bool eliminer(Jeu& jeu) {
	for (unsigned int i = 0; i < jeu.nbJoueur; ++i) {
		if (jeu.joueurs[i].nbPoint == 1) { //v�rifie le nombre de points de chaque joueur est diff�rent de 4 quarts de singe
			cout << "La partie est finie" << endl;
			return true; //renvoie si un joueur a 4 quarts de singe
		}
	}
	return false; //renvoie si aucun joueur n'a 4 quarts de singe
}
