#include "Constantes.h"
#include "Header.h"
 
Erreur chargementInscriptions(ShiftInscription * * pDebShifts) {
	Erreur codeErreur = PAS_D_ERREUR;
	FILE * fiInscription;
	ShiftInscription shift;
	Doublette inscriptionLu;
	ShiftInscription * pShiftSauv = NULL;
	ShiftInscription * pShiftNouv;
	Doublette * pSauveDoublette = NULL;
	Doublette * pNouvDoublette;
	int date;
	int heure;
	
	fopen_s(&fiInscription, FICHIER_DAT_INSCRIPTION, "rb");
	if (fiInscription == NULL) {
		return ERREUR_OUVERTURE_FICHIER_INSCRIPTION;
	}

	fread_s(&shift, sizeof(shift), sizeof(shift), 1, fiInscription);

	date = shift.dateShift;
	heure = shift.heureShift;
	
	while (!feof(fiInscription) && codeErreur == PAS_D_ERREUR) {
		codeErreur = nouveauShift(&pShiftNouv);

		if (codeErreur == PAS_D_ERREUR) {
			pShiftNouv->dateShift = date;
			pShiftNouv->heureShift = heure;
			pShiftNouv->nombreDoublettes = shift.nombreDoublettes;
			pShiftNouv->pDebInscription = NULL;
			pShiftNouv->pSuivShift = NULL;

			if (*pDebShifts == NULL) {
				*pDebShifts = pShiftNouv;
			}
			else {
				pShiftSauv->pSuivShift = pShiftNouv;
			}
			pShiftSauv = pShiftNouv;
		
			for (int i = 0; i < shift.nombreDoublettes; i++) {

				fread_s(&inscriptionLu, sizeof(inscriptionLu), sizeof(inscriptionLu), 1, fiInscription);

				pNouvDoublette = (Doublette *)malloc(sizeof(Doublette));
				if (pNouvDoublette == NULL) {
					return ERREUR_MEMOIRE;
				}
				else {
					pNouvDoublette->matriculePremierJouer = inscriptionLu.matriculePremierJouer;
					pNouvDoublette->matriculeDeuxiemeJouer = inscriptionLu.matriculeDeuxiemeJouer;
					pNouvDoublette->categorie = inscriptionLu.categorie;
					pNouvDoublette->pSuivInscription = NULL;

					if (pShiftSauv->pDebInscription != NULL) {
						pSauveDoublette->pSuivInscription = pNouvDoublette;
					}
					else {
						pShiftSauv->pDebInscription = pNouvDoublette;
					}
					pSauveDoublette = pNouvDoublette;
				}
			}
		}
		fread_s(&shift, sizeof(shift), sizeof(shift), 1, fiInscription);
		date = shift.dateShift;
		heure = shift.heureShift;
	}
	fclose(fiInscription);
	return codeErreur;
}