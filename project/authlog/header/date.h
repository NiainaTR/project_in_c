#ifndef DATE
#define DATE

int is_bissex(int year);
int indicMois(int m);
int get_nbr_jour_par_siecle(int year);
char *date_to_formGasy(int jour, int mois, int annee, char *heure);

#endif