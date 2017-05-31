#include "Constantes.h"
#include "Header.h"


void dialogues(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;

	Menu choix;

	choix = choixObtenu(pLexique, MENU_PRINCIPAL);

	while (choix != QUITTER) {

		switch (choix) {
		case AJOUT_INSCRIPTION :
			codeErreur = ajouterInscription(pLexique, pDebShifts, membres, nbMembres);
			break;

		case SUPPRIMER_INSCRIPTION :
			codeErreur = supprimerInscription(pLexique, pDebShifts, membres, nbMembres);
			break;

		case DEPLACER_INSCRIPTION:
			codeErreur = deplacerInscription(pLexique, pDebShifts, membres, nbMembres);
			break;

		case IMPRIMER_SHIFTS:
			codeErreur = imprimerInscriptions(pLexique, pDebShifts, membres, nbMembres);
			break;

		case IMPRIMER_DOUBLETTES_CATEGORIE:
			codeErreur = imprimerDoubletteCategorie(pLexique, pDebShifts, membres, nbMembres);
			break;
		}

		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, (PREMIER_ERREUR + codeErreur));
			printf("\n\n");
		}
		if (codeErreur != ERREUR_MEMOIRE && codeErreur != ERREUR_OUVERTURE_FICHIER_SHIFT && 
			codeErreur != ERREUR_OUVERTURE_FICHIER_MEMBRE && codeErreur != ERREUR_OUVERTURE_FICHIER_INSCRIPTION) {
			choix = choixObtenu(pLexique, MENU_PRINCIPAL);
		}
	}
	codeErreur = sauverShifts(pDebShifts);
	libererShifts(pDebShifts);
}

Menu choixObtenu(Message * pLexique, DebutDeMessage debMenu) {
	Menu choix;
	int maxChoix;
	bool choixValide;

	do {
		maxChoix = afficherMenu(pLexique, debMenu);

		afficherMessage(pLexique, OBTENTION_CHOIX);
		scanf_s("%d", &choix);
		VIDEBUFFER;

		choixValide = (choix >= PREMIER_CHOIX && choix <= maxChoix);

		if (!choixValide) {
			afficherMessage(pLexique, (PREMIER_ERREUR + MAUVAIS_CHOIX));
			printf("\n");
		}
	} while (!choixValide);
	return choix;
}

int afficherMenu(Message * pLexique, DebutDeMessage debMenu) {
	Message * pDebMenu;
	Message * pMessage;
	int maxChoix;
	int numChoix;

	messageTrouve(pLexique, debMenu, &pDebMenu);
	printf("%s", pDebMenu->texte);
	printf("\t\t**************\n");

	maxChoix = nbChoixMenu(&pDebMenu->pSuiv, debMenu);

	numChoix = 1;
	pMessage = pDebMenu->pSuiv;
	
	while (pMessage != NULL && numChoix <= maxChoix) {
		printf(" %d . %s", numChoix, pMessage->texte);
		numChoix++;
		pMessage = pMessage->pSuiv;
	}
	return maxChoix;
}