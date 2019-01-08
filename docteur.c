#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct docteur docteur;
struct docteur{
  char *name;
  char *university;
  char *speciality;
  char *review;
};

typedef struct element_liste element_liste ;
struct element_liste{
  docteur value;
  element_liste * suivant;
};

typedef struct docteur_list docteur_list;
struct docteur_list{
  element_liste *premier;
  int taille;
};

void inserer_doc(docteur_list * liste, docteur doc) {
  element_liste * nouveau = malloc(sizeof(element_liste));
  nouveau->value = doc;
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

docteur init_doc(char * name, char * university, char * speciality, char * review) {
  docteur doc;
  doc.name = name;
  doc.university = university;
  doc.speciality = speciality;
  doc.review = review;
  return doc;
}

void afficher_liste(docteur_list * liste) {
  element_liste * temp = liste->premier;
  while(temp != NULL) {
    printf("Nom : %s\n", temp->value.name);
    temp = temp->suivant;
  }
}

int main(int argc, char const *argv[]) {
  docteur_list *liste = malloc(sizeof(docteur_list));
  liste->taille = 0;
  printf("Taille init : %d\n", liste->taille);

  docteur * mon_docteur = malloc(sizeof(docteur));
  *mon_docteur = init_doc("Nom", "Université", "", "");
  inserer_doc(liste, *mon_docteur);

  docteur * mon_docteur_deux = malloc(sizeof(docteur));
  *mon_docteur_deux = init_doc("Nom2", "Year2", "", "");
  inserer_doc(liste, *mon_docteur_deux);

  printf("Taille actuelle : %d\n", liste->taille);
  afficher_liste(liste);
  return 0;
}
