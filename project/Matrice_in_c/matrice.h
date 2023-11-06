#ifndef MATRICE
#define MATRICE
double **Allocation2D(int li , int co);
double ***Allocation3D(int li , int co);
void GetDataMatrice(char nom , double **matrice , int li , int co);
void AfficherMatrice(char nom , double **matrice , int li , int co);
double **AdditionerMatrice(double **matriceA , double **matriceB , int liA , int coA , int liB , int coB);
double **MultiplierMatrice(double **matriceA , double **matriceB , int liA , int coA , int liB , int coB);
double **Transpose(double **matrice , int li , int co);
double Determinant(double **matrice , int li , int co);
double **FindMineur(double **matrice , int li , int co , int n1 , int n2);
double **Comatrice(double **matrice , int li , int co);
double **InverserMatrice(double **matrice , int li , int co);
#endif
