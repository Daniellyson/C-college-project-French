#include "Constantes.h"
#include "Header.h"

Erreur chargementMembres(Membre * membres, int * nbMembres) {
	Erreur codeErreur = PAS_D_ERREUR;
	Membre membre;
	
	FILE * fiMembre;

	fopen_s(&fiMembre, FICHIER_DAT_FSBB, "r");
	if (fiMembre == NULL) {
		return ERREUR_OUVERTURE_FICHIER_MEMBRE;
	}
	do {
		membre = membreLu(fiMembre);
		
		gestionChaineMembre(&membre);
		
		*(membres + *nbMembres) = membre;
		(*nbMembres)++;
						
	} while (!feof(fiMembre));
	fclose(fiMembre);
	return codeErreur;
}

Membre membreLu(FILE * fiMembre) {
	Membre membreLu;
	fscanf_s(fiMembre, "%d", &membreLu.matricule);
	fgets(membreLu.nom, LG_NOM_MEMBRE, fiMembre);
	fgets(membreLu.prenom, LG_PRENOM_MEMBRE, fiMembre);
	fscanf_s(fiMembre, "%d", &membreLu.moyenne);
	return membreLu;
}

void gestionChaineMembre(Membre * membre) {
	
	int position = 0;
	while ((*membre).nom[position] != '\n') {
		position++;
	}

	int i = position;
	while ((*membre).nom[i] != '\0') {
		(*membre).nom[i] = (*membre).nom[i + 1];
		i++;
	}

	position = 0;
	while ((*membre).prenom[position] != '\n') {
		position++;
	}

	i = position;
	while ((*membre).prenom[i] != '\0') {
		(*membre).prenom[i] = (*membre).prenom[i + 1];
		i++;
	}
}