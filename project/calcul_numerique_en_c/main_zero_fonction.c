#include <stdio.h> 
#include <math.h> 
#include "HEADER/methode_zero_fonction.h"


double f(double x){
        return log(x) - 1;
}

double f_prime(double x){
	return 1/x;
}


int main(){

	double a = 0.5;
	double b = 5;
	
	double epsilon = 1e-6;
	
	printf("Methode de dichotomie\n");
	
	dichotomie(f , a , b , epsilon);
	
	printf("\nMethode de Descartes\n");	 
	
	descartes(f , a , b , epsilon);
        
        printf("\nMethode de Newton\n");
        
        int iteration = 10;
        double val_approx = a+b/2;
        
	newton(f , f_prime , val_approx , epsilon , iteration);
	
	return 0;
}
