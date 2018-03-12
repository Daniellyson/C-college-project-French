#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define PLUS +1
#define MOINS -1
#define NBR_MAX_MEMBRES 33
#define NBR_MAX_DOUBLETTES_SHIFT 3
#define NBR_MAX_CATEGORIE 6
#define NBR_DATES 7
#define LG_NOM_MEMBRE 80
#define LG_PRENOM_MEMBRE 30
#define LG_MESSAGE_LEXIQUE 100
#define NBMAXCHOIXMENU 7
#define PREMIER_CHOIX 1
#define FICHIER_FRANCAIS "Francais.txt"
#define FICHIER_ANGLAIS "English.txt"
#define FICHIER_DAT_FSBB "MembresFSBB.dat"
#define FICHIER_DAT_SHIFTS "DatesOrgShifts.dat"
#define FICHIER_DAT_INSCRIPTION "inscriptions.dat"
#define VIDEBUFFER while(getchar() != '\n')



typedef enum langue Langue;
enum langue { 
	FRANCAIS = 1, 
	ANGLAIS 
};

typedef enum menu Menu;
enum menu {
	AJOUT_INSCRIPTION = 1,
	SUPPRIMER_INSCRIPTION,
	DEPLACER_INSCRIPTION,
	IMPRIMER_SHIFTS,
	IMPRIMER_DOUBLETTES_CATEGORIE,
	QUITTER
};

typedef enum erreur Erreur;
enum erreur {
	PAS_D_ERREUR,
	ERREUR_OUVERTURE_FICHIER_SHIFT,
	ERREUR_OUVERTURE_FICHIER_MEMBRE,
	ERREUR_OUVERTURE_FICHIER_INSCRIPTION,
	ERREUR_MEMOIRE,
	PLUS_DE_PLACE_SHIFTS,
	MAUVAIS_CHOIX,
	SHIFT_INCONNU,
	MEMBRE_INCONNU,
	MEMBRE_DEJA_INSCRIT,
	DOUBLETTE_PAS_VALIDE,
	DOUBLETTE_EGAUX,
	ERREUR_OUVERTURE_FICHIER_LANGUE
};

typedef enum debutDeMessage DebutDeMessage;
enum debutDeMessage {
	MENU_PRINCIPAL = 1001,
	CHOIX_OBTENTION = 2001,
	OBTENTION_CHOIX = 3001,
	DEBUT_AFFICHAGE = 4001,
	PREMIER_ERREUR = 5001
};

typedef enum affichage Affichage;
enum affichage {
	DATE_HEURE,
	DOUBLETTE,
	CATEGORIE,
	MAT_NOM_PRENOM,
	SHIFT_PLACE_LIBRE,
	LISTER_DOUBLETTES,
	NOM_PRENOM,
	PAS_DINSCRIPTION,
	PAS_INSCRIPTION_POUR_CETTE_CATEGORIE
};

typedef enum infoObtention InfoObtention;
enum infoObtention {
	INFO_SHIFT_DATE,
	INFO_SHIFT_HEURE,
	INFO_MATRICULE,
	INFO_SHIFT_NB_DOUBLETTES
};

typedef enum categorie Categorie;
enum categorie {
	CAT_1 = 1,
	CAT_2,
	CAT_3,
	CAT_4,
	CAT_5,
	CAT_6
};


typedef struct message Message;
struct message {
	int numero;
	char texte[LG_MESSAGE_LEXIQUE];
	Message * pSuiv;
};

typedef struct doublette Doublette;
struct doublette {
	int matriculePremierJouer;
	int matriculeDeuxiemeJouer;
	int categorie;
	Doublette * pSuivInscription;
};

typedef struct shiftInscription ShiftInscription;
struct shiftInscription {
	int dateShift;
	int heureShift;
	int nombreDoublettes;
	Doublette * pDebInscription;
	ShiftInscription * pSuivShift;
};

typedef struct membre Membre;
struct membre {
	int matricule;
	char nom[LG_NOM_MEMBRE];
	char prenom[LG_PRENOM_MEMBRE];
	int moyenne;
};

typedef struct shift Shift;
struct shift {
	int dateShift;
	int heureShift;
};