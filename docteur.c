#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct docteur docteur; // création du type docteur, avec toutes ses caractéristiques (nom, université diplomante, spécialité, avis)
struct docteur{
	char *name;
 	char *university;
  	char *speciality;
  	char *review;
};

typedef struct element_liste element_liste ;
struct element_liste{
  	docteur * value;
  	element_liste * suivant;
};

typedef struct docteur_list docteur_list;
struct docteur_list{
  	element_liste *premier;
  	int taille;
};

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
    //printf("new_doc : %p\n", new_doc);
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

void init_doc(docteur * doc) {
  doc->name = malloc(30);
  doc->university = malloc(70);
  doc->speciality = malloc(100);
  doc->review = malloc(150);
}

void afficher_liste(docteur_list * liste) {
  element_liste * temp = liste->premier;
  while(temp != NULL) {
    printf("Nom : %s, Université : %s, Adresse en mémoire : %p\n", temp->value->name, temp->value->university, temp->value);
    temp = temp->suivant;
  }
}

void remplissage_liste (docteur_list *dl)
{
	FILE *fichier;
// Fonction qui permet le remplissage des données de médecins dans la "liste"
	fichier= fopen("docteur.txt","r");

	if(fichier!=NULL){
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		docteur doc;
		while ((read = getline(&line, &len, fichier)) != -1) {
			if(len > 10) { // Sécurité de ligne trop petite
				init_doc(&doc); // A refaire à chaque itération sinon écrit dans la même zone mémoire
				sscanf(line,"%[^,],%[^,],%[^,],%[^,]", doc.name, doc.university, doc.speciality, doc.review);
				printf("%s\n",doc.name);
				printf("%s\n",doc.university);
				printf("%s\n",doc.speciality);
				printf("%s\n\n",doc.review);
				inserer_doc(dl, doc);
				printf("BBBBB\n");
			}
		}
	}
}



int main(int argc, char const *argv[]) {
docteur_list *liste = malloc(sizeof(docteur_list));
  liste->taille = 0;
  liste->premier = NULL; 
     /*printf("Taille init : %d\n", liste->taille);

  docteur * mon_docteur = malloc(sizeof(docteur));
  *mon_docteur = set_doc("Nom", "Université", "", "");
  inserer_doc(liste, *mon_docteur);

  docteur * mon_docteur_deux = malloc(sizeof(docteur));
  *mon_docteur_deux = set_doc("Nom2", "Year2", "", "");
  inserer_doc(liste, *mon_docteur_deux);

  // printf("Taille actuelle : %d\n", liste->taille);
  afficher_liste(liste);

  remplissage_liste(liste);

  printf("\n\n\n"); */
  afficher_liste(liste);

  
  return 0;
}
