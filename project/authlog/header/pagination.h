#ifndef PAGES
#define PAGES

int *get_info(char *search);
void pagination(int page, int total , int line_per_page , char *search);
void display_per_page(char *search, int page, int line_per_page);
void affiche_connected(char *search, int page, char *id, int line_per_page);
#endif