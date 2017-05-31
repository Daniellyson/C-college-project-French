#include "Constantes.h"
#include "Header.h"


Langue langueLue(void) {

	Langue choix;
	
	do {
		system("cls");
		printf("\n\t   BIENVENUE / WELCOME\n");
		printf(" _____________________________________________\n");
		printf("| Choisissez la langue / Choose your language |\n");
		printf("|                                             |\n");
		printf("|\t\t1 pour FRANCAIS               |\n");
		printf("|\t\t2 for ENGLISH                 |\n");
		printf("|_____________________________________________|\n");
		printf("\n Choix / Choice : ");
		scanf_s("%d", &choix);
		VIDEBUFFER;

	} while (choix < FRANCAIS || choix > ANGLAIS);
	printf("\n");
	return choix;
}

Erreur chargerLexique(Langue langue, Message * * pLexique) {
	FILE * fiLexique;
	Message message;
	Message * pMessage;
	Message * pLexiquePrec = NULL;
	Erreur codeErreur;

	fiLexique = nomFichierLangage(langue);

	if (fiLexique == NULL) {
		return ERREUR_OUVERTURE_FICHIER_LANGUE;
	}
	else {
		codeErreur = PAS_D_ERREUR;

		do {
			message = messageLu(fiLexique);

			pMessage = (Message *)malloc(sizeof(Message));

			if (pMessage == NULL) {
				return ERREUR_MEMOIRE;
			}
			else {
				pMessage->numero = message.numero;
				strcpy_s(pMessage->texte, LG_MESSAGE_LEXIQUE, message.texte);
				pMessage->pSuiv = NULL;
				
				if (*pLexique == NULL) {
					*pLexique = pMessage;
				}
				else {
					pLexiquePrec->pSuiv = pMessage;
				}
				pLexiquePrec = pMessage;
			}
		} while (!feof(fiLexique) && codeErreur == PAS_D_ERREUR);
	}
	fclose(fiLexique);
	return codeErreur;
}

FILE * nomFichierLangage(Langue langue) {
	FILE * pFicher;
	if (langue == FRANCAIS) {
		fopen_s(&pFicher, FICHIER_FRANCAIS, "r");
	}
	else {
		fopen_s(&pFicher, FICHIER_ANGLAIS, "r");
	}
	return pFicher;
}

Message messageLu(FILE * fiLexique) {
	Message message;
	fscanf_s(fiLexique, "%d", &message.numero);
	fgets(message.texte, LG_MESSAGE_LEXIQUE, fiLexique);
	return message;
}

void messageTrouve(Message * pLexique, DebutDeMessage numMessage, Message * * pDebMenu) {

	Message * pMessage = pLexique;
	while (pMessage != NULL && pMessage->numero < numMessage) {
		pMessage = pMessage->pSuiv;
	}
	*pDebMenu = pMessage;
}

int nbChoixMenu(Message * * pDebMenu, DebutDeMessage debMenu) {
	int maxChoix = 0;
	Message * pMenu = *pDebMenu;
	while (pMenu != NULL && pMenu->numero < debMenu + NBMAXCHOIXMENU) {
		maxChoix++;
		pMenu = pMenu->pSuiv;
	}
	return maxChoix;
}

void afficherMessage(Message * pLexique, DebutDeMessage numMessage) {
	Message * pMessage;
	messageTrouve(pLexique, numMessage, &pMessage);
	printf("\n%s", pMessage->texte);
}

void libererLexique(Message * pLexique) {
	Message * ptr = pLexique;
	Message * ptrSauve;

	while (ptr != NULL) {
		ptrSauve = ptr;
		ptr = ptr->pSuiv;
		free(ptrSauve);
	}
}

void imprimerMessageErreur(Erreur codeErreur, Langue langue) {

	switch (langue) {
	case FRANCAIS:
		if (codeErreur == ERREUR_OUVERTURE_FICHIER_LANGUE) {
			printf("Erreur d'ouverture du fichier langue !");
		}
		else {
			printf("Erreur, plus de place memoire !");
		}
		break;
	case ANGLAIS:
		if (codeErreur == ERREUR_OUVERTURE_FICHIER_LANGUE) {
			printf("Error while opening the language file !");
		}
		else {
			printf("Error, no more memory !");
		}
		break;
	}
	printf("\n\n");
	system("pause");
}