#ifndef C
#define C

typedef struct {
	char nom[50];
	char prenom[50];
	char tel[50];
	char email[255];
	char adress[255];
	char date_de_naissance[255];
	char lieu_de_naissance[255];
	char bacc_year[255];
	char genre[255];
	char cin[255];
	char lien_git[255];
}Etudiant;


typedef struct {
	char label[50];
	char marque[50];
	char mac_address[50];
}Pc;

char **split(char *str , const char *delimiter);
char** allouer_2D(char** tab,int nombre1,int nombre2);
int get_nbr_ligne(char *chemin_fichier);
Etudiant* get_ligne_fichier_etudiant(Etudiant* etudiant , char * chemin_fichier , int nbr);
Pc* get_ligne_fichier_pc(Pc *pc , char * chemin_fichier , int nbr);
void sort_etudiant(Etudiant* etudiant ,int nbr);
void sort_pc(Pc* pc , int nbr);
void put_pc_data_in_fichier(Pc *pc ,  char *chemin_fichier , int nbr);
void put_etudiant_data_in_fichier(Etudiant *etudiant ,  char *chemin_fichier , int nbr);
void initialize_etudiant(Etudiant *etudiant);
void initialize_pc(Pc *pc);

#endif 
