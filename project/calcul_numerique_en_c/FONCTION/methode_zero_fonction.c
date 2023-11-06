#include <stdio.h>
#include <math.h>


void dichotomie(double (*f)(double) , double a , double b , double epsilon){
        double alpha = 0.0;

        while(fabs(a-b) > epsilon){
           alpha = (a+b)/2;
           if(f(a) * f(alpha) <= 0){
                b = alpha;
           }
           else if(f(b) * f(alpha) <= 0){
                a = alpha;
           }
           printf("alpha = %f\n" , alpha);
       }
}

void descartes(double (*f)(double) , double a , double b , double epsilon){
	double x0 = a;
	double x1 = b;
	double X = 0.0;
	
	while(fabs(f(x1)) > epsilon){
	  X = x1 - f(x1) * (x1-x0) / (f(x1) - f(x0));
  	  x0 = x1;
  	  x1 = X;
	  printf("alpha = %f\n", x1);	  
	}
	
}

void newton(double (*f)(double) , double (*f_prime)(double) ,double x1 , double epsilon , int iteration){
	double X = 0.0;
	
	for(int i = 0 ; i < iteration ; i++){
		X = x1 - (f(x1) / f_prime(x1));
	  	printf("alpha = %f", X);
		if(fabs(f(X)) > epsilon) break;
	}
}
