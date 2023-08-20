/**
* @file Jeu.cpp
* @brief Projet Saé S1.02: Quart de singe
* @author John LI et Nassim BEN DAALI Grp 105
* @version 1.0
* @brief Composants pour le déroulement du jeu 
* @date Semestre 1 Période B
*/



#include "Jeu.h"
#include "Robot.h"

/**
* @brief Initialise la partie et les joueurs
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] char** argv, pour obtenir le nombre de joueurs
* @return void
*/
void initialiser(Jeu& jeu, char** argv) {
	jeu.mot = NULL; //Initialise le mot pour la partie de jeu
	jeu.mot = new char[jeu.nbLettre + 1]; //Initialise dynamiquement le mot à une taille d'une lettre
	jeu.nbJoueur = strlen(argv[1]); //Initialise le nombre de joueurs
	jeu.joueurs = new Joueur[jeu.nbJoueur]; //Initialise dynamiquement le nombre de joueurs 
	// attribue aux joueurs leur type, leur numéro, leur nombre de points 
	for (unsigned int i = 0; i < jeu.nbJoueur; ++i) {
		jeu.joueurs[i].type = argv[1][i];
		jeu.joueurs[i].NumJoueur = i + 1;
		jeu.joueurs[i].nbPoint = 0;
	}
}


/**
* @brief Entrez le mot à saisir et affiche si le mot existe ou pas ou si le mot commence par les mêmes lettres
* @param[in-out] Jeu& jeu, Dico& dico, référence du jeu et du dico
* @param[in] unsigned int& i, position du joueur
* @return int, 0 pour sortir de la fonction
*/
/**
* @brief Entrez le mot à saisir et affiche si le mot existe ou pas ou si le mot commence par les mêmes lettres
* @param[in-out] Jeu& jeu, Dico& dico, référence du jeu et du dico
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
		tmp = robot_choix_bluff(jeu, dico, y); // tmp est égal au mot trouvé
		//si le robot ne trouve pas de mots dans le dico, il renvoie "!" pour signifier sa défaite 

	}

	for (unsigned int y = 0; y < strlen(tmp); ++y)
		tmp[y] = toupper(tmp[y]); // met en majuscule 
	if (verif2(tmp, jeu)) { //si le mot commence par les mêmes lettres que le mot du jeu 
		if (verif_dichotomique(dico, dico.nbMot, tmp)) { // et si le mot existe dans le dico, on affiche le message correspondant
			cout << "le mot " << tmp << " existe, " << jeu.joueurs[i].NumJoueur << jeu.joueurs[i].type << " prend un quart de singe" << endl;
			jeu.joueurs[i].nbPoint += 0.25; // ajoute au joueur courant un quart de singe
		}
		else {
			cout << "le mot " << tmp << " n existe pas, " << jeu.joueurs[y].NumJoueur << jeu.joueurs[y].type << " prend un quart de singe" << endl;
			jeu.joueurs[y].nbPoint += 0.25; // ajoute au joueur précédent un quart de singe
			i = y; // la position du joueur repart du joueur précédent
		}
	}
	else {//si le mot ne commence pas par les mêmes lettres que le mot du jeu 
		cout << "le mot " << tmp << " ne commence pas par les lettres attendues, " << jeu.joueurs[y].NumJoueur << jeu.joueurs[y].type << " prend un quart de singe" << endl;
		jeu.joueurs[y].nbPoint += 0.25;// ajoute au joueur précédent un quart de singe
		i = y;// la position du joueur repart du joueur précédent
	}
	//fin de la manche quand un joueur se prend un quart de singe
	afficher_manche(jeu); //appel la fonction afficher_manche(jeu) pour afficher la situation actuelle de la partie avec le nombre de points des joueurs
}



/**
* @brief Affiche que le mot existe s'il a été trouvé
* @param[in-out] Jeu& jeu, référence du jeu
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
* @param[in-out] Jeu& jeu, référence du jeu, Joueur* joueurs, pointeur sur les joueurs
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
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] unsigned int i, la position du joueur
* @return void
*/
void afficher(Jeu& jeu, unsigned int i) {
	if (jeu.mot == NULL) //si le mot est vide, affiche en début de partie ou réinitialisation du mot
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
* @param[in-out] Jeu& jeu, référence du jeu
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
	reset_mot(jeu); //réinitialise le mot de la manche
}

/**
* @brief Réalise une copie du mot de la manche
* @param[in-out] char*& mot, référence du mot de la manche
* @param[in] int taille, taille du mot
* @return void
*/
void Copie(char*& mot, int taille) {
	/* Alloue en mémoire dynamique un nouveau tableau
	* à cette taille*/
	char* copie = new char[taille + 1];
	// copie le mot dans le nouveau tableau copie
	for (int i = 0; i < taille; i++)
		copie[i] = mot[i];
	copie[taille] = '\0'; //rajouté pour pouvoir comparer avec les mots du dico
	delete[] mot; //désalloue l'ancien tableau pour le mot 

	/* Actualise la mise à jour du conteneur en mémoire dynamique
	* Faites pointer le tableau support du conteneur
	* sur le nouveau tableau en mémoire dynamique */
	mot = copie;
}


/**
* @brief Vérifie si le mot rentré à bien les mêmes lettres que le mot de la manche
* @param[in-out] Jeu& jeu, référence du jeu
* @param[in] char mot[ALPHABET], le mot rentré
* @return bool , true si le mot commence par les mêmes lettres , false sinon
*/
bool verif2(char mot[ALPHABET], Jeu& jeu) {
	for (unsigned int i = 0; i < jeu.nbLettre; ++i) {
		if (mot[i] != jeu.mot[i]) { //vérifie si pour chaque position du mot rentré et du mot de la manche, on a bien les mêmes lettres
			return false; //le mot ne commence pas par les mêmes lettres
		}
	}
	return true; //le mot commence par les mêmes lettres
}


/**
* @brief Réinitialise le mot de la manche
* @param[in-out] Jeu& jeu, référence du jeu
* @return void
*/
void reset_mot(Jeu& jeu) {
	delete[] jeu.mot; // désalloue le tableau du mot de la manche
	//initialise le mot de la manche et le nombre de lettres à 0
	jeu.mot = NULL;
	jeu.nbLettre = 0;
	jeu.mot = new char[jeu.nbLettre + 1]; //Initialise dynamiquement le mot à une taille d'une lettre
}

/**
* @brief Devient le joueur précédent
* @param[in-out] Jeu& jeu, référence du jeu, unsigned int& i, position du joueur
* @return void
*/
void joueurPrecedent(Jeu& jeu, unsigned int& i) {
	if (i == 0) //si on est à la position du premier joueur
		i = jeu.nbJoueur - 1; // la position du joueur devient le dernier
	else
		--i; //sinon la position du joueur devient celle du précédent
}


/**
* @brief Vérifie si un joueur à 4 quart de singe
* @param[in-out] Jeu& jeu, référence du jeu
* @return bool, true si un joueur à 4 quarts de singe et false sinon
*/
bool eliminer(Jeu& jeu) {
	for (unsigned int i = 0; i < jeu.nbJoueur; ++i) {
		if (jeu.joueurs[i].nbPoint == 1) { //vérifie le nombre de points de chaque joueur est différent de 4 quarts de singe
			cout << "La partie est finie" << endl;
			return true; //renvoie si un joueur a 4 quarts de singe
		}
	}
	return false; //renvoie si aucun joueur n'a 4 quarts de singe
}
