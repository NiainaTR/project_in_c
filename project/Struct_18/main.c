#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"



int main(){
	
	//Sorter le fichier pc et le mettre dans un autre fichier 
	int nbr_ligne_fpc = get_nbr_ligne("./fichier_source/PC.csv");//nbr de ligne du fichier pc
	
	Pc *pc = malloc(sizeof(Pc)*nbr_ligne_fpc);
	
	pc = get_ligne_fichier_pc(pc , "./fichier_source/PC.csv" , nbr_ligne_fpc);
	
	sort_pc(pc , nbr_ligne_fpc);//sorter par ordre alphabetique
	
	put_pc_data_in_fichier(pc , "./fichier_source/PC.csv" , nbr_ligne_fpc);
	
	
	
	//Sorter le fichier etudiant et le mettre dans un autre fichier 
	int nbr_ligne_fetudiant = get_nbr_ligne("./fichier_source/etudiant.csv");//nbr de ligne du fichier pc
	
	Etudiant *etudiant = malloc(sizeof(Etudiant)*nbr_ligne_fetudiant);
	
	etudiant = get_ligne_fichier_etudiant(etudiant , "./fichier_source/etudiant.csv" , nbr_ligne_fetudiant);

	
	sort_etudiant(etudiant , nbr_ligne_fetudiant);//sorter par ordre alphabetique
		

	put_etudiant_data_in_fichier(etudiant , "./fichier_source/etudiant_sort.csv" , nbr_ligne_fetudiant);
	
	
	return 0;
}
