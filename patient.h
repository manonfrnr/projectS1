#ifndef PATIENT
#define PATIENT

typedef struct patient patient; // création de la structure patient. Chaque patient est défini par un nom, un age, une date d'entrée et de sortie, une maladie et des observations
struct patient{
  char *name;
  char *year;
  char *DateIn;
  char *DateOut;
  char *pathologie;
  char *Observation;
};

typedef struct element_patient element_patient ; // création de la structure element_patient qui sont contenus dans la liste. Ils contiennent eux même les patients
struct element_patient{
  patient * value;
  element_patient * suivant;
};

typedef struct patient_list patient_list; // création de la structure liste, liste d'element_patient
struct patient_list{
  element_patient *premier;
  int taille;
};

void save (patient_list * liste); 
void inserer_pat(patient_list * liste, patient pat); 
patient init_pat(char * name, char * year, char * DateIn, char * DateOut, char * pathologie, char * Observation); 
void crea_pat(patient * pat); 
void afficher_liste(patient_list * liste); 
void fill_pat (patient_list* pl); 
int comparer_patients(patient pat1, patient pat2); 
void delete_pat (patient_list * liste, patient pat); 

#endif