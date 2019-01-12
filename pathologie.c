#include <stdio.h>
#include <stdlib.h>

typedef struct patient patient;
struct patient{
	char *name;
	char *year;
	char *DateIn;
	char *DateOut;
	char *pathologie;
	char *Observation;
};

typedef struct pathologie pathologie;
struct pathologie{
  	char * nom;
  	char *definition;
};

typedef struct element_pathologie element_pathologie ;
struct element_pathologie{
  	pathologie * value;
 	element_pathologie * suivant;
};

typedef struct liste_pathologie liste_pathologie;
struct liste_pathologie{
  	element_pathologie *premier;
  	int taille;
};

void inserer_path(liste_pathologie * liste, pathologie patho) {
 	element_pathologie * nouveau = malloc(sizeof(element_pathologie));
	pathologie * new_path= malloc(sizeof(pathologie));
	*new_path = patho;
	nouveau->value = new_path;
	nouveau->suivant = NULL;
	if (liste->taille == 0) {
  		liste->premier = nouveau;
 	} else {
  		element_pathologie * temp = liste->premier;
  		while(temp->suivant != NULL) {
   			temp = temp->suivant;
  		}
 	temp->suivant = nouveau;
 	}
 	liste->taille++;
}

pathologie init_path(char * nom, char * definition) {
  pathologie patho;
  patho.nom = nom;
  patho.definition = definition;
  return patho;
}

void crea_path(pathologie * patho){
  patho->nom= malloc (30);
  patho->definition = malloc(250);
}

void afficher_path(liste_pathologie * patho) {
  	element_pathologie * temp = patho->premier;
	printf("\n/////////////////////////////////////////////////////////////////////");
	printf("\nTaille actuelle : %d\n", patho->taille);
  while(temp != NULL) {
    printf("Nom : %s\t\nDefinition: %s\t\n\n", temp->value->nom,temp->value->definition);
    temp = temp->suivant;
  }
  printf("\n");
}

void fill_path (liste_pathologie* lp){
	FILE *fichier;
// Fonction qui permet le remplissage des données patients dans la "liste"
	fichier= fopen("pathologie.txt","r");
	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		pathologie patho;
		while ((read = getline(&line, &len, fichier)) != -1) {
			crea_path(&patho); // A refaire pour chaque élément sinon réécriture sur le 1er élément
			sscanf(line,"%[^,],%[^,]", patho.nom, patho.definition);
			
			inserer_path(lp,patho);
					    	
		}
	}
	fclose(fichier);
	
}

int main(int argc, char const *argv[])
{
	liste_pathologie *liste = malloc(sizeof(liste_pathologie));
  	liste->taille = 0;
  	liste->premier = NULL; 
  	fill_path(liste); 
  	afficher_path(liste);
 	char* dada = malloc(10); 
 	char* def= malloc(50); 
  	dada="Bonjour";
  	def="Hello"; 
  	pathologie *nouvelle_patho = malloc(sizeof(pathologie)); 
  	nouvelle_patho->nom = dada; 
  	nouvelle_patho->definition = def; 
  	inserer_path(liste, *nouvelle_patho); 

  	afficher_path(liste); 
	return 0;
}