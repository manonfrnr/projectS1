#include "docteur.h"

void inserer_doc(docteur_list * liste, docteur doc) {
  element_liste * nouveau = malloc(sizeof(element_liste));
  docteur * new_doc = malloc(sizeof(docteur));
  *new_doc = doc;
  nouveau->value = new_doc;
  nouveau->suivant = NULL;
  if (liste->taille == 0) {
    liste->premier = nouveau;
  } else {
    element_liste * temp = liste->premier;
    while(temp->suivant != NULL) {
      temp = temp->suivant;
    }
    temp->suivant = nouveau;
  }
  liste->taille++;
}

docteur set_doc(char * name, char * university, char * speciality, char * review) {
  docteur doc;
  doc.name = name;
  doc.university = university;
  doc.speciality = speciality;
  doc.review = review;
  return doc;
}

void init_doc(docteur * doc) { // initialisation du docteur
  doc->name = malloc(30);
  doc->university = malloc(70);
  doc->speciality = malloc(100);
  doc->review = malloc(150);
}
void afficher_doc(docteur * doc)
{
	if(doc != NULL) {
		printf("Nom : %s \nUniversité : %s\nSpécialité: %s\nAvis sur le médecin: %s\n", doc->name, doc->university, doc->speciality, doc->review);
	} else {
		printf("Impossible d'afficher ce médecin, non trouvé.\n");
	}
}

void afficher_liste_doc(docteur_list * liste) { // fonction qui permet d'afficher la liste entière
  //printf("Taille : %d\n", liste->taille);
  //printf("Premier : %s\n", liste->premier->value->name);
  element_liste * temp = liste->premier;
  while(temp != NULL) {
    afficher_doc(temp->value);
    printf("\n\n");
    temp = temp->suivant;
  }
}

void remplissage_liste (docteur_list *dl)// Fonction qui permet le remplissage des données de médecins dans la liste à partit du fichier de départ ou de sauvegarde
{
	FILE *fichier;
	fichier= fopen("sauvegardedoc.txt","r");
	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		docteur doc;
		while ((read = getline(&line, &len, fichier)) != -1) {
			if(len > 10) { // Sécurité de ligne trop petite
        if(line[strlen(line) - 1 ] == '\n') {
          line[strlen(line) - 1 ] = '\0'; // On supprime le dernier caractère de la ligne, qui est un '\n'
        }
				init_doc(&doc); // A refaire à chaque itération sinon écrit dans la même zone mémoire
				sscanf(line,"%[^,],%[^,],%[^,],%[^,]", doc.name, doc.university, doc.speciality, doc.review);
				inserer_doc(dl, doc);
			}
		}
	}
}

int comparer_docteurs(docteur doc1, docteur doc2){ // fonction de comparaison de deux chaines éléments de type docteur pour pouvoir rechercher un docteur notemment pour le supprimer
	if (strcmp(doc1.name, doc2.name) == 0){
		if (strcmp(doc1.university, doc2.university) == 0){
			if(strcmp(doc1.speciality, doc2.speciality) ==0){
				if(strcmp(doc1.review, doc2.review) ==0){
					return 1;
				}
			}
		}
    }
	return 0;
}

void save_doc (docteur_list * liste){ // fonction qui permet la sauvegarde de la liste par l'écriture dans un fichier
	element_liste *liste1 = liste->premier;
	FILE * fichier;
	fichier= fopen("sauvegardedoc.txt","w");
	if(fichier!=NULL){
		while (liste1!=NULL) {
			fprintf(fichier,"%s,%s,%s,%s",liste1->value->name,liste1->value->university,liste1->value->speciality,liste1->value->review);
			fprintf(fichier, "\n");
			liste1=liste1->suivant;
		}
	}
	fclose(fichier);
}

void delete_doc (docteur_list * liste, docteur doc){    //Supprime un élément de la liste des patients en fonction des 3 cas
	if(liste-> taille ==0)// soit liste est vide --> on fait rien
	{
		printf("La liste ne contient aucun élément!\n");
		return;
	}

	if(comparer_docteurs(*(liste->premier->value), doc) ==1) // utilisation de la fonction comparer_docteurs (cf plus haut)
	{ // soit c'est le premier --> rededirifer element premier vers le 2e
		element_liste *temp1;
		temp1 = liste->premier;
		liste->premier = liste->premier->suivant;
		free(temp1);
		liste->taille --;
		return;
	}
// soit c'est au milieu de la liste --> le précédent doit pointer vers le suivant
	element_liste *temp1 = liste->premier;
	element_liste *temp2 = NULL;
	while(comparer_docteurs(*(temp1->value), doc) !=1) {
		temp2 = temp1;
		temp1 = temp1->suivant;
	}

	temp2->suivant = temp1->suivant;
	free(temp1);
	liste->taille --;
}

docteur * get_doc_by_name(docteur_list * liste, char * name) {
  element_liste * elem = liste->premier;
  while(elem != NULL) {
    if(strcmp(elem->value->name, name) == 0) {
      return elem->value;
    }
    elem = elem->suivant;
  }
  return NULL;
}

/*
<-----------> MAIN DU FICHIER SERVANT A FAIRE LES TESTS UNITAIRES <------------->
int main(int argc, char const *argv[]) {
docteur_list *liste = malloc(sizeof(docteur_list));
  liste->taille = 0;
  liste->premier = NULL;
  printf("Taille init : %d\n", liste->taille);
  docteur * mon_docteur = malloc(sizeof(docteur));
  *mon_docteur = set_doc("AAA", "BBB", "CCC", "DDD");
  inserer_doc(liste, *mon_docteur);
  docteur * mon_docteur_deux = malloc(sizeof(docteur));
  *mon_docteur_deux = set_doc("EEE", "FFF", "GGG", "HHHH");
  inserer_doc(liste, *mon_docteur_deux);
  afficher_liste_doc(liste);
  docteur * mon_docteur_trois = malloc(sizeof(docteur));
  *mon_docteur_trois = set_doc("MANON", "MANON", "MANON", "MANON");
  inserer_doc(liste, *mon_docteur_trois);
  afficher_liste_doc(liste);
  delete_doc(liste, *mon_docteur_deux);
  printf("\n\n\n");
  afficher_liste_doc(liste);
  save(liste);
  return 0;
} */
