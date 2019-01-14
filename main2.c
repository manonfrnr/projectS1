#include "pathologie.h"
#include "patient.h"
#include "docteur.h"
#include "fileattente.h"

liste_pathologie *liste_pathos;
patient_list *liste_patient; 
docteur_list *liste_docteur;
file_patient *file_urgence; 
	
void menu_patient()
{
	while (1)
	{
		int choix; 
		printf("\t\t1- Afficher la liste des patients \n");
		printf("\t\t2- Rechercher un patient\n");
		printf("\t\t3- Crée un patient\n");
		printf("\t\t4- Supprimer un Patient\n");
		printf("\t\t5- Retour\n");
		scanf ("%d", &choix); 

		switch(choix)
		{
			case 1: { // Pour afficher la liste des patients
				afficher_liste_pat(liste_patient);
				break; 
			}

			case 2: { // Pour rechercher un patient 
				char name[30];
				printf("Quel est le nom du patient ?");
				scanf("%s", name);
				afficher_patient(get_pat_by_name(liste_patient, name));
				break; 
			}

			case 3: { //  Pour créer un patient
				patient * pat = malloc(sizeof(patient));
				char * temp_path = malloc(100);
				char * temp_doc = malloc(100);
				crea_pat(pat); 
				printf("Quel nom ?"); 
				scanf("%s", pat->name); 
				printf("Son âge?"); 
				scanf("%s", pat->year); 
				printf("Sa date d'admision?"); 
				scanf("%s" ,pat->DateIn); 
				printf("Sa date de sortie ?"); 
				scanf("%s", pat->DateOut); 
				printf("Sa pathologie ?"); 
				scanf("%s", temp_path);
				pat->Pathologie = get_path_by_name(liste_pathos, temp_path);
				printf("Son médecin: voulez vous le médecin disponible le plus rapidement ou choisir votre médecin ?\n");
				scanf("%s", temp_doc);
				if(strlen(temp_doc) <= 1) {
					pat->Docteur = get_free_doc(liste_docteur, liste_patient);
				} else {
					pat->Docteur = get_doc_by_name(liste_docteur, temp_doc);
				}
				printf("Des observations ?\n");
				scanf("%s", pat->Observation); 
				inserer_pat(liste_patient,*pat); 
				save_pat(liste_patient); 
				break; 
			}

			case 4: { //Pour supprimer un patient 
				// Recherche du patient
				char pat_suppr[20]; 
				printf("Quel est le nom du patient que vous voulez supprimer ?\n");
				scanf("%s", pat_suppr); 
				delete_pat(liste_patient, *(get_pat_by_name(liste_patient, pat_suppr))); 
				save_pat(liste_patient); 
				break; 
			}

			case 5: // Retour
				return; 
				break; 

			default:
				printf("Choix incorrect.\n");
				break; 
		}
	}	
}

void menu_docteur()
{
	while(1)
	{
		int choix; 
		printf("\t\t1- Afficher la liste des docteurs \n");
		printf("\t\t2- Rechercher un docteur\n");
		printf("\t\t3- Crée un docteur\n");
		printf("\t\t4- Supprimer un Docteur\n");
		printf("\t\t5- Retour\n");
		scanf ("%d", &choix); 

		switch(choix)
		{
			case 1: { // Pour afficher la liste des docteurs
				afficher_liste_doc(liste_docteur);
			}

			case 2: { // Pour rechercher un docteur
				char name[30];
				printf("Quel est le nom du médecin ?");
				scanf("%s", name);
				afficher_doc(get_doc_by_name(liste_docteur, name));
				break; 
			}

			case 3: { //  Pour créer un docteur
				docteur *doc;
				doc = malloc(sizeof(docteur)); 
				init_doc(doc); 
				printf("Quel nom ?"); 
				scanf("%s", doc->name); 
				printf("Son Université diplomante?"); 
				scanf("%s", doc->university); 
				printf("Sa spécialité?"); 
				scanf("%s" ,doc->speciality); 
				printf("Un avis sur lui?"); 
				scanf("%s", doc->review); 
				printf("Son médecin: voulez vous le médecin disponible le plus rapidement ou choisir votre médecin ?\n");
				///////////////////////////////////// A REMPLIR 

				inserer_doc(liste_docteur,*doc); 
				save_doc(liste_docteur); 
				break; 
			}

			case 4: //Pour supprimer un docteur 
			{
				// Recherche du docteur
				char doc_suppr[20];  
				printf("Quel est le nom du patient que vous voulez supprimer ?\n");
				scanf("%s", doc_suppr); 
				delete_doc(liste_docteur, *(get_doc_by_name(liste_docteur, doc_suppr))); 
				save_doc(liste_docteur); 
				break;
			}

			case 5: // Retour
				break; 

			default:
				printf("Choix incorrect.\n");
				break; 
		}
	}
}	

void menu_urgence ()
	{	
		while(1)
		{
			int choix; 
			printf("\t\t1- Ajouter un patient à la liste d'attente \n");
			printf("\t\t2- Récupérer un patient \n");
			printf("\t\t3- Afficher la file d'attente\n");
			printf("\t\t5- Retour\n");
			scanf ("%d", &choix);

			switch(choix)
			{
				case 1: // Pour ajouter un patient à la file d'attente
				{
					patient_urgence *pat_u; 
					pat_u = malloc(sizeof(patient_urgence)); 
					initialisation_patient_urgence(pat_u); 
					printf("Nom du patient ?\n");
					scanf("%s", pat_u->name);
					printf("Symptomes?\n");
					scanf("%s", pat_u->symptome);
					printf("Heure d'arrivée?\n");
					scanf("%s", pat_u->heure_arrivee); 
					enfiler_file_attente ( file_urgence, *pat_u);
				}

				case 2: { // Pour récupérer un patient
					patient pat_recup;
					patient_urgence pat_u;
					char patho_temp[50];
				 	pat_u = *(defiler_file_attente (file_urgence));
				 	printf("Le patient %s est appelé pour son rendez-vous\n", pat_u.name);
				 	pat_recup = *(conversion_patient(&pat_u)); 
				 	printf("Quelle date sommes nous aujourd'hui?\n");
				 	scanf("%s", pat_recup.DateIn); 
				 	printf("Après visite médicale, de quelle pathologie souffre le patient?\n");
				 	scanf("%s", patho_temp); 
				 	pat_recup.Pathologie = get_path_by_name(liste_pathos, patho_temp);
				 	pat_recup.Docteur = get_free_doc(liste_docteur, liste_patient);
				 	inserer_pat(liste_patient, pat_recup);
				 	save_pat(liste_patient);
					break; 
				}

				case 3: { //  Pour afficher la file d'attente
					afficher_file_attente(file_urgence); 
					break;
				}

				case 5: // Retour
					return;
					break; 

				default:
					printf("Choix incorrect.\n");
					break; 
			}
		}
	}		


void menu_pathologies ()
{
	while(1)
	{
		int choix;
		printf("\t\t1- Afficher la liste des pathologies \n");
		printf("\t\t2- Ajouter une pathologie\n");
		printf("\t\t5- Retour\n");
		scanf ("%d", &choix);
		switch(choix)
		{
			case 1: // Pour afficher la liste des pathologies
				afficher_path(liste_pathos); 

			case 2: { // Pour ajouter une pathologie
				pathologie *patho; 
				patho = malloc(sizeof(pathologie)); 
				crea_path(patho);  
				printf("Nom de la pathologie ?\n");
				scanf("%s", patho->nom);
				printf("Definition?\n");
				scanf("%s", patho->definition);
				break;
			} 


			case 5: // Retour
				return;
				break; 

			default:
				printf("Choix incorrect.\n");
				break; 
		}

	}
}

void action_user(){
	printf("Bienvenue dans le logiciel de gestion de Patients! \n");
	int choix; 
	while (1)
	{
		printf("Que souhaitez vous faire ?\n");
		printf("\t\t1- Accéder au menu Patients\n");
		printf("\t\t2- Accéder au menu Médecins\n");
		printf("\t\t3- Accéder au menu Urgences\n");
		printf("\t\t4- Accéder au menu Pathologies\n");
		printf("\t\t9- Quitter le programme\n");
		scanf("%d", &choix); 
		switch (choix)
		{
			case 1: // Pour accéder au menu patient
			menu_patient(); 
			break; 

			case 2: // Pour accéder au menu Médecins
			menu_docteur(); 
			break; 

			case 3: // Pour accéder au menu Urgence 
			menu_urgence();  
			break; 

			case 4: // Pour accéder au menu Pathologie
			menu_pathologies();
			break;

			case 9:
			return;

		}
	}	



	save_pat(liste_patient);
	save_doc(liste_docteur);
	save_urgence(file_urgence);
	
	printf("\n\n\t\tMerci d'avoir utiliser Hopital manage's patient\n\n\n\n ");

}

int main(){                                                                                                                                                      
	//initialisation des listes

	liste_pathos= malloc(sizeof(liste_pathologie));
  	liste_pathos->taille = 0;
  	liste_pathos->premier = NULL; 
	fill_path(liste_pathos); 

	liste_docteur = malloc(sizeof(docteur_list));
  	liste_docteur->taille = 0;
 	liste_docteur->premier = NULL; 
	remplissage_liste(liste_docteur);

	liste_patient = malloc(sizeof(patient_list));
	liste_patient->taille = 0;
	liste_patient->premier = NULL;
	fill_pat(liste_patient, liste_docteur, liste_pathos);

	file_urgence=malloc(sizeof(file_patient));
	file_urgence->taille=0;
	file_urgence->debut=NULL;
	file_urgence->fin=NULL;
	printf("test\n");
	
 	//interaction de l'utilisateur.
	action_user();

	return 0;
}