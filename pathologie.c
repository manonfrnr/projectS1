#include "pathologie.h"

void inserer_path(liste_pathologie * liste, pathologie patho) { // fontion qui permet d'insérer une pathologie déjà créée dans la liste
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

pathologie init_path(char * nom, char * definition) { // initiailsation de la pthologie
  pathologie patho;
  patho.nom = nom;
  patho.definition = definition;
  return patho;
}

void crea_path(pathologie * patho){ // création de la pathologie avec allocation de mémoire
  patho->nom= malloc (50);
  patho->definition = malloc(600);
}

void afficher_path(liste_pathologie * patho) { // affichage de la liste des pathologies, en parcourant la liste
  	element_pathologie * temp = patho->premier;
	printf("\n/////////////////////////////////////////////////////////////////////");
	printf("\nTaille actuelle : %d\n", patho->taille);
  while(temp != NULL) {
    printf("Nom : %s\t\nDefinition: %s\t\n\n", temp->value->nom,temp->value->definition);
    temp = temp->suivant;
  }
  printf("\n");
}

void fill_path (liste_pathologie* lp){ // remplissage des pathologies à partir du fichier texte
	FILE *fichier;
// Fonction qui permet le remplissage des données patients dans la "liste"
	fichier= fopen("pathologie.txt","r");

	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		pathologie patho;
		while ((read = getline(&line, &len, fichier)) != -1) {
      if(line[strlen(line) - 1 ] == '\n') {
        line[strlen(line) - 1 ] = '\0'; // On supprime le dernier caractère de la ligne, qui est un '\n'
      }
			crea_path(&patho); // A refaire pour chaque élément sinon réécriture sur le 1er élément
			sscanf(line,"%[^,],%[^,]", patho.nom, patho.definition);
			inserer_path(lp,patho);

		}
	}
	fclose(fichier);
}

int compare_path(pathologie path1, pathologie path2) {
  if(strcmp(path1.nom, path2.nom) == 0) {
    if(strcmp(path1.definition, path2.definition) == 0) {
      return 1;
    }
  }
  return 0;
}

pathologie * get_path_by_name(liste_pathologie * liste, char * name) {
  element_pathologie * elem = liste->premier;
  while(elem != NULL) {
    if(strcmp(elem->value->nom, name) == 0) {
      return elem->value;
    }
    elem = elem->suivant;
  }
  return NULL;
}


/* <-----------> MAIN DU FICHIER SERVANT A FAIRE LES TESTS UNITAIRES <------------->
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
*/
