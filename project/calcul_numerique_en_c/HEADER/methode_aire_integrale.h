#ifndef AIRE_H
#define AIRE_H

double calc_aire_method_rect(double (*f)(double), double n, double a, double b);

double calc_aire_method_trapeze(double (*f)(double), double n, double a, double b);

double calc_aire_method_simpson(double (*f)(double), double n, double a, double b);

#endif 
