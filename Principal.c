#include "Constantes.h"
#include "Header.h"


void main(void) {
	Erreur codeErreur = PAS_D_ERREUR;
	Langue langue;
	Message * pLexique = NULL;
	ShiftInscription * pDebShifts = NULL;
	Membre membres[NBR_MAX_MEMBRES];
	int nbMembres = 0;

	langue = langueLue();
	codeErreur = chargerLexique(langue, &pLexique);

	if (codeErreur != PAS_D_ERREUR) {
		imprimerMessageErreur(codeErreur, langue);
	}
	else {
		codeErreur = initialiserShifts(&pDebShifts);
		if (codeErreur != PAS_D_ERREUR) {
			afficherMessage(pLexique, (PREMIER_ERREUR + codeErreur));
			printf("\n");
			system("pause");
			/*pour ne pas changer la structure du DA principal j'ai mis system pause 2 fois pour les cas des fichiers manquants
			je n'ai pas mis system pause à la fin car quand on clique quiter(6), il ne faut pas cliquer encore une fois*/
		}
		else {
			codeErreur = chargementMembres(membres, &nbMembres);

			if (codeErreur != PAS_D_ERREUR) {
				afficherMessage(pLexique, (PREMIER_ERREUR + codeErreur));
				printf("\n");
				system("pause");
			}
			else {
				dialogues(pLexique, pDebShifts, membres, nbMembres);
			}
		}
	}
	if (pLexique != NULL) {
		libererLexique(pLexique);
	}
}