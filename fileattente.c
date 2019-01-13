#include "fileattente.h"


void set_patient_urgence (patient_urgence * pat, char *name, char *symptome, char *heure_arrivee){  
	pat->name = name; 
	pat->symptome = symptome; 
	pat->heure_arrivee = heure_arrivee; 
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



patient_urgence * defiler_file_attente (file_patient *file_attente){ // permet de récupérer le premier élément de la file (celui qui est là depuis plus longtemps)
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

patient conversion(patient pat,patient_urgence urgence){
	pat.name = urgence.name;
	Printf("Quel est l'age du patient?");	
	scanf("%s",&pat.year);
	Printf("Date d'entrée du patient?");
	scanf("%s",&pat.DateIn);
	Printf("Date de sortie du patient? (mettre ? si indeterminee)");	
	scanf("%s",pat.DateOut);
	Printf("Pathologie du patient? (mettre ? si indeterminee)");	
	scanf("%s",pat.pathologie);
	pat.Observation = urgence.symptome;
	return pat;
}

void save_urgence (file_patient *file_attente){ // fonction qui permet la sauvegarde de la liste par l'écriture dans un fichier
	element_file *liste1 = malloc(sizeof(element_file));
	liste1=file_attente->debut;
	FILE * fichier;
	fichier= fopen("sauvegarde.txt","w");
	if(fichier!=NULL){
		while (liste1!=NULL) {
			fprintf(fichier,"%s,%s,%s",liste1->value->name,liste1->value->symptome,liste1->value->heure_arrivee);	
			fprintf(fichier, "\n");
			liste1=liste1->suivant;	    	
		}
	}
	free(liste1);
	fclose(fichier);
}
	
/* <-----------> MAIN DU FICHIER SERVANT A FAIRE LES TESTS UNITAIRES <-------------> 
int main(int argc, char const *argv[]){
	patient_urgence * pat1 = malloc(sizeof(patient_urgence));
	initialisation_patient_urgence(pat1);
	set_patient_urgence(pat1, "pat1", "bonjour", "11H");
	
	patient_urgence * pat2 = malloc(sizeof(patient_urgence));
	initialisation_patient_urgence(pat2);
	set_patient_urgence(pat2, "pat2", "truc", "12H");
	
	patient_urgence * pat3 = malloc(sizeof(patient_urgence));
	initialisation_patient_urgence(pat3);
	set_patient_urgence(pat3, "pat3", "dodo", "13H");
	
	file_patient * file_attente = malloc(sizeof(file_patient));
	initialisation_file(file_attente);
	
	enfiler_file_attente(file_attente, *pat1);
	enfiler_file_attente(file_attente, *pat2);
	enfiler_file_attente(file_attente, *pat3);
	
	afficher_file_attente(file_attente);
	
	patient_urgence * pat4 = defiler_file_attente(file_attente);
	printf("Défilé : %s\n", pat4->name);
	
	afficher_file_attente(file_attente); 
	
	return 0;
} */
