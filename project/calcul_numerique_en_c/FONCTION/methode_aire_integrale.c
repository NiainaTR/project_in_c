#include <stdio.h> 

double calc_aire_method_rect(double (*f)(double), double n, double a, double b) {
    double s_rect = 0.0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        s_rect += f(a) * h;
        a += h; // Mettre à jour la valeur de a
    }

    return s_rect;
}

double calc_aire_method_trapeze(double (*f)(double), double n, double a, double b) {
    double s_trap = 0.0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        s_trap += f(a) * h + h * (f(a + h) - f(a)) / 2;
        a += h; // Mettre à jour la valeur de a
    }

    return s_trap;
}

double calc_aire_method_simpson(double (*f)(double), double n, double a, double b) {
    double s_simpson = 0.0;
    double h = (b - a) / n;

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            s_simpson += (h / 3) * (f(a) + 4 * f(a + h) + f(a + 2 * h));
        }

        a += h; // Mettre à jour la valeur de a
    }

    return s_simpson;
}

