#include <stdio.h>
#include <math.h>
#include "HEADER/methode_aire_integrale.h"

double f(double x) {
    return log(x) - 1;
}



int main() {
    double  nbr_inter = 1000;
    double a = 3.0; // Utilisez des valeurs de type double pour a et b
    double b = 10.0;

    double s_rect = calc_aire_method_rect(f, nbr_inter, a, b);
    double s_trap = calc_aire_method_trapeze(f, nbr_inter, a, b);
    double s_simpson = calc_aire_method_simpson(f, nbr_inter, a, b);

    printf("aire_rect = %f\naire_trap = %f\naire_simpson = %f\n", s_rect, s_trap, s_simpson);

    return 0;
}

