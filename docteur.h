#ifndef DOCTEUR
#define DOCTEUR

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

void inserer_doc(docteur_list * liste, docteur doc);
docteur set_doc(char * name, char * university, char * speciality, char * review);
void init_doc(docteur * doc);
void afficher_liste_doc(docteur_list * liste);
void remplissage_liste (docteur_list *dl);
int comparer_docteurs(docteur doc1, docteur doc2);
void save_doc (docteur_list * liste);
void delete_doc (docteur_list * liste, docteur doc);
docteur * get_doc_by_name(docteur_list * liste, char * name);

#endif
