#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/tsanta/webC/authlog/header/util.h"





int is_bissex(int year){
    int bool = 0;
    if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        bool = 1;
    }
    return bool;
}

int indicMois(int m){

    int indic = 0;

    int *dict = (int *)malloc(100 * sizeof(int));
    
    

    dict[0] = 0;
    dict[1] = 3;
    dict[2] = 3;
    dict[3] = 6;
    dict[4] = 1;
    dict[5] = 4;
    dict[6] = 6;
    dict[7] = 2;
    dict[8] = 5;
    dict[9] = 0;
    dict[10] = 3;
    dict[11] = 5;

    for (int i = 1; i < 13; i++){
        if(m == i) indic = dict[i-1];
    }

    return indic;
}

int get_nbr_jour_par_siecle(int year){
    int nbr = 0;

    int reste = (year / 100) % 4;

    int *dict = (int *)malloc(100 * sizeof(int));
    
    dict[0] = 6;
    dict[1] = 4;
    dict[2] = 2;
    dict[3] = 0;

    for (int i = 0; i < 4; i++){
        if(i == reste) nbr = dict[i];
    }

    return nbr;
}

char * date_to_formGasy(int jour , int mois , int annee , char *heure){
    char *date = malloc(1000);

    int numJour = 0;

    char **jrSemaine = NULL;
    jrSemaine = allouer2D(jrSemaine);

    strcpy(jrSemaine[0] , "Alahady");
    strcpy(jrSemaine[1] , "Alatsinainy");
    strcpy(jrSemaine[2] , "Talata");
    strcpy(jrSemaine[3] , "Alarobia");
    strcpy(jrSemaine[4] , "Alakamisy");
    strcpy(jrSemaine[5] , "Zoma");
    strcpy(jrSemaine[6] , "Sabotsy");
    
    
    char **DouzeMois = NULL;
    DouzeMois = allouer2D(jrSemaine);

    strcpy(DouzeMois[1] , "Janoary");
    strcpy(DouzeMois[2] , "Febroary");
    strcpy(DouzeMois[3] , "Martsa");
    strcpy(DouzeMois[4] , "Aprily");
    strcpy(DouzeMois[5] , "May");
    strcpy(DouzeMois[6] , "Jona");
    strcpy(DouzeMois[7] , "Jolay");
    strcpy(DouzeMois[8] , "Aogositra");
    strcpy(DouzeMois[9] , "Septambra");
    strcpy(DouzeMois[10] , "Oktobra");
    strcpy(DouzeMois[11] , "Noavambra");
    strcpy(DouzeMois[12] , "Desambra");

    if(mois < 3 && is_bissex(annee) == 1) annee -= 1;

    int aa = annee % 100;
    int nbr_year_bissex = aa / 4;
    
    numJour = (jour + aa + nbr_year_bissex + indicMois(mois) + get_nbr_jour_par_siecle(annee)) % 7;
    
    sprintf(date, "%s %d %s %d tamin'ny %s", jrSemaine[numJour], jour, DouzeMois[mois], annee, heure);

    return date;
}
