#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"


char** allouer_2D(char** tab,int nombre1,int nombre2){
	tab = malloc(nombre1 * sizeof(char*));
	for(int i = 0 ; i < nombre1 ; i++){
		tab[i] = malloc(nombre2);
	}
	return tab;
}

char **split(char *str , const char *delimiter){
	char **result = NULL;
	result = allouer_2D(result , 10 , 100);
	
	char *chaine = strtok(str , delimiter);
	
	int i = 0;
	while(chaine != NULL){
		strcpy(result[i] , chaine);
		i++;
		chaine = strtok(NULL , delimiter);
	}
	return result;
}



int get_nbr_ligne(char *chemin_fichier){
	FILE *fichier = fopen(chemin_fichier , "r");
	char *tmp = malloc(100);
	int nbr_ligne = 0;
	if(fichier != NULL){
		while(fgets(tmp , 100 , fichier) != NULL){
			nbr_ligne++;
		}
	}
	fclose(fichier);
	return nbr_ligne;
}

Pc* get_ligne_fichier_pc(Pc *pc , char * chemin_fichier , int nbr){
	FILE* fichier = NULL;
	fichier = fopen(chemin_fichier ,"r");
	
	for(int i=0;i<nbr;i++){
		char tmp[256];
		char **tab = NULL;
		tab = allouer_2D(tab , 200 , 200);
		fgets(tmp , 256 , fichier);
		tab = split(tmp , ",");
		strcpy(pc[i].label , tab[0]);
		strcpy(pc[i].marque , tab[1]);
		strcpy(pc[i].mac_address , tab[2]);
		free(tab);
	}
	fclose(fichier);
	return pc;
}

Etudiant* get_ligne_fichier_etudiant(Etudiant* etudiant, char * chemin_fichier , int nbr){
	FILE* fichier = NULL;
	fichier = fopen(chemin_fichier ,"r");
	for(int i=0;i<nbr;i++){
		char ch[255];
		fgets(ch,255,fichier);
		sscanf(ch,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",etudiant[i].nom,etudiant[i].prenom,etudiant[i].tel,etudiant[i].email,etudiant[i].adress,etudiant[i].date_de_naissance,etudiant[i].lieu_de_naissance,etudiant[i].bacc_year,etudiant[i].genre,etudiant[i].cin,etudiant[i].lien_git);
		//printf("%s, %s, %s", val[i].pc,val[i].mac,val[i].label);
	}
	fclose(fichier);
	return etudiant;
}


void sort_etudiant(Etudiant* etudiant ,int nbr){
    Etudiant tmp;
    int bool = 0;
    while (bool==0){
        bool = 1;
        for (int i=0;i<nbr-1;i++){
            if (strcmp(etudiant[i].nom,etudiant[i+1].nom)>0){
                tmp = etudiant[i];
                etudiant[i] = etudiant[i+1];
                etudiant[i+1] = tmp; 
                bool = 0;
            }
        }
    }
}

void sort_pc(Pc* pc , int nbr){
    Pc tmp;
    int bool = 0;
    while (bool == 0){
        bool = 1;
        for (int i=0;i<nbr;i++){
            if (strcmp(pc[i].label,pc[i+1].label)>0){
                tmp = pc[i];
                pc[i] = pc[i+1];
                pc[i+1] = tmp; 
                bool = 0;
            }
        }
    }
}



void put_pc_data_in_fichier(Pc *pc ,  char *chemin_fichier , int nbr){
	FILE *fichier = fopen(chemin_fichier , "w+");
	for(int i = 0 ; i < nbr ; i++){
		fprintf(fichier , "%s,%s,%s\n" , pc[i].label, pc[i].marque , pc[i].mac_address);
	}
	fclose(fichier);
}
void put_etudiant_data_in_fichier(Etudiant *etudiant ,  char *chemin_fichier , int nbr){
	FILE *fichier = fopen(chemin_fichier , "w+");
	
	for(int i = 0 ; i < nbr ; i++){
		fprintf(fichier , "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n" , etudiant[i].nom , etudiant[i].prenom , etudiant[i].tel ,  etudiant[i].email ,etudiant[i].adress ,  etudiant[i].date_de_naissance ,etudiant[i].lieu_de_naissance ,etudiant[i].bacc_year ,etudiant[i].genre ,etudiant[i].cin ,etudiant[i].lien_git);
	}
	fclose(fichier);
}


