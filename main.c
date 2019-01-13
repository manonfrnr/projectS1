#include "pathologie.h"
#include "patient.h"
#include "docteur.h"
#include "fileattente.h"


void action_user(liste_pathologie * liste_pathologie, patient_list * liste_patient, docteur_list * liste_docteur, file_patient * liste_urgence){
	int value;
	int value2;
	int num=0;
	int echapp=9;
	while(value !=echapp){
		value=0;
		printf("Que voulez vous faire?\n");
		printf("\t\t1 - Afficher element(s)\n");
		printf("\t\t2 - Ajouter un element\n");
		printf("\t\t3 - Supprimer un element\n");
		/*printf("\t\t4 - Ajouter un patient qui est présent dans la file d'attente\n");
		printf("\t\t5 - Ajouter un patient dans la file d'attente\n");
		printf("\t\t6 - Afficher tout les medecins\n");
		printf("\t\t7 - Afficher toutes les pathologies\n");*/
		printf("\t\t%d - Quitter le logiciel\n",echapp);
		scanf("%d",&value);
		if(value==1){
			printf("Que voulez vous faire?\n");
			printf("\t\t1 - Afficher les patients\n");
			printf("\t\t2 - Afficher un patient\n");
			printf("\t\t3 - Afficher les docteurs\n");
			printf("\t\t4 - Afficher les pathologies\n");
			printf("\t\t5 - Retour");
			while(value2!=5){
				value2=0;
				scanf("%d",&value2);
				if(value2==1){afficher_liste_pat(liste_patient);}
				if(value2==2){
					afficher_liste_pat(liste_patient);
					printf("Quel patient voulez-vous afficher en detaille?");
					while(num<1&&num>liste_patient->taille){
						scanf("%d",&num);
					}
					afficher_patient(liste_patient,num);			
				}
				if(value2==3){afficher_doc(liste_docteur);}
				if(value2==4){afficher_path(liste_pathologie);}
			}
		}
		if(value==2){
			printf("Que voulez vous faire?\n");
			printf("\t\t1 - Ajouter un patient\n");
			printf("\t\t2 - Ajouter un patient à la liste d'attente\n");
			printf("\t\t3 - Ajouter un docteur\n");
			printf("\t\t4 - Ajouter une pathologie\n");
			printf("\t\t5 - Retour");
			while(value2!=5){
				value2=0;
				scanf("%d",&value2);
				if(value2==1){
					if(liste_patient->taille<25){
						printf("Patient à ajouter?");
						afficher_file_attente(liste_urgence);
						patient_attente=defiler_file_attente(liste_urgence);
						patient=conversionpatient(patient_attente);
						inserer_pat(liste_patient, patient);
						afficher_list(liste_patient);
					}
					else{
						printf("Impossible de rajouter un patient");
					}
				}
				if(value2==2){
					initialisation_patient_urgence(urgence);
					char * name;
					char * symptome;
					char * heure_arrivee;
					scanf("%s",name);
					scanf("%s",symptome);
					scanf("%s",heure_arrivee);
					urgence=set_patient_urgence(name,symptome,heure_arrivee);	
				}
							
				if(value2==3){
					init_doc(docteur);
					char * name;
					char * university;
					char * speciality;
					char * review;	
					scanf("%s",name);
					scanf("%s",university);
					scanf("%s",speciality);
					scanf("%s",review);
					docteur=set_doc(name,university,speciality,review);	
					inserer_doc(liste_docteur,docteur);			
				}
				if(value2==4){
					crea_path(pathologie);
					char * name;
					char * definition;
					scanf("%s",name);
					scanf("%s",definition);
					pathologie=init_path(name,definition);
					inserer_path(liste_pathologie,pathologie);					

				}
			}
		}

		if(value==3){
			printf("Que voulez vous faire?\n");
			printf("\t\t1 - Supprimer un patient\n");
			printf("\t\t2 - Supprimer un docteur\n");
			printf("\t\t3 - Supprimer une pathologie\n");
			printf("\t\t5 - Retour");
			while(value2!=5){
				value2=0;
				scanf("%d",&value2);
				if(value2==1){
					if(listepat->taille!=0){
						
					}
					else{
						printf("Impossible de supprimer un patient");
					}
				}
				if(value2==2){
					
				}
							
				if(value2==3){
				}
			}
		}
	}
	clear();
	printf("Sauvegarde en cours");
	
	save_pat(liste_patient);
	save_doc(liste_docteur);
	//save_urgence(liste_urgence);
	//save_path(liste_pathologie);
	printf("\n\n\t\tMerci d'avoir utiliser Hopital manage's patient\n\n\n\n ");
}








int main(){
	//initialisation des listes

	liste_pathologie *liste_pathos= malloc(sizeof(liste_pathologie));
  	liste_pathos->taille = 0;
  	liste_pathos->premier = NULL; 
	fill_path(liste_pathos); 

	patient_list *liste_patient = malloc(sizeof(patient_list));
	liste_patient->taille = 0;
	liste_patient->premier = NULL;

	docteur_list *liste_docteur = malloc(sizeof(docteur_list));
  	liste_docteur->taille = 0;
 	liste_docteur->premier = NULL; 
	remplissage_liste(liste_docteur);

	file_patient *liste_urgence=malloc(sizeof(file_patient));
	liste_urgence->taille=0;
	liste_urgence->debut=NULL;

 	//interaction de l'utilisateur.
	action_user(liste_pathologie,liste_patient,liste_docteur,liste_urgence);

	return 0;
}
