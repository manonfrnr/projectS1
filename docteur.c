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
    printf("Nom : %s \nUniversité : %s\nSpécialité: %s\nAvis sur le médecin: %s\n", temp->value->name, temp->value->university, temp->value->speciality, temp->value->review);
   	printf("Taille de la liste:%d\n",liste->taille );
    printf("\n\n");

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

int comparer_docteurs(docteur doc1, docteur doc2){
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

void save (docteur_list * liste){
	docteur_list *liste1 = malloc(sizeof(docteur_list));
	liste1=liste;
	FILE * fichier;
	fichier= fopen("sauvegarde.txt","w");
	if(fichier!=NULL){
		while (liste1->premier!=NULL) {
			fprintf(fichier,"%s,%s,%s,%s",liste1->premier->value->name,liste1->premier->value->university,liste1->premier->value->speciality,liste1->premier->value->review);	
			fprintf(fichier, "\n");
			liste1->premier=liste1->premier->suivant;	    	
		}
	}
	free(liste1);
	fclose(fichier);
}

void delete_doc (docteur_list * liste, docteur doc){    //Supprime un élément de la liste des patients
	// soit liste est vide --> on fait rien 
	// soit c'est le premier --> redef element premier vers le 2e 
	// soit c'est au milieu de la liste --> le précédent doit pointer ver le suivant 
	if(liste-> taille ==0)
	{
		printf("La liste ne contient aucun élément!\n");
		return; 
	} 

	if(comparer_docteurs(*(liste->premier->value), doc) ==1)
	{ 
		element_liste *temp1;
		temp1 = liste->premier; 
		liste->premier = liste->premier->suivant; 
		free(temp1); 
		liste->taille --; 
		return; 
	}

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
  afficher_liste(liste);

  docteur * mon_docteur_trois = malloc(sizeof(docteur));
  *mon_docteur_trois = set_doc("MANON", "MANON", "MANON", "MANON");
  inserer_doc(liste, *mon_docteur_trois);
  afficher_liste(liste);

  delete_doc(liste, *mon_docteur_deux);
  // printf("Taille actuelle : %d\n", liste->taille);
  //afficher_liste(liste);

  //remplissage_liste(liste);

  printf("\n\n\n"); 
  afficher_liste(liste);
  save(liste); 

  
  return 0;
}
