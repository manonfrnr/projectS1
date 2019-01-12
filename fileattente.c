#include <stdio.h>
#include <stdlib.h>

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

void set_patient_urgence (char *name, char *symptome, char *heure_arrivee){  
	patient_urgence pat; 
	pat.name = name; 
	pat.symptome = symptome; 
	pat.heure_arrivee = heure_arrivee; 
}

void initialisation_patient_urgence (patient_urgence * pat){ // initialisation de la structure du patient urgence, avec allocation de mémoire
	pat->name = malloc (30);
	pat->symptome = malloc(100);
	pat->heure_arrivee = malloc(10); 
}

void initialisation_file ( file_patient * file_attente){ //Création de la file, indispensable avant toute chose.
	file_attente->debut = NULL; 
	file_attente->fin = NULL; 
	file_attente->taille = 0; 
}

void enfiler_file_attente ( file_patient * file_attente, patient_urgence nouveau_pat){ // permet de rajouter un élément en queue de la file
	patient_urgence * pat_a_inserer = malloc(sizeof(patient_urgence));
	*pat_a_inserer = nouveau_pat;
	
	element_file * nouvel_element = malloc(sizeof(element_file));
	nouvel_element->value = pat_a_inserer;
	nouvel_element->suivant = NULL;
	
	if(file_attente->taille == 0) {
		file_attente->debut = nouvel_element;
		file_attente->fin = nouvel_element;
	} else {
		file_attente->fin->suivant = nouvel_element;
		file_attente->fin = nouvel_element;
	}
	file_attente->taille++;
}

patient_urgence * defiler_file_attente (file_patient *file_attente){ // permet de récupérer le premier élément de al file (celui qui est là depuis plus longtemps)
	patient_urgence * pat_a_suppr; 
	if (file_attente->taille ==1){
		pat_a_suppr = file_attente->debut->value; 
		file_attente->debut = NULL; 
		file_attente-> fin = NULL;
	} else if (file_attente->taille == 0){ 
		pat_a_suppr= NULL; 
	} else {
		pat_a_suppr = file_attente->debut->value; 
		file_attente->debut = file_attente->debut->suivant; 
	}
	file_attente->taille --; 
	return pat_a_suppr;  
}

void afficher_file_attente(file_patient *file_attente){// permet grace à un parcours de liste d'affichier la liste 
	element_file *element_temp ; 
	element_temp = file_attente->debut; 
	while (element_temp != NULL){
		printf("Nom: %s, Symptomes %s, Heure d'arrivée %s \n \n", element_temp->value->name, element_temp->value->symptome, element_temp->value->heure_arrivee);
		element_temp = element_temp-> suivant; 
	}
	printf("\n\n Fin de la liste! \n");
}
	
int main(int argc, char const *argv[]){
	return 0;
}