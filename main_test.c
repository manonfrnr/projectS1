#include "pathologie.h"
#include "patient.h"
#include "docteur.h"
#include "fileattente.h"


/*void action_user(liste_pathologie * liste_pathologie, patient_list * liste_patient, docteur_list * liste_docteur, file_patient * liste_urgence){
	int value=0;
	int value2=0;
	int num=0;
	int echapp=9;
	while(value !=echapp){
		value=0;
		printf("Que voulez vous faire?\n");
		printf("\t\t1 - Afficher element(s)\n");
		printf("\t\t2 - Ajouter un element\n");
		printf("\t\t3 - Supprimer un element\n");
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
				if(value2==1){
					afficher_liste_pat(liste_patient);
				}
				if(value2==2){
					afficher_liste_pat(liste_patient);
					printf("Quel patient voulez-vous afficher en detaille?");
					while(num<1&&num>liste_patient->taille){
						scanf("%d",&num);
					}
					afficher_patient(liste_patient,num);
				}
				if(value2==3){
					afficher_liste_doc(liste_docteur);
				}
				if(value2==4){
					afficher_path(liste_pathologie);
				}
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
						patient_urgence * patient_attente=malloc(sizeof(patient_urgence ));
						patient * Patient=malloc(sizeof(patient));
						printf("Patient à ajouter?");
						afficher_file_attente(liste_urgence);
						patient_attente=defiler_file_attente(liste_urgence);
						Patient->name=patient_attente->name;
						inserer_pat(liste_patient, *Patient);
						afficher_liste_pat(liste_patient);
					}
					else{
						printf("Impossible de rajouter un patient");
					}
				}
				if(value2==2){
					patient_urgence * urgence=malloc(sizeof(patient_urgence ));
					initialisation_patient_urgence(urgence);
					scanf("%s",urgence->name);
					scanf("%s",urgence->symptome);
					scanf("%s",urgence->heure_arrivee);
					set_patient_urgence(urgence,urgence->name,urgence->symptome,urgence->heure_arrivee);
				}

				if(value2==3){
					docteur * docteur=malloc(sizeof(docteur));
					init_doc(docteur);
					scanf("%s",docteur->name);
					scanf("%s",docteur->university);
					scanf("%s",docteur->speciality);
					scanf("%s",docteur->review);
					*docteur=set_doc(docteur->name,docteur->university,docteur->speciality,docteur->review);
					inserer_doc(liste_docteur,*docteur);
				}
				if(value2==4){
					pathologie * pathologie=malloc(sizeof(pathologie));
					crea_path(pathologie);
					scanf("%s",pathologie->nom);
					scanf("%s",pathologie->definition);
					*pathologie=init_path(pathologie->nom,pathologie->definition);
					inserer_path(liste_pathologie,*pathologie);
				}
			}
		}

		if(value==3){
			printf("Que voulez vous faire?\n");
			printf("\t\t1 - Supprimer un patient\n");
			printf("\t\t2 - Supprimer un docteur\n");
			printf("\t\t5 - Retour");
			while(value2!=5){
				value2=0;
				scanf("%d",&value2);
				if(value2==1){
					if(liste_patient->taille!=0){

					}
					else{
						printf("Impossible de supprimer un patient");
					}
				}
				if(value2==2){
					if(liste_patient->taille!=0){
						//delete_doc
					}
					else{
						printf("Impossible de supprimer un docteur\n");
					}
				}
			}
		}
	}



	save_pat(liste_patient);
	save_doc(liste_docteur);
	save_urgence(liste_urgence);

	printf("\n\n\t\tMerci d'avoir utiliser Hopital manage's patient\n\n\n\n ");
} */








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
	liste_urgence->fin=NULL;


	patient * mon_patient = malloc(sizeof(patient));
  *mon_patient = init_pat("AAA", "BBB", "CCC", "DDD", "EEE");
	mon_patient->Docteur = liste_docteur->premier->value;
	mon_patient->Pathologie = liste_pathos->premier->value;
  inserer_pat(liste_patient, *mon_patient);

	patient * mon_patient2 = malloc(sizeof(patient));
  *mon_patient2 = init_pat("ZZZ", "BBB", "CCC", "DDD", "EEE");
	mon_patient2->Docteur = liste_docteur->premier->value;
	mon_patient2->Pathologie = liste_pathos->premier->suivant->value;
  inserer_pat(liste_patient, *mon_patient2);

	patient * mon_patient3 = malloc(sizeof(patient));
  *mon_patient3 = init_pat("WWW", "BBB", "CCC", "DDD", "EEE");
	mon_patient3->Docteur = liste_docteur->premier->suivant->value;
	mon_patient3->Pathologie = liste_pathos->premier->value;
  inserer_pat(liste_patient, *mon_patient3);

	afficher_liste_pat(liste_patient);

	printf("\n------------------------\n");
	printf("path:%s\n", get_path_by_name(liste_pathos, "Cyanose")->nom);

	patient_list * pathooo = get_patients_by_path(liste_patient, *(get_path_by_name(liste_pathos, "Cyanose")));
	afficher_liste_pat(pathooo);


	//afficher_liste_doc(liste_docteur);

 	//interaction de l'utilisateur.
	//action_user(liste_pathos,liste_patient,liste_docteur,liste_urgence);

	return 0;
}
