#ifndef PATHOLOGIE
#define PATHOLOGIE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pathologie pathologie; // création de la structure pathologie, chaque pathologie comprenant un nom et une explication
struct pathologie{
  	char * nom;
  	char *definition;
};

typedef struct element_pathologie element_pathologie ; // création de la structure qui servira d'élement liste
struct element_pathologie{
  	pathologie * value;
 	element_pathologie * suivant;
};

typedef struct liste_pathologie liste_pathologie; // création de la structure liste
struct liste_pathologie{
  	element_pathologie *premier;
  	int taille;
};

void inserer_path(liste_pathologie * liste, pathologie patho);
pathologie init_path(char * nom, char * definition);
void crea_path(pathologie * patho);
void afficher_path(liste_pathologie * patho);
void fill_path (liste_pathologie* lp);
int compare_path(pathologie path1, pathologie path2);
pathologie * get_path_by_name(liste_pathologie * liste, char * name);

#endif
