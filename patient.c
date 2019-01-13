#include "patient.h"

void save_pat (patient_list * liste){ // fonction qui permet la sauvegarde de la liste en l'écrivant dans un fichier .txt qui sera relu à la prochaine ouverture
	element_patient *liste1 = malloc(sizeof(element_patient));
	liste1=liste->premier;
	FILE * fichier;
	fichier= fopen("sauvegardepat.txt","w");
	if(fichier!=NULL){
		while (liste1!=NULL) {
			fprintf(fichier,"%s,%s,%s,%s,%s,%s",liste1->value->name,liste1->value->year,liste1->value->DateIn,liste1->value->DateOut,liste1->value->pathologie,liste1->value->Observation);
			fprintf(fichier, "\n");	
			liste1=liste1->suivant;	    	
		}
	}
	free(liste1);
	fclose(fichier);
}

void inserer_pat(patient_list * liste, patient pat) { // permet d'insérer un patient déjà défini dans la liste existante
 	 element_patient * nouveau = malloc(sizeof(element_patient));
	  patient * new_pat= malloc(sizeof(patient));
	  *new_pat = pat;
	  nouveau->value = new_pat;
	  nouveau->suivant = NULL;
	  if (liste->taille == 0) {
  		  liste->premier = nouveau;
 	 } else {
  		  element_patient * temp = liste->premier;
  		  while(temp->suivant != NULL) {
   			   temp = temp->suivant;
  		  }
 		   temp->suivant = nouveau;
 	 }
 	 liste->taille++;
}

patient init_pat(char * name, char * year, char * DateIn, char * DateOut, char * pathologie, char * Observation) { // initialisation du patient 
  patient pat;
  pat.name = name;
  pat.year = year;
  pat.DateIn = DateIn;
  pat.DateOut = DateOut;
  pat.pathologie = pathologie;
  pat.Observation = Observation;
  return pat;
}

void crea_pat(patient * pat){ // création d'un patient, en allouant la mémoire
  pat->name= malloc (30);
  pat->year = malloc(4);
  pat->DateIn = malloc(9);
  pat->DateOut = malloc(9);
  pat->pathologie = malloc(70);
  pat->Observation = malloc(200);
}

void afficher_liste_pat(patient_list * liste) { //permet grace à un parcours de la liste d'afficher la liste 
  element_patient * temp = liste->premier;
	printf("\n/////////////////////////////////////////////////////////////////////");
	printf("\nTaille actuelle : %d\n", liste->taille);
 if(liste->taille == 0){
  	printf("La liste est vide, rien à afficher!\n");
  }
  while(temp != NULL) {
    printf("Nom : %s\tÂge: %s\tDate d'internement: %s\tDate de sortie: %s\nPathologie: %s;\nObservation:%s:\n\n", temp->value->name,temp->value->year,temp->value->DateIn,temp->value->DateOut,temp->value->pathologie,temp->value->Observation);
    temp = temp->suivant;
  }
  printf("\n");
}

void fill_pat (patient_list* pl){ // permet de lire dans le fichier de sauvegarde les caractéristiques de chaque patient
	FILE *fichier;
	fichier= fopen("sauvegardepat.txt","r");
	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		patient pat;
		while ((read = getline(&line, &len, fichier)) != -1) {
			crea_pat(&pat); // A refaire pour chaque élément sinon réécriture sur le 1er élément
			sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", pat.name, pat.year, pat.DateIn, pat.DateOut,pat.pathologie, pat.Observation);		
			inserer_pat(pl,pat); 				    	
		}
	}
	fclose(fichier);	
}

int comparer_patients(patient pat1, patient pat2){ // fonction comparant deux patient pat1 et pat2.Permet de retrouver un patient précisément. Est notemment utile pour la fonction supprimer
	if (strcmp(pat1.name, pat2.name) == 0){
		if (strcmp(pat1.year, pat2.year) == 0){
			if(strcmp(pat1.DateIn, pat2.DateIn) ==0){
				if(strcmp(pat1.DateOut, pat2.DateOut) ==0){
					if(strcmp(pat1.pathologie, pat2.pathologie) ==0){
						if(strcmp(pat1.Observation, pat2.Observation) ==0){
							return 1; 
						}
					}
				}
			}
		}
    } 
	return 0; 
}


void delete_pat (patient_list * liste, patient pat){    //Supprime un élément de la liste des patients à l'aide de la fonction précédente, et en fonction de 3 cas: 
	if(liste-> taille ==0){ // soit liste est vide --> on fait rien 
		printf("La liste ne contient aucun élément!\n");
		return; 
	}
	if(comparer_patients(*(liste->premier->value), pat) ==1){ // soit c'est le premier --> rediriger element premier vers le 2e 
		element_patient *temp1;
		temp1 = liste->premier; 
		liste->premier = liste->premier->suivant; 
		free(temp1); 
		liste->taille --; 
		return; 
	}
	element_patient *temp1 = liste->premier; // soit c'est au milieu de la liste --> le précédent doit pointer ver le suivant 
	element_patient *temp2 = NULL; 
	while(comparer_patients(*(temp1->value), pat) !=1) {
		temp2 = temp1; 
		temp1 = temp1->suivant; 
	}
	temp2->suivant = temp1->suivant; 
	free(temp1); 
	liste->taille --; 
}

 

/* <-----------> MAIN DU FICHIER SERVANT A FAIRE LES TESTS UNITAIRES <-------------> 
int main(int argc, char const *argv[]) {
  patient_list *liste = malloc(sizeof(patient_list));
  liste->taille = 0;
  liste->premier = NULL; 
   
  patient * mon_patient = malloc(sizeof(patient));
  *mon_patient = init_pat("AAA", "BBB", "CCC", "DDD", "EEE", "FFF");
  inserer_pat(liste, *mon_patient);
  afficher_liste_pat(liste); 

  patient * mon_patient_deux = malloc(sizeof(patient));
  *mon_patient_deux = init_pat("Nom2", "Year2", "", "", "", "");
  inserer_pat(liste, *mon_patient_deux);
  afficher_liste_pat(liste); 

  patient * mon_patient_trois = malloc(sizeof(patient));
  *mon_patient_trois = init_pat("Nom3", "Year3", "", "", "", "");
  inserer_pat(liste, *mon_patient_trois);
  afficher_liste_pat(liste); 

  delete_pat (liste, *mon_patient_deux); 
  afficher_liste_pat(liste); 
  save_pat(liste); 
  afficher_liste_pat(liste);
  return 0;
} */ 
