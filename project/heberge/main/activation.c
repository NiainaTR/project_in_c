
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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
		MotSeparee[i] = malloc(1000);
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


int is_enable(char *conf){
    int is_enable = 0;
    
    const char *chemin_dossier = "/etc/apache2/sites-enabled";

    DIR *dossier = opendir(chemin_dossier);

    if (dossier == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

     struct dirent *entree;

    while ((entree = readdir(dossier)) != NULL) {
        if (strcmp(entree->d_name, ".") != 0 && strcmp(entree->d_name, "..") != 0) {
            if(strcmp(entree->d_name , "000-default.conf") != 0){
                if(strcmp(entree->d_name , conf) == 0) is_enable = 1;
            }
        }
    }

    closedir(dossier);


    return is_enable;

}


void find_sites_availables(){
    
   const char *chemin_dossier = "/etc/apache2/sites-available";


   
    DIR *dossier = opendir(chemin_dossier);

    if (dossier == NULL) {
        perror("Erreur lors de l'ouverture du dossier");
        exit(EXIT_FAILURE);
    }

                
    FILE *fichier_write = fopen("sites" , "w");
                

 
    struct dirent *entree;

    while ((entree = readdir(dossier)) != NULL) {
        
        if (strcmp(entree->d_name, ".") != 0 && strcmp(entree->d_name, "..") != 0) {
            if(strcmp(entree->d_name , "000-default.conf") != 0  && strcmp(entree->d_name , "default-ssl.conf") != 0){
               
                char *chemin = malloc(1000);

                sprintf(chemin , "%s/%s" , chemin_dossier , entree->d_name);
                
                
                FILE *fichier_read = fopen(chemin , "r");

                char *line = malloc(256);

                if(fichier_read != NULL && fichier_write != NULL){
                    while(fgets(line , 256 , fichier_read) != NULL){
                        if(!strchr(line , '#')){
                            if(strstr(line , "ServerName ")){
                                char *tmp = malloc(100);
                                sscanf(line , "\tServerName %s" , tmp);
                                is_enable(entree->d_name) == 1 ? fprintf(fichier_write , "%s    1\n" , tmp) : fprintf(fichier_write , "%s    0\n" , tmp);
                            }
                        }
                        
                    }
                }
            }
        }
    }

    fclose(fichier_write);
    closedir(dossier);

}

int nbr_ligne_fichier(char *chemin){
    int nbr = 0;

    FILE *file = fopen(chemin , "r");
    
    char *line = malloc(256);

    if(file != NULL){
        while(fgets(line , 256 , file) != NULL){
            nbr++;
        }
    } 

    fclose(file);

    return nbr;
}


void pagination(int page, int total , int line_per_page)
{
    int max = page + line_per_page;

    if(max > total) max = total;

    printf(
        "<footer>"
        "<ul class='pagination'>"
    );

    for (int i = page; i <= max; i++){
        printf("<li><a href='http://www.configure.com/cgi/activation.cgi?is=1&search=&page=%d'>%d</a></li>" ,i , i);    
    }

    printf(
        "</ul>"
        "</footer>"
    );
    
    
}



void display_all(int page){

    find_sites_availables();

    int nbr_site_available = nbr_ligne_fichier("sites");

    FILE *file = fopen("sites" , "r");
    FILE  *tmp = fopen("tmp" , "w");

    char *line = malloc(256);
    char *domaine = NULL;
    int is_activate = 0;

    int i = 1;

    display_fichier("./HTML/head_activation.html");
    
    printf(
        "<div class='container'>"
        "<table>"
            "<caption>"
                "<span class='search-count'>Sites availables : %d</span>"
            "</caption>" , nbr_site_available);
    
    printf(
            "<thead>"
                "<tr>"
                    "<th>N°</th>"
                    "<th>ServerName</th>"
                    "<th>Activate / Desactivate</th>"
                    "<th>About</th>"
                "</tr>"
            "</thead>"
            "<tbody class='content'>"
    );

    if(file != NULL && tmp != NULL){
        while(fgets(line , 256 , file) != NULL){
           sscanf(line , "%ms   %d" , &domaine , &is_activate);
            if(is_activate == 1){
                fprintf(tmp , "<tr><td>%d</td><td>%s</td><td><p class='session opened'><a href='http://www.configure.com/cgi/activationext.cgi?is=1&search=&page=%d&site=%s&a=0'>Desactivate</a></p></td><td><a href='http://www.configure.com/cgi/about.cgi?site=%s&page=1'>STAT</a></td></tr>\n" , i , domaine ,page, domaine , domaine);                 
            }                                                                                                                                                                  
            else{
                fprintf(tmp , "<tr><td>%d</td><td>%s</td><td><p class='session closed'><a href='http://www.configure.com/cgi/activationext.cgi?is=1&search=&page=%d&site=%s&a=1'>Activate</a></p></td><td><a href='http://www.configure.com/cgi/about.cgi?site=%s&page=1'>STAT</a></td></tr>\n" , i , domaine ,page, domaine , domaine);                     
            }
            i++;
        }
    } 
    
    
    fclose(file);
    fclose(tmp);

        FILE *f1 = fopen("tmp", "r");
        

        int line_per_page = 10;

        int pos_curs = line_per_page * (page - 1);

        char *ligne = malloc(1000);

        int l = 0;
        int count = 0;

        while (fgets(ligne, 1000, f1) != NULL)
        {
            if (l == pos_curs && count < line_per_page)
            {
                printf("%s", ligne);
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
    
    int nbr_pages = nbr_site_available / line_per_page;


    if(nbr_pages % line_per_page != 0 || nbr_pages == 0) nbr_pages++;

    printf("<div class='pages'><p> PAGE : %d/%d</p><ul>", page , nbr_pages);
    
    pagination(page, nbr_pages , line_per_page);

}


int main() {
    char *data = getenv("QUERY_STRING");
   
    printf("Content-Type:text/html\n\n");

    char *search = NULL;
    int is_premier = 0;
    int page = 1;

    sscanf(data , "is=%d&search=%s&page=%d" , &is_premier , search , &page);
    
    if(is_premier == 1){
        display_all(page);
    }
    
    return 0;
}
