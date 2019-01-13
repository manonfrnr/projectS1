#ifndef FILEATTENTE
#define FILEATTENTE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct patient_urgence patient_urgence; // création du type patient_urgence, avec toutes ses caractéristiques (nom, symptome, heure arrivée)
struct patient_urgence{
  char *name;
  char *symptome;
  char *heure_arrivee; 
};

typedef struct element_file element_file;  // création du type de la file, en premier arrivé, premier sorti 
struct element_file{	
	patient_urgence *value; 
	element_file *suivant; 
};

typedef struct file_patient file_patient; //liste doublement chainée
struct file_patient { // structure qui permet un meilleur controle de la file, en ayant toujours accès à don premier élément, son dernier et sa taille
	element_file *debut; 
	element_file *fin; 
	int taille; 
};  


void set_patient_urgence (patient_urgence * pat, char *name, char *symptome, char *heure_arrivee); 
void initialisation_patient_urgence (patient_urgence * pat); 
void initialisation_file ( file_patient * file_attente); 
void enfiler_file_attente ( file_patient * file_attente, patient_urgence nouveau_pat); 
patient_urgence * defiler_file_attente (file_patient *file_attente);
void afficher_file_attente(file_patient *file_attente); 
void save_urgence (file_patient *file_attente);
#endif
