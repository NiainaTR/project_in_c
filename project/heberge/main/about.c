#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display_fichier(char *chemin){
        FILE *fichier = fopen(chemin , "r");
        
        char *line = malloc(1000);
        if (fichier != NULL)
        {
                while(fgets(line , 1000 , fichier) != NULL){
                        printf("%s\n", line);
                }
        }
        fclose(fichier);
}
char** split(char*mot,char ch){
	
    char **MotSeparee=(char**)malloc(sizeof(char*)*100);
	
    for(int i = 0 ; i < 100 ; i++){
		MotSeparee[i] = malloc(100);
	}
	int k=0,j=0;
	for(int i=0; i<strlen(mot); i++){
		if(mot[i]==ch){
			k++;j=0;
		}
		else {
			MotSeparee[k][j] = mot[i];
			j++;
		}
	}
	return MotSeparee;
}
int nbr_ligne_fichier(char *chemin){
    int nbr = 0;

    FILE *file = fopen(chemin , "r");
    
    char *line = malloc(1000);

    if(file != NULL){
        while(fgets(line , 1000 , file) != NULL){
            nbr++;
        }
    } 

    fclose(file);

    return nbr;
}

void pagination(int page, int total , int line_per_page , char *site)
{
    int max = page + line_per_page;

    if(max > total) max = total;

    printf(
        "<footer>"
        "<ul class='pagination'>"
    );

    for (int i = page; i <= max; i++){
        printf("<li><a href='http://www.configure.com/cgi/about.cgi?site=%s&page=%d'>%d</a></li>" ,site,i , i);    
    }

    printf(
        "</ul>"
        "</footer>"
    );
    
}

char **get_date_hour(char *date){
    char **tab=(char**)malloc(sizeof(char*)*100);
	
    for(int i = 0 ; i < 100 ; i++){
		tab[i] = malloc(100);
	}
    for(int i = 1 , j = 0; i < 12 ; i++ , j++){
        tab[0][j] = date[i]; 
    }
    for(int i = 13 , j = 0; i < strlen(date) ; i++ , j++){
        tab[1][j] = date[i]; 
    }

    return tab;
}

void display_about_site(char *site , int page){
    char * chemin = malloc(500);

    sprintf(chemin , "/var/log/apache2/%s.access.log" , site);

    int nbr_visites = nbr_ligne_fichier(chemin);
    

    FILE *file = fopen(chemin , "r");
    FILE *tempo = fopen("tempo" , "w");
    

    display_fichier("./HTML/head_activation.html");
    
    printf(
        "<div class='container'>"
        "<table>"
            "<caption>"
                "<span class='search-count'>Nombres de visites : %d</span>"
            "</caption>" , nbr_visites);
    


    
    printf(
            "<thead>"
                "<tr>"
                    "<th>N°</th>"
                    "<th>IP client</th>"
                    "<th>Date</th>"
                    "<th>Heure</th>"
                    "<th>Methode Req</th>"
                    "<th>Page Req</th>"
                    "<th>Version HTTP</th>"
                    "<th>Status</th>"
                    "<th>Taille en res</th>"
                    "<th>Page origine du req</th>"
                    "<th>OS</th>"
                    "<th>Navigateur</th>"
                "</tr>"
            "</thead>"
            "<tbody class='content'>"
    );
    
    char *line = malloc(1000);

    int i = 1;
    
    if(file != NULL && tempo != NULL){
        while(fgets(line , 1000 , file) != NULL){
            char **tab = split(line , ' ');
            char **date = get_date_hour(tab[3]);
            fprintf(tempo , "<tr><td>%d</td><td id='ip'>%s</td><td id='date'>%s</td><td id='heure'>%s</td><td id='methode'>%s</td><td id='page'>%s</td><td id='version'>%s</td><td id='status'>%s</td><td id='taille'>%s</td><td id='origin'>%s</td><td id='os'>%s</td><td id='nav'>%s</td></tr>\n",i, tab[0] , date[0] , date[1] , tab[5] , tab[6] , tab[7] , tab[8] , tab[9] , tab[10] , tab[13] , tab[19]);                             
            i++;
        }
    } 
    
    fclose(file);
    fclose(tempo);

    FILE *f1 = fopen("tempo", "r");
        

        int line_per_page = 10;

        int pos_curs = line_per_page * (page - 1);

        char *ligne = malloc(1000);

        int l = 0;
        int count = 0;

        while (fgets(ligne, 1000, f1) != NULL)
        {
            if (l == pos_curs && count < line_per_page)
            {
                printf("%s\n", ligne);
                pos_curs++;
                count++;
            }
            else
            {
                count = 0;
            }
                l++;
        }


    display_fichier("./HTML/foot_activation.html");

    int nbr_pages = nbr_visites / line_per_page;


    if(nbr_pages % line_per_page != 0 || nbr_pages == 0) nbr_pages++;

    printf("<div class='pages'><p> PAGE : %d/%d</p><ul>", page , nbr_pages);
    
    pagination(page, nbr_pages , line_per_page , site);

}


int main(){
    char *url = getenv("QUERY_STRING");
    
    printf("Content-Type:text/html\n\n");
    
    char *site = NULL;
    int page = 1;

    sscanf(url , "site=%m[^&]&page=%d" , &site , &page);

    display_about_site(site , page);
    

    return 0;
}