# Matrice_in_c
Calcul matricielle en C

Ce programme a pour but de faciliter les calculs matricielles  , mais cette version ne prend pas encore en charge les fractions.

-Contenus :
  -libmatrice.a(bibliothèque statique)
  -matrice.c(fichier source contenant toutes les fonctions)
  -matrice.h(en-tête)

-Utilisation:
  -Inclure le fichier d'en-tête dans votre programme 
  -Exemple de commande de compilation:
  gcc main.c -o main -L(chemin vers la bibliothèque statique) -lmatrice

-Les fonctions dans la bibliothèque:
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

