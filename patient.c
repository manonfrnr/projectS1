#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct patient patient;
struct patient{
  char *name;
  char *year;
  char *DateIn;
  char *DateOut;
  char *Pathologie;
  char *Observation;
};

typedef struct element_patient element_patient ;
struct element_patient{
  patient * value;
  element_patient * suivant;
};

typedef struct patient_list patient_list;
struct patient_list{
  element_patient *premier;
  int taille;
};

typedef struct pathologie pathologie;
struct pathologie{
  char * name;
  char * definition;
  patient * value1;
  patient * value2;
  patient * value3;
  patient * value4;
};

typedef struct element_pathologie element_pathologie ;
struct element_pathologie{
  pathologie * value;
  element_pathologie * suivant;
};

typedef struct liste_pathologie liste_pathologie;
struct patient_list{
  element_pathologie *premier;
  int taille;
};

void save (patient_list * liste){
	patient_list *liste1 = malloc(sizeof(patient_list));
	liste1=liste;
	FILE * fichier;
	fichier= fopen("sauvegarde.txt","w");
	if(fichier!=NULL){
		while (liste1->premier!=NULL) {
			fprintf(fichier,"%s,%s,%s,%s,%s,%s",liste1->premier->value->name,liste1->premier->value->year,liste1->premier->value->DateIn,liste1->premier->value->DateOut,liste1->premier->value->Pathologie,liste1->premier->value->Observation);	
			liste1->premier=liste1->premier->suivant;	    	
		}
	}
	free(liste1);
	fclose(fichier);
}

void inserer_pat(patient_list * liste, patient pat) {
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


patient init_pat(char * name, char * year, char * DateIn, char * DateOut, char * Pathologie, char * Observation) {
  patient pat;
  pat.name = name;
  pat.year = year;
  pat.DateIn = DateIn;
  pat.DateOut = DateOut;
  pat.Pathologie = Pathologie;
  pat.Observation = Observation;
  return pat;
}

void crea_pat(patient * pat){
  pat->name= malloc (30);
  pat->year = malloc(4);
  pat->DateIn = malloc(9);
  pat->DateOut = malloc(9);
  pat->Pathologie = malloc(70);
  pat->Observation = malloc(200);
}

void afficher_liste(patient_list * liste) {
  element_patient * temp = liste->premier;
	printf("\n/////////////////////////////////////////////////////////////////////");
	printf("\nTaille actuelle : %d\n", liste->taille);
  while(temp != NULL) {
    printf("Nom : %s\tÂge: %s\tDate d'internement: %s\tDate de sortie: %s\nPathologie: %s;\nObservation:%s;\n\n", temp->value->name,temp->value->year,temp->value->DateIn,temp->value->DateOut,temp->value->Pathologie,temp->value->Observation);
    temp = temp->suivant;
  }
  printf("\n");
}


void fill_pat (patient_list* pl){
	FILE *fichier;
// Fonction qui permet le remplissage des données patients dans la "liste"
	fichier= fopen("sauvegarde.txt","r");
	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		patient pat;
		while ((read = getline(&line, &len, fichier)) != -1) {
			crea_pat(&pat); // A refaire pour chaque élément sinon réécriture sur le 1er élément
			sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", pat.name, pat.year, pat.DateIn, pat.DateOut,pat.Pathologie, pat.Observation);
			
			inserer_pat(pl,pat);
			printf("étape4\n");		    	
		}printf("étape5\n");
	}printf("étape6\n");
	fclose(fichier);
	
}



void delete_pat (patient_list * liste, patient * pat){
//Supprime un élément de la liste des patients
	element_patient * liste1 = malloc(sizeof(element_patient *));
	liste1=liste->premier;
	if(liste->taille==0){
		printf("Aucun élémént à supprimer");
		return;printf("\ntest1\n");
	}
	if(liste1->value==NULL){
		liste1=liste1->suivant;printf("\ntest2\n");
	}
	
	while((liste1->suivant != NULL)  &&  (pat != liste1->value)){
		if(pat!=liste1->value){
		liste1=liste1->suivant;printf("\ntest3\n");}
		else{break;}		
	}
	printf("\ntest4\n");
	if(liste1->suivant->suivant !=NULL){		
	liste1=liste1->suivant->suivant;
	}
	else{liste1=NULL;}	
	printf("\ntest4\n");		
	//liste->taille--;
	save(liste);
	return;
}



int main(int argc, char const *argv[]) {
  patient_list *liste = malloc(sizeof(patient_list));
  liste->taille = 0;
  printf("Taille init : %d\n", liste->taille);
	fill_pat(liste);
 /* patient * mon_patient = malloc(sizeof(patient));
  *mon_patient = init_pat("Nom", "Year", "", "", "", "");
  inserer_pat(liste, *mon_patient);
	
	printf("Taille actuelle : %d\n", liste->taille);afficher_liste(liste);*/

  patient * mon_patient_deux = malloc(sizeof(patient));
  *mon_patient_deux = init_pat("Nom2", "Year2", "", "", "", "");
  /*inserer_pat(liste, *mon_patient_deux);

  printf("Taille actuelle : %d\n", liste->taille);
  afficher_liste(liste);
  
  patient * mon_patient = malloc(sizeof(patient));
   *mon_patient = init_pat("Nom", "Year", "in", "out", "path", "obs");
  inserer_pat(liste, *mon_patient);*/
  afficher_liste(liste);
	
	delete_pat(liste,mon_patient_deux);	printf("\ntest\n");
	//fill_pat(liste);
	save(liste);printf("\ntest\n");
	
	
	inserer_pat(liste, *mon_patient_deux);
	fill_pat(liste);
	printf("2\n");
	  afficher_liste(liste);
	printf("7");
	save(liste);
  afficher_liste(liste);
  return 0;
}
