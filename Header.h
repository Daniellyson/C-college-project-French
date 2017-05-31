#pragma once
#include "Constantes.h"


//Lexique.c
Langue langueLue(void);
Erreur chargerLexique(Langue langue, Message * * pLexique);
FILE * nomFichierLangage(Langue langue);
Message messageLu(FILE * fiLexique);
void messageTrouve(Message * pLexique, DebutDeMessage numMessage, Message * * pDebMenu);
int nbChoixMenu(Message * * pDebMenu, DebutDeMessage debMenu);
void afficherMessage(Message * pLexique, DebutDeMessage numMessage);
void libererLexique(Message * pLexique);
void imprimerMessageErreur(Erreur codeErreur, Langue langue);


//Fichier Membre.c
Erreur chargementMembres(Membre * membres, int * nbMembres);
Membre membreLu(FILE * fiMembre);
void gestionChaineMembre(Membre * membre);


//Fichier Inscription.c
Erreur chargementInscriptions(ShiftInscription * * pDebShifts);


//Fichier Shifts.c
Erreur initialiserShifts(ShiftInscription * * pDebShifts);
Erreur detectionFichierShifts(bool * premiereFois);
Erreur chargementDatesOrgShifts(ShiftInscription * * pDebShifts);
Shift shiftLu(FILE * fiShift);
Erreur nouveauShift(ShiftInscription * * pShiftNouv);
void ajouterShift(ShiftInscription * * pDebShifts, ShiftInscription * * pShiftSauv, ShiftInscription * pShiftNouv, int date, int heure);
Erreur sauverShifts(ShiftInscription * pDebShifts);
void libererShifts(ShiftInscription * pDebShifts);


//Interface.c
void dialogues(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres);
Menu choixObtenu(Message * pLexique, DebutDeMessage debMenu);
int afficherMenu(Message * pLexique, DebutDeMessage debMenu);


//Gestion.c
Erreur ajouterInscription(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres);
void majNbDoublette(ShiftInscription * pShift, int quantite);
void ajouterDoubletteShift(ShiftInscription * pShift, int matricule1, int matricule2, int categorieLu, Doublette * pNouvDoublette);
int categorie(int moy1, int moy2);
bool membreDejaInscrit(ShiftInscription * pDebShifts, Membre membre);
Membre matriculeObtenu(Message * pLexique, Membre * membres, int nbMembres);
bool membreTrouve(Membre * membres, int nbMembres, Membre membre, int * indMembre);
void listerMembre(Membre * membres, int nbMembres);
Erreur shiftObtenu(Message * pLexique, ShiftInscription * pDebShifts, ShiftInscription * * pShift);
bool shiftTrouve(ShiftInscription * pDebShifts, Shift shift, ShiftInscription * * pShift);
Erreur afficherShiftsIncomplets(ShiftInscription * pDebShifts);
Erreur nouvelleDoublette(Doublette * * pNouvDoublette);
Erreur imprimerInscriptions(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres);
Erreur supprimerInscription(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres);
void supprimerDoublette(ShiftInscription * pShift, Doublette * pDoublette, Doublette * pDoubletteSauv);
bool doubletteTrouvee(ShiftInscription * pDebShifts, int matricule1, int matricule2, ShiftInscription * * pShift, Doublette * * pDoublette, Doublette * * pDoubletteSauv);

Erreur deplacerInscription(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres);
Erreur imprimerDoubletteCategorie(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres);