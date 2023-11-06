#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/home/tsanta/webC/authlog/header/util.h"

#define DIMX 1000
#define DIMY 1000
#define DIMZ 1000


int get_nbr_lines_fichier(char *chemin){

    int nbr = 0;

    FILE *fichier = fopen(chemin, "r");

    char *line = malloc(1000);

    while(fgets(line , 1000 , fichier) != NULL){
        nbr++;
    }

    return nbr;
}

char **allouer2D(char **tab){
    tab = malloc(DIMX*sizeof(char *));

    for (int i = 0; i < DIMX; i++){
        tab[i] = malloc(DIMY);
    }

    return tab;
}

char ***allouer3D(char ***tab){
    tab = malloc(DIMZ * sizeof(char **));

    
    for (int i = 0; i < DIMZ; i++){
        tab[i] = malloc(DIMY * sizeof(char *));
        for (int j = 0; j < DIMY ; j++){
            tab[i][j] = malloc(DIMX);
        }
    }

    return tab;
}



void display_fichier(char *chemin){
        FILE *fichier = fopen(chemin , "r");

        char *line = malloc(256);
        if (fichier != NULL)
        {
                while(fgets(line , 256 , fichier) != NULL){
                        printf("%s\n", line);
                }
        }
        fclose(fichier);
}