#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "/home/tsanta/heberge/header/util.h"


void display_fichier(char *chemin){
        FILE *fichier = fopen(chemin , "r");

        char *line = malloc(256);
        if (fichier != NULL)
        {
                while(fgets(line , 256 , fichier) != NULL){
                        printf("%s\n", line);
                }
        }
        fclose(fichier);
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

   
    closedir(dossier);

}


int *get_info(char *search)
{ // retourne ['bool' , 'linetotal'];

    int *info = malloc(5 * sizeof(int));

    int bool = 0;
    int total = 0;

    
    FILE *fichier = popen( , "r");

    char *line = malloc(1000);


    //%[a-zA-Z0-9]
    int annee = 0;
    int mois = 0;
    int jour = 0;


    char *heure = malloc(100);
    char *date = malloc(100);

    char *session;
    char *user;

    if(fichier != NULL){

    while (fgets(line, 1000, fichier) != NULL)
    {
        if(strstr(line , "for user")){
            sscanf(line, "%[^T]T%[^.]%*[^ ] %*s%*s%*s%*s%ms%*s%*s%ms", date , heure , &session , &user);
            user = strtok(user, "(");
            sscanf(date , "%d-%d-%d" , &jour , &mois , &annee);
            if(strcmp(user ,search) == 0){
                bool = 1;
                total++;
            }
        }
    }

    }

    free(cmd);
    free(line);
    free(heure);
    free(date);
    
    
    info[0] = bool;
    info[1] = total;
    return info;
}



void affiche_connected(char *search , int page, char *id , int line_per_page){
    
    if(search == NULL && page == 1){
        
        display_fichier(HTML_PRIMARY);
        
        //printf("<h1>%s</h1>",id);
        printf(" <header>\n"
               "<form action='' method='get'>\n");
        printf("<input type='text' name='search' placeholder='Entrer votre recherche...'>\n"
               "<input type='hidden' name='page' value=1>\n");
        printf("<input type='hidden' name='id' value=%s>\n",id);
        printf(
            "<button type='submit'>rechercher</button>\n"
            "</form>\n");     
    }

    else{
        if (get_info(search)[0] == 0)
        {
             printf("<h1>data not found</h1>");
        }
        else{
        display_fichier(HTML_HOME_HEAD);
        
        int total = get_info(search)[1];
        
        printf(" <header>\n"
               "<form action='http://www.webc.com/cgi-bin/authlog/connected.cgi' method='get'>\n");
        printf("<input type='text' name='search' placeholder='Entrer votre recherche...'>\n"
               "<input type='hidden' name='page' value=1>\n");
        printf("<input type='hidden' name='id' value=%s>\n",id);
        printf(
            "<button type='submit'>rechercher</button>\n"
            "</form>\n");

          printf("<form action='http://www.webc.com/cgi-bin/authlog/logoutext.cgi' method='post'>\n"
               "<input type='hidden' name='id' value='%s'/>"
               "<button type='submit' id='logout'>Se deconnecter</button></form>\n"
               "</header>\n" , id
        );

        printf(
               "<div class='container'>\n"
               "<table>\n"
               "<caption>\n");

        printf("<span class='search-count'>Resultats trouvés : %d</span>", total);
        
         printf("</caption>\n"
           "<thead>\n"
           "    <tr>\n"
           "        <th>N°</th>\n"
           "        <th>Utilisateurs</th>\n"
           "        <th>Session</th>\n"
           "        <th>Date</th>\n"
           "    </tr>\n"
           "</thead>\n"
           "<tbody class='content'>\n"
           );

        //printf("<table border='1'><tr><th>TEMPS</th><th>SESSION (opened / closed)</th><th>UTILISATEURS</th></tr>");

        char *cmd = malloc(1000);

        sprintf(cmd, "tail -%d %s", NBR_END_LINES, "/var/log/auth.log");

        FILE *fichier = popen(cmd , "r");


        
        char *line = malloc(1000);

        //%[a-zA-Z0-9]
        int annee = 0;
        int mois = 0;
        int jour = 0;


        char *heure = malloc(100);
        char *date = malloc(100);

        char *session;
        char *user;
        
        FILE *f = fopen("tmp", "w");

        int number = 1;
        if (fichier != NULL && f != NULL)
        {
            
            while (fgets(line, 1000, fichier) != NULL)
            {   
                if (strstr(line, "for user"))
                {
                    // sscanf(line, "%15m[^\n]%*s%*s%*s%*s%ms%*s%*s%ms", &date , &session , &user);
                    sscanf(line, "%[^T]T%[^.]%*[^ ] %*s%*s%*s%*s%ms%*s%*s%ms", date, heure, &session, &user);
                    user = strtok(user, "(");
                    sscanf(date, "%d-%d-%d", &annee, &mois, &jour);
                    if (strstr(user , search))
                    {   
                        fprintf(f , "<tr><td>%d</td><td>%s</td><td><p class=%s>%s</p></td><td>%s</td></tr>\n", number  , user ,   session[0] == 'o' ? "'session opened'" : "'session closed'" , session , date_to_formGasy(jour , mois , annee , heure));
                        number++;
                    }
                }
            }
        }

       
        fclose(fichier);
        fclose(f);  
    
        FILE *f1 = fopen("tmp", "r");

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
     printf("</tbody>\n"
               "</table>\n"
            "</div>\n");

        
        int nbr_pages = total / line_per_page;


        if(total % line_per_page != 0) nbr_pages++;


        printf("<div class='pages'><p> PAGE : %d/%d</p><ul>", page , nbr_pages);

        pagination(page, nbr_pages, line_per_page , search , id);

        }

    }

}



