#ifndef UTIL
#define UTIL


#define HTML_HEAD "./HTML/head.html"
#define HTML_FOOT "./HTML/foot.html"
#define HTML_HOME_HEAD "./HTML/head_home.html"
#define HTML_PRIMARY "./HTML/primary.html"
#define HTML_HOME "./HTML/index.html"
#define HTML_SEARCH "./HTML/search.html"

#define NBR_END_LINES 500


char **allouer2D(char **tab);
void display_fichier(char *chemin);
char ***allouer3D(char ***tab);
int get_nbr_lines_fichier(char *chemin);

#endif