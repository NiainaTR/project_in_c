#ifndef FONCTION_H
#define FONCTION_H


void dichotomie(double(*f)(double) , double a , double b , double epsilon);
void descartes(double(*f)(double) , double a , double b , double epsilon);
void newton(double(*f)(double) , double(*f_prime)(double) ,double x1 , double epsilon , int iteration);

#endif
