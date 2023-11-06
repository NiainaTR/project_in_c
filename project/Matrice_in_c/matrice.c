#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

double **Allocation2D(int li , int co){
	
	double **resultat = NULL;
	resultat = (double **)malloc(li*sizeof(double*));
	for(int i = 0 ; i < li ; i++){
		resultat[i] = (double*)malloc(co*sizeof(double));
	}
	
	return resultat;
}

double ***Allocation3D(int li , int co){
	double ***resultat = NULL;
	resultat = (double ***)malloc(li*sizeof(double**));
	for(int i = 0 ; i < li ; i++){
		resultat[i] = Allocation2D(li , co);
	}
	
	return resultat;
}


double **InverserMatrice(double **matrice , int li , int co){
	double **inverse = NULL;
	
	if(Determinant(matrice , li , co) == 0){
		printf("Matrice non inversible\n");
		return inverse;
	}
	

	inverse = Allocation2D(li , co);
	
	
	double **TransposeCom = NULL;
	TransposeCom = Allocation2D(li , co);
	
	TransposeCom = Transpose(Comatrice(matrice , li , co) , li , co);
	
	
	for(int i = 0 ; i < li ; i++){
		for(int j = 0 ; j < co ; j++){
			inverse[i][j] = (1 / Determinant(matrice , li , co))*TransposeCom[i][j]	;
		}	
	}
	return inverse;
}




double **Comatrice(double **matrice , int li , int co){
	double **com = NULL;
	com = Allocation2D(li ,co);
	
	for(int i = 0 ; i < li ; i++){
		for(int j = 0 ; j < co ; j++){
			if((i+j) % 2 == 0)
			{
				com[i][j] = Determinant(FindMineur(matrice , li , co , i , j) , li-1 , co-1);
			}
			else{
				com[i][j] = (-1)*Determinant(FindMineur(matrice , li , co , i , j) , li-1 , co-1);
			}
		}	
	}
	
	return com;
}

double **FindMineur(double **matrice , int li , int co , int n1 , int n2){
	double **mineur = NULL;
	mineur = Allocation2D(li-1 , co-1);
	int LiMin = 0;
	int CoMin  = 0;
	
	for(int i = 0 ; i < li ; i++){
		for(int j = 0  ; j < co ; j++){
			if( i != n1 && j != n2 ){
				mineur[LiMin][CoMin] = matrice[i][j];
				CoMin++;		
			}		
				if(CoMin == co - 1){
				CoMin = 0;LiMin++;
			}	
		}
	}
	return mineur;
}


double Determinant(double **matrice , int li , int co){
	double det = 0.0;
	if(li != co){
		printf("Erreur\n");
		return det;
	}
	if(li == 2){
		det = matrice[0][0]*matrice[1][1] - matrice[1][0]*matrice[0][1];
		return det;
	}
	else{
		
		double *Coeff = NULL;
		Coeff = (double*)malloc(co*sizeof(double));
		
		for(int i = 0 ; i < co ; i++){
			Coeff[i] = matrice[0][i];	
		}
		
		for(int i = 0 ; i < li ; i++){
			if(i % 2 == 0){
				det += Coeff[i] * Determinant(FindMineur(matrice , li , co , 0 , i) , li-1 , co-1);
			}
			else{
				det += (-1) * Coeff[i] * Determinant(FindMineur(matrice , li , co , 0 , i) , li-1 , co-1);
			}
		}
	}
	return det;
}

double **Transpose(double **matrice , int li , int co){
	
	double **resultat = NULL;
	resultat = Allocation2D(li , co);
	for(int i = 0 ; i < li ; i++){
		for(int j = 0 ; j < co ; j++){
			resultat[j][i] = matrice[i][j];
		}
	}
	return resultat;
}

double **MultiplierMatrice(double **matriceA , double **matriceB , int liA , int coA , int liB , int coB){
	if(coA != liB){
		printf("Erreur !! \n");
		return NULL;	
	}
	int li = liA , co = coB;
	
	double **resultat = NULL;
	resultat = Allocation2D(li , co);
	
	for(int i = 0 ; i < li ; i++){
		for(int k = 0 ; k < co ; k++){		
			for(int j= 0 ; j < liB ; j++){
				resultat[i][k] += matriceA[i][j]*matriceB[j][k];
			}
			resultat[i][k] = resultat[i][k];
		}
	}
	return resultat;
}

double **AdditionerMatrice(double **matriceA , double **matriceB , int liA , int coA , int liB , int coB){
	if(liA != liB || coA != coB){
		printf("Erreur !! \n");
		return NULL;
	}
	int li = liA , co = coA;
	
	double **resultat = NULL;
	resultat = Allocation2D(li , co);
	
	
	for(int i= 0 ; i < li ; i++){
		for(int j= 0 ; j < co ; j++){
			resultat[i][j] = matriceA[i][j] + matriceB[i][j];
		}
	} 
	return resultat;
}

void GetDataMatrice(char nom , double **matrice , int li , int co){
	for(int i= 0 ; i < li ; i++){
		for(int j= 0 ; j < co ; j++){
			printf("%c[%d][%d] = " , nom  , i , j);
			scanf("%lf" , &matrice[i][j]);
		}
	}
}

void AfficherMatrice(char nom , double **matrice , int li , int co){
	for(int i = 0 ; i < li ; i++){
		if(i == 1){
			printf("  %c = " , nom);
		}
		for(int j = 0 ; j < co ; j++){
			printf("\t%f" , matrice[i][j]);	
		}
		printf("\n");
	}
}
