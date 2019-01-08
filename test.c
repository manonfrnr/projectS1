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

typedef struct element_liste element_liste ;
struct element_liste{
  patient value;
  element_liste * suivant;
};

typedef struct patient_list patient_list;
struct patient_list{
  element_liste *premier;
  int taille;
};

void inserer_pat(patient_list * liste, patient pat) {
  element_liste * nouveau = malloc(sizeof(element_liste));
  nouveau->value = pat;
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
  element_liste * temp = liste->premier;
  while(temp != NULL) {
    printf("Nom : %s\n", temp->value.name);
    temp = temp->suivant;
  }
}

int main(int argc, char const *argv[]) {
  patient_list *liste = malloc(sizeof(patient_list));
  liste->taille = 0;
  printf("Taille init : %d\n", liste->taille);

  patient * mon_patient = malloc(sizeof(patient));
  *mon_patient = init_pat("Nom", "Year", "", "", "", "");
  inserer_pat(liste, *mon_patient);

  patient * mon_patient_deux = malloc(sizeof(patient));
  *mon_patient_deux = init_pat("Nom2", "Year2", "", "", "", "");
  inserer_pat(liste, *mon_patient_deux);

  printf("Taille actuelle : %d\n", liste->taille);
  afficher_liste(liste);
  return 0;
}
