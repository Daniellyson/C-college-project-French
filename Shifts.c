#include "Constantes.h"
#include "Header.h"

Erreur initialiserShifts(ShiftInscription * * pDebShifts) {
	Erreur codeErreur = PAS_D_ERREUR;

	bool premiereFois;

	codeErreur = detectionFichierShifts(&premiereFois);

	if (codeErreur == PAS_D_ERREUR) {
		if (premiereFois) {
			codeErreur = chargementDatesOrgShifts(pDebShifts);
		}
		else {
			codeErreur = chargementInscriptions(pDebShifts);
		}
	}
	return codeErreur;
}

Erreur detectionFichierShifts(bool * premiereFois) {
	FILE * fiShift;
	FILE * fiInscription;
	Erreur codeErreur = PAS_D_ERREUR;

	fopen_s(&fiInscription, FICHIER_DAT_INSCRIPTION, "rb");

	if (fiInscription == NULL) {
		*premiereFois = true;
		fopen_s(&fiShift, FICHIER_DAT_SHIFTS, "rb");

		if (fiShift == NULL) {
			return ERREUR_OUVERTURE_FICHIER_SHIFT;
		}
		else {
			fclose(fiShift);
		}
	}
	else {
		*premiereFois = false;
		fclose(fiInscription);
	}
	return codeErreur;
}

Erreur chargementDatesOrgShifts(ShiftInscription * * pDebShifts) {
	Erreur codeErreur = PAS_D_ERREUR;
	FILE * fiShift;
	ShiftInscription * pShiftSauv;
	Shift shift;
	ShiftInscription * pShiftNouv;
	int date;
	int heure;

	fopen_s(&fiShift, FICHIER_DAT_SHIFTS, "rb");
	if (fiShift == NULL) {
		return ERREUR_OUVERTURE_FICHIER_SHIFT;
	}
	
	do { 
		shift = shiftLu(fiShift);
		date = shift.dateShift;
		heure = shift.heureShift;

		codeErreur = nouveauShift(&pShiftNouv);
		
		if (codeErreur == PAS_D_ERREUR) {
			ajouterShift(pDebShifts, &pShiftSauv, pShiftNouv, date, heure);
		}
		
	} while (!feof(fiShift) && codeErreur == PAS_D_ERREUR);

	fclose(fiShift);
	return codeErreur;
}

Shift shiftLu(FILE * fiShift) {
	Shift shift;
	fscanf_s(fiShift, "%d", &shift.dateShift);
	fscanf_s(fiShift, "%d", &shift.heureShift);
	return shift;
}

Erreur nouveauShift(ShiftInscription * * pShiftNouv) {
	Erreur codeErreur = PAS_D_ERREUR;
	*pShiftNouv = (ShiftInscription *)malloc(sizeof(ShiftInscription));
	if (pShiftNouv == NULL) {
		return ERREUR_MEMOIRE;
	}	
	return codeErreur;
}

void ajouterShift(ShiftInscription * * pDebShifts, ShiftInscription * * pShiftSauv, ShiftInscription * pShiftNouv, int date, int heure) {

	pShiftNouv->dateShift = date;
	pShiftNouv->heureShift = heure;
	pShiftNouv->nombreDoublettes = 0;
	pShiftNouv->pDebInscription = NULL;
	pShiftNouv->pSuivShift = NULL;

	if (*pDebShifts == NULL) {
		*pDebShifts = pShiftNouv;
	}
	else {
		(*pShiftSauv)->pSuivShift = pShiftNouv;
	}
	*pShiftSauv = pShiftNouv;
}

Erreur sauverShifts(ShiftInscription * pDebShifts) {
	Erreur codeErreur = PAS_D_ERREUR;
	ShiftInscription shift;
	Doublette inscription;
	ShiftInscription * pShift = pDebShifts;
	Doublette * pDoublette;
	FILE * fiInscription;

	fopen_s(&fiInscription, FICHIER_DAT_INSCRIPTION, "wb");

	if (fiInscription == NULL) {
		return ERREUR_OUVERTURE_FICHIER_INSCRIPTION;
	}
	else {
		while (pShift != NULL) {
			
			shift.dateShift = pShift->dateShift;
			shift.heureShift = pShift->heureShift;
			shift.nombreDoublettes = pShift->nombreDoublettes;

			fwrite(&shift, sizeof(shift), 1, fiInscription);

			pDoublette = pShift->pDebInscription;
			while (pDoublette != NULL) {
				inscription.matriculePremierJouer = pDoublette->matriculePremierJouer;
				inscription.matriculeDeuxiemeJouer = pDoublette->matriculeDeuxiemeJouer;
				inscription.categorie = pDoublette->categorie;

				fwrite(&inscription, sizeof(inscription), 1, fiInscription);

				pDoublette = pDoublette->pSuivInscription;
			}
			pShift = pShift->pSuivShift;
		}
		fclose(fiInscription);
	}
	return codeErreur;
}

void libererShifts(ShiftInscription * pDebShifts) {
	ShiftInscription * pDeb;
	ShiftInscription * pDebSauve;
	Doublette * pDoublette;
	Doublette * pDoubletteSauve;

	pDeb = pDebShifts;
	while (pDeb != NULL) {
		pDoublette = pDeb->pDebInscription;
		while (pDoublette != NULL) {
			pDoubletteSauve = pDoublette;
			pDoublette = pDoublette->pSuivInscription;
			free(pDoubletteSauve);
		}
		pDebSauve = pDeb;
		pDeb = pDeb->pSuivShift;
		free(pDebSauve);
	}
}