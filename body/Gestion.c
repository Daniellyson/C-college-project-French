#include "Constantes.h"
#include "Header.h"


Erreur ajouterInscription(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;
	Doublette * pNouvDoublette;
	ShiftInscription * pShift;
	Membre membreLu;
	int matricule1;
	int moy1;
	int matricule2;
	int moy2;
	int categorieLu;
	bool dejaInscrit;

	afficherMessage(pLexique, (DEBUT_AFFICHAGE + SHIFT_PLACE_LIBRE));
	codeErreur = afficherShiftsIncomplets(pDebShifts);

	if (codeErreur != PLUS_DE_PLACE_SHIFTS) {
		codeErreur = nouvelleDoublette(&pNouvDoublette);

		if (codeErreur != ERREUR_MEMOIRE) {
			codeErreur = shiftObtenu(pLexique, pDebShifts, &pShift);

			if (codeErreur == PAS_D_ERREUR) {
				membreLu = matriculeObtenu(pLexique, membres, nbMembres);
				moy1 = membreLu.moyenne;
				matricule1 = membreLu.matricule;

				dejaInscrit = membreDejaInscrit(pDebShifts, membreLu);
				if (dejaInscrit) {
					return MEMBRE_DEJA_INSCRIT;
				}

				if (!dejaInscrit) {
					membreLu = matriculeObtenu(pLexique, membres, nbMembres);
					moy2 = membreLu.moyenne;
					matricule2 = membreLu.matricule;

					if (matricule1 == matricule2) {
						return DOUBLETTE_EGAUX;
					}
					dejaInscrit = membreDejaInscrit(pDebShifts, membreLu);

					if (dejaInscrit) {
						return MEMBRE_DEJA_INSCRIT;
					}
					if (!dejaInscrit) {
						categorieLu = categorie(moy1, moy2);

						ajouterDoubletteShift(pShift, matricule1, matricule2, categorieLu, pNouvDoublette);

						majNbDoublette(pShift, PLUS);
					}
				}
			}
		}
	}
	return codeErreur;
}

void majNbDoublette(ShiftInscription * pShift, int quantite) {
	
	pShift->nombreDoublettes += quantite;
}

void ajouterDoubletteShift(ShiftInscription * pShift, int matricule1, int matricule2, int categorieLu, Doublette * pNouvDoublette) {
	
	Doublette * pDeb = pShift->pDebInscription;
	Doublette * pSauve = NULL;
	
	while (pDeb != NULL && pDeb->categorie < categorieLu) {
		pSauve = pDeb;
		pDeb = pDeb->pSuivInscription;
	}

	pNouvDoublette->matriculePremierJouer = matricule1;
	pNouvDoublette->matriculeDeuxiemeJouer = matricule2;
	pNouvDoublette->categorie = categorieLu;
	pNouvDoublette->pSuivInscription = NULL;

	if (pDeb == pShift->pDebInscription) {
		pShift->pDebInscription = pNouvDoublette;
	}
	else {
		pSauve->pSuivInscription = pNouvDoublette;
	}
	pNouvDoublette->pSuivInscription = pDeb;
}

int categorie(int moy1, int moy2) {
	
	int  moyenne;
	moyenne = (moy1 + moy2) / 2;

	if (moyenne >= 200) {
		return CAT_1;
	}
	else {
		if (moyenne >= 190) {
			return CAT_2;
		}
		else {
			if (moyenne >= 180) {
				return CAT_3;
			}
			else {
				if (moyenne >= 170) {
					return CAT_4;
				}
				else {
					if (moyenne >= 160) {
						return CAT_5;
					}
					else {
						return CAT_6;
					}
				}
			}
		}
	}
}

bool membreDejaInscrit(ShiftInscription * pDebShifts, Membre membre) {
	bool dejaExiste = false;
	ShiftInscription * pShift = pDebShifts;

	while (pShift != NULL) {
		Doublette * pDoublette = pShift->pDebInscription;
		while (pDoublette != NULL) {
			if (membre.matricule == pDoublette->matriculePremierJouer || membre.matricule == pDoublette->matriculeDeuxiemeJouer) {
				dejaExiste = true;
				return dejaExiste;
			}
			pDoublette = pDoublette->pSuivInscription;
		}
		pShift = pShift->pSuivShift;
	}
	return dejaExiste;
}

Membre matriculeObtenu(Message * pLexique, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;
	bool membreExiste;
	Membre membre;
	int indMembre = 0;

	afficherMessage(pLexique, (DEBUT_AFFICHAGE + LISTER_DOUBLETTES));
	listerMembre(membres, nbMembres);

	do {
		afficherMessage(pLexique, (CHOIX_OBTENTION + INFO_MATRICULE));
		scanf_s("%d", &membre.matricule);
		
		VIDEBUFFER;

		membreExiste = membreTrouve(membres, nbMembres, membre, &indMembre);

		if (!membreExiste) {
			afficherMessage(pLexique, (PREMIER_ERREUR + MEMBRE_INCONNU));
		}

	} while (!membreExiste);

	return *(membres + indMembre);
}

bool membreTrouve(Membre * membres, int nbMembres, Membre membre, int * indMembre) {
	bool membreExiste = true;

	while (*indMembre < nbMembres && (*(membres + *indMembre)).matricule < membre.matricule) {
		(*indMembre)++;
	}
	if ((*(membres + *indMembre)).matricule != membre.matricule) {
		membreExiste = false;
		return membreExiste;
	}
	return membreExiste;
}

void listerMembre(Membre * membres, int nbMembres) {
	
	printf("-----------------------------------------------\n");
	for (int i = 0; i < nbMembres; i++) {
		printf("%6d    | %12.12s %11.11s | ", (*(membres + i)).matricule, (*(membres + i)).nom, (*(membres + i)).prenom);
		printf("%d \n", (*(membres + i)).moyenne);
	}
}

Erreur shiftObtenu(Message * pLexique, ShiftInscription * pDebShifts, ShiftInscription * * pShift) {
	Erreur codeErreur = PAS_D_ERREUR;
	bool shiftExiste;
	Shift shift;

	do {
		afficherMessage(pLexique, (CHOIX_OBTENTION + INFO_SHIFT_DATE));
		scanf_s("%d", &shift.dateShift);
		VIDEBUFFER;

		afficherMessage(pLexique, (CHOIX_OBTENTION + INFO_SHIFT_HEURE));
		scanf_s("%d", &shift.heureShift);
		VIDEBUFFER;

		shiftExiste = shiftTrouve(pDebShifts, shift, pShift);

		if (shiftExiste && (NBR_MAX_DOUBLETTES_SHIFT - (*pShift)->nombreDoublettes) == 0) {
			return PLUS_DE_PLACE_SHIFTS;
		}
		/*Si un utilisateur essaie d'inscrire une doublette dans un shift que n'a plus de place, même si la date 
		ne s'affiche plus. Il faut gerer le cas d'erreur pour des utilisateurs malveillants*/
				
		if (!shiftExiste) {
			afficherMessage(pLexique, (PREMIER_ERREUR + SHIFT_INCONNU));
		}
	} while (!shiftExiste);
	return codeErreur;
}

bool shiftTrouve(ShiftInscription * pDebShifts, Shift shift, ShiftInscription * * pShift) {
	
	bool shiftExiste;
	Erreur codeErreur = PAS_D_ERREUR;

	*pShift = pDebShifts;

	while (*pShift != NULL) {
		if ((*pShift)->dateShift == shift.dateShift && (*pShift)->heureShift == shift.heureShift) {
			shiftExiste = true;
			return shiftExiste;
		}
		else {
			shiftExiste = false;
		}
		*pShift = (*pShift)->pSuivShift;
	}
	return shiftExiste;
}

Erreur afficherShiftsIncomplets(ShiftInscription * pDebShifts) {
	Erreur codeErreur = PAS_D_ERREUR;
	printf("-----------------------------------\n");

	ShiftInscription * pShift = pDebShifts;
	while (pShift != NULL) {
		if (NBR_MAX_DOUBLETTES_SHIFT - pShift->nombreDoublettes != 0) {
			printf("%d | %d  | %d \n", pShift->dateShift, pShift->heureShift, (NBR_MAX_DOUBLETTES_SHIFT - pShift->nombreDoublettes));
		}
		pShift = pShift->pSuivShift;
	}
	return codeErreur;
}

Erreur nouvelleDoublette(Doublette * * pNouvDoublette) {
	Erreur codeErreur = PAS_D_ERREUR;

	*pNouvDoublette = (Doublette *)malloc(sizeof(Doublette));
	if (pNouvDoublette == NULL) {
		return ERREUR_MEMOIRE;
	}
	return codeErreur;
}


Erreur imprimerInscriptions(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;

	ShiftInscription * pShift = pDebShifts;
	Doublette * pDoublette;

	while (pShift != NULL) {
		afficherMessage(pLexique, (DEBUT_AFFICHAGE + DATE_HEURE));
		printf(" %d : %d\n", pShift->dateShift, pShift->heureShift);
		
		pDoublette = pShift->pDebInscription;
		if (pDoublette == NULL) {
			afficherMessage(pLexique, (DEBUT_AFFICHAGE + PAS_DINSCRIPTION));
		}
		else {
			while (pDoublette != NULL) {

				int i = 0;
				while (i < NBR_MAX_MEMBRES && pDoublette->matriculePremierJouer != (*(membres + i)).matricule) {
					i++;
				}

				afficherMessage(pLexique, (DEBUT_AFFICHAGE + MAT_NOM_PRENOM));
				printf("\t%9d | %12.12s %11.11s |\n", pDoublette->matriculePremierJouer, (*(membres + i)).nom, (*(membres + i)).prenom);

				int j = 0;
				while (j < NBR_MAX_MEMBRES && pDoublette->matriculeDeuxiemeJouer != (*(membres + j)).matricule) {
					j++;
				}
				printf("\t%9d | %12.12s %11.11s |\n", pDoublette->matriculeDeuxiemeJouer, (*(membres + j)).nom, (*(membres + j)).prenom);

				afficherMessage(pLexique, (DEBUT_AFFICHAGE + CATEGORIE));
				printf("%18d|\n\n", pDoublette->categorie);
				printf("--------------------------------------------------\n");

				pDoublette = pDoublette->pSuivInscription;
			}
		}
		pShift = pShift->pSuivShift;
		printf("\n==================================================\n");
	}
	printf("\n");
	return codeErreur;
}

Erreur supprimerInscription(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;
	Membre membreLu;
	int matricule1;
	int matricule2;
	bool estDoublette;
	ShiftInscription * pShift;
	Doublette * pDoublette;
	Doublette * pDoubletteSauv;


	membreLu = matriculeObtenu(pLexique, membres, nbMembres);
	matricule1 = membreLu.matricule;

	membreLu = matriculeObtenu(pLexique, membres, nbMembres);
	matricule2 = membreLu.matricule;

	if (matricule1 == matricule2) {
		return DOUBLETTE_EGAUX;
	}
	else {
		estDoublette = doubletteTrouvee(pDebShifts, matricule1, matricule2, &pShift, &pDoublette, &pDoubletteSauv);
	}

	if (estDoublette) {
		supprimerDoublette(pShift, pDoublette, pDoubletteSauv);

		majNbDoublette(pShift, MOINS);
	}
	else {
		return DOUBLETTE_PAS_VALIDE;
	}

	return codeErreur;
}

void supprimerDoublette(ShiftInscription * pShift, Doublette * pDoublette, Doublette * pDoubletteSauv) {

	if (pDoublette == pShift->pDebInscription) {
		pShift->pDebInscription = pDoublette->pSuivInscription;
	}
	else {
		pDoubletteSauv->pSuivInscription = pDoublette->pSuivInscription;
	}

	free(pDoublette);
}

bool doubletteTrouvee(ShiftInscription * pDebShifts, int matricule1, int matricule2, ShiftInscription * * pShift,
	Doublette * * pDoublette, Doublette * * pDoubletteSauv) {

	bool estDoublette = true;

	*pShift = pDebShifts;

	while (*pShift != NULL) {
		*pDoublette = (*pShift)->pDebInscription;
		while (*pDoublette != NULL && (*pDoublette)->matriculePremierJouer != matricule1 &&
			(*pDoublette)->matriculeDeuxiemeJouer != matricule1) {

			*pDoubletteSauv = *pDoublette;
			*pDoublette = (*pDoublette)->pSuivInscription;
		}
		if ((*pDoublette) != NULL) {
			if (((*pDoublette)->matriculePremierJouer == matricule1 || (*pDoublette)->matriculePremierJouer == matricule2) &&
				((*pDoublette)->matriculeDeuxiemeJouer == matricule1 || (*pDoublette)->matriculeDeuxiemeJouer == matricule2)) {

				return estDoublette;
			}
		}
		*pShift = (*pShift)->pSuivShift;
	}	
	return estDoublette = false;
}

Erreur deplacerInscription(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;
	Membre membreLu;
	int matricule1;
	int moy1;
	int matricule2;
	int moy2;
	int categorieLu;
	bool estDoublette;
	ShiftInscription * pShift;
	ShiftInscription * pShiftCopie;
	Doublette * pDoublette;
	Doublette * pDoubletteSauv;
	Doublette * pNouvDoublette;


	membreLu = matriculeObtenu(pLexique, membres, nbMembres);
	matricule1 = membreLu.matricule;
	moy1 = membreLu.moyenne;

	membreLu = matriculeObtenu(pLexique, membres, nbMembres);
	matricule2 = membreLu.matricule;
	moy2 = membreLu.moyenne;

	if (matricule1 == matricule2) {
		return DOUBLETTE_EGAUX;
	}
	else {
		estDoublette = doubletteTrouvee(pDebShifts, matricule1, matricule2, &pShift, &pDoublette, &pDoubletteSauv);
		pShiftCopie = pShift;
		categorieLu = categorie(moy1, moy2);
	}

	if (estDoublette) {
		supprimerDoublette(pShift, pDoublette, pDoubletteSauv);

		majNbDoublette(pShift, MOINS);
	}
	else {
		return DOUBLETTE_PAS_VALIDE;
	}

	afficherMessage(pLexique, (DEBUT_AFFICHAGE + SHIFT_PLACE_LIBRE));
	codeErreur = afficherShiftsIncomplets(pDebShifts);

	if (codeErreur == PAS_D_ERREUR) {
		codeErreur = nouvelleDoublette(&pNouvDoublette);

		if (codeErreur != ERREUR_MEMOIRE) {
			codeErreur = shiftObtenu(pLexique, pDebShifts, &pShift);

			if (codeErreur != PLUS_DE_PLACE_SHIFTS) {

				categorieLu = categorie(moy1, moy2);

				ajouterDoubletteShift(pShift, matricule1, matricule2, categorieLu, pNouvDoublette);

				majNbDoublette(pShift, PLUS);
			}
			else {
				/*si l'utilisateur essaie de remplacer la doublette dans un shift qu'il n'y a plus de place, 
				il faut remettre la meme doublette dans le shift qu'on vient de supprimer*/
				ajouterDoubletteShift(pShiftCopie, matricule1, matricule2, categorieLu, pNouvDoublette);
				majNbDoublette(pShiftCopie, PLUS);
			}
		}
	}
	return codeErreur;
}

Erreur imprimerDoubletteCategorie(Message * pLexique, ShiftInscription * pDebShifts, Membre * membres, int nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;

	ShiftInscription * pShift;
	Doublette * pDoublette;
	bool existeInscritDansCategorie;
	
	for (int cpt = 0; cpt < NBR_MAX_CATEGORIE; cpt++) {
		afficherMessage(pLexique, (DEBUT_AFFICHAGE + CATEGORIE));
		printf("%18d|\n", cpt + 1);

		existeInscritDansCategorie = false;

		pShift = pDebShifts;
		while (pShift != NULL) {
			pDoublette = pShift->pDebInscription;
			while (pDoublette != NULL) {
				if (pDoublette->categorie == (cpt + 1)) {
					int i = 0;
					while (i < NBR_MAX_MEMBRES && pDoublette->matriculePremierJouer != (*(membres + i)).matricule) {
						i++;
					}

					afficherMessage(pLexique, (DEBUT_AFFICHAGE + NOM_PRENOM));

					printf(" %12.12s %11.11s \n", (*(membres + i)).nom, (*(membres + i)).prenom);

					int j = 0;
					while (j < NBR_MAX_MEMBRES && pDoublette->matriculeDeuxiemeJouer != (*(membres + j)).matricule) {
						j++;
					}
					printf(" %12.12s %11.11s \n", (*(membres + j)).nom, (*(membres + j)).prenom);

					existeInscritDansCategorie = true;
				}
				pDoublette = pDoublette->pSuivInscription;
			}
			pShift = pShift->pSuivShift;
		}
		if (!existeInscritDansCategorie) {
			afficherMessage(pLexique, (DEBUT_AFFICHAGE + PAS_INSCRIPTION_POUR_CETTE_CATEGORIE));
		}
		printf("\n======================================\n");
	}
	printf("\n");
	return codeErreur;
}