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
  patient value;
  element_patient * suivant;
};

typedef struct patient_list patient_list;
struct patient_list{
  element_patient *premier;
  int taille;
};

void inserer_pat(patient_list * liste, patient pat) {
  element_patient * nouveau = malloc(sizeof(element_patient));
  nouveau->value = pat;
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

/*void delete_pat (patient_list * liste, patient pat){
//Supprime un élément de la liste des patients

	patient_list * temp1=NULL;
	patient_list * temp2=liste;
	while(strcmp(pat->name,temp2->value.name) !=0){
		temp1=temp2;
		temp2=((element_patient *)temp2->suivant);
	}

	if(temp1== NULL){
		liste=((element_patient *)liste->suivant);
	}

	else{
		temp1->suivant =temp2 -> suivant;
		free(temp2);
	}
}*/

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

void afficher_liste(patient_list * liste) {
  element_patient * temp = liste->premier;
  while(temp != NULL) {
    printf("Nom : %s\n", temp->value.name);
    temp = temp->suivant;
  }
  printf("\n");
}


void fill_pat (patient_list* pl){
	FILE *fichier;
// Fonction qui permet le remplissage des données patients dans la "liste"
	fichier= fopen("patient.txt","r");

	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		int protection=0;
		//pl=supprentete(pl);
		while (((read = getline(&line, &len, fichier)) != -1)&&(protection!=15)) {
			//printf("\n%d\t",protection);
		//	printf("\n%d\t",pl->size);
		//	printf("\n%s\n", line);
			char name[50];
			char year[50];
			char di[50];
			char Do[50];
			char path[50];
			char obs[50];
			//sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", pat->patname, pat->year, pat->DateIn, pat->DateOut, pat->Pathologie, pat->Observation);

			sscanf(line,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]", name,year,di,Do,path, obs);
			patient pat=init_pat(name, year, di, Do, path, obs);
			inserer_pat(pl,pat);
			afficher_liste(pl);
			printf("\ntest\n");
			protection++;
		    	
		}
	printf("\nfin while\n");
	//pl=supprentete(pl);
	afficher_liste(pl);
	}
	
}



int main(int argc, char const *argv[]) {
  patient_list *liste = malloc(sizeof(patient_list));
  liste->taille = 0;
  printf("Taille init : %d\n", liste->taille);

  patient * mon_patient = malloc(sizeof(patient));
  *mon_patient = init_pat("Nom", "Year", "", "", "", "");
  inserer_pat(liste, *mon_patient);
	
	printf("Taille actuelle : %d\n", liste->taille);afficher_liste(liste);

  patient * mon_patient_deux = malloc(sizeof(patient));
  *mon_patient_deux = init_pat("Nom2", "Year2", "", "", "", "");
  inserer_pat(liste, *mon_patient_deux);

  printf("Taille actuelle : %d\n", liste->taille);
  afficher_liste(liste);
  return 0;
}
