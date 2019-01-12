#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct patient patient; // création de la structure patient. Chaque patient est défini par un nom, un age, une date d'entrée et de sortie, une maladie et des observations
struct patient{
  char *name;
  char *year;
  char *DateIn;
  char *DateOut;
  char *pathologie;
  char *Observation;
};

typedef struct element_patient element_patient ; // création de la structure element_patient qui sont contenus dans la liste. Ils contiennent eux même les patients
struct element_patient{
  patient * value;
  element_patient * suivant;
};

typedef struct patient_list patient_list; // création de la structure liste, liste d'element_patient
struct patient_list{
  element_patient *premier;
  int taille;
};

void save (patient_list * liste){ // fonction qui permet la sauvegarde de la liste en l'écrivant dans un fichier .txt qui sera relu à la prochaine ouverture
	patient_list *liste1 = malloc(sizeof(patient_list));
	liste1=liste;
	FILE * fichier;
	fichier= fopen("sauvegarde.txt","w");
	if(fichier!=NULL){
		while (liste1->premier!=NULL) {
			fprintf(fichier,"%s,%s,%s,%s,%s,%s",liste1->premier->value->name,liste1->premier->value->year,liste1->premier->value->DateIn,liste1->premier->value->DateOut,liste1->premier->value->pathologie,liste1->premier->value->Observation);
			fprintf(fichier, "\n");	
			liste1->premier=liste1->premier->suivant;	    	
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
  		  liste->premier = nouveau;printf("2\n");
 	 } else {
  		  element_patient * temp = liste->premier;printf("2b\n");
  		  while(temp->suivant != NULL) {printf("3\n");
   			   temp = temp->suivant;
  		  }
 		   temp->suivant = nouveau;printf("4\n");
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

void afficher_liste(patient_list * liste) { //permet grace à un parcours de la liste d'afficher la liste 
  element_patient * temp = liste->premier;
	printf("\n/////////////////////////////////////////////////////////////////////");
	printf("\nTaille actuelle : %d\n", liste->taille);
 if(temp == NULL){
  	printf("La liste est vide!\n");
  }
  while(temp != NULL) {
    printf("Nom : %s\tÂge: %s\tDate d'internement: %s\tDate de sortie: %s\nPathologie: %s;\nObservation:%s;\n\n", temp->value->name,temp->value->year,temp->value->DateIn,temp->value->DateOut,temp->value->pathologie,temp->value->Observation);
    temp = temp->suivant;
  }
  printf("\n");
}

void fill_pat (patient_list* pl){ // permet de lire dans le fichier de sauvegarde les caractéristiques de chaque patient
	FILE *fichier;
	fichier= fopen("sauvegarde.txt","r");
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
	if(comparer_patients(*(liste->premier->value), pat) ==1){ // soit c'est le premier --> redef element premier vers le 2e 
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

int main(int argc, char const *argv[]) {
  patient_list *liste = malloc(sizeof(patient_list));
  liste->taille = 0;
  liste->premier = NULL; 
   
  patient * mon_patient = malloc(sizeof(patient));
  *mon_patient = init_pat("AAA", "BBB", "CCC", "DDD", "EEE", "FFF");
  inserer_pat(liste, *mon_patient);
  afficher_liste(liste); 

  patient * mon_patient_deux = malloc(sizeof(patient));
  *mon_patient_deux = init_pat("Nom2", "Year2", "", "", "", "");
  inserer_pat(liste, *mon_patient_deux);
  afficher_liste(liste); 

  patient * mon_patient_trois = malloc(sizeof(patient));
  *mon_patient_trois = init_pat("Nom3", "Year3", "", "", "", "");
  inserer_pat(liste, *mon_patient_trois);
  afficher_liste(liste); 

  delete_pat (liste, *mon_patient_deux); 
  save(liste); 
  afficher_liste(liste);
  return 0;
}
