#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/tsanta/webC/authlog/header/util.h"
#include "/home/tsanta/webC/authlog/header/date.h"
#include "/home/tsanta/webC/authlog/header/pagination.h"

#define LINE_PER_PAGE 10

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
int is_connected(char *chemin , char *user_find){
    
    FILE *fichier = fopen(chemin , "r");

    char *line = malloc(1000);

    char *user;
    int bool;


    if (fichier != NULL)
    {

        while (fgets(line, 1000, fichier) != NULL)
        {
        
            sscanf(line , "%ms   %d" , &user , &bool);
            if (strcmp(user , user_find) == 0 && bool == 1)
            {
                return 1;
            }
        }
    }

    return 0;
}

int main(){
    
    char *data = getenv("QUERY_STRING");
    
    if(data == NULL){
        printf("Content-Type:text/html\n\n");
        printf("<h1>ERROR</h1>");
    }
    
    else{       
                char *search = NULL;
                int page;

                char *id = NULL;

                char **tab = split(data, '&');

                char **tab1 = split(tab[0], '=');
                search = tab1[1];

                char **tab2 = split(tab[1], '=');
                page = atoi(tab2[1]);

                char **tab3 = split(tab[2], '=');
                id = tab3[1];
                
                if(strcmp(search , "") == 0) search = NULL;

            if(is_connected("connected.txt" , id) == 0){
                printf("Location: http://www.webc.com\n\n");
            }
            else{
                printf("Content-Type:text/html\n\n");
                affiche_connected(search, page, id, LINE_PER_PAGE);
                display_fichier(HTML_FOOT);
            }
            
            

            //printf("<h1>%s</h1>", id);

            // char *search = NULL;
            // int page;

            // char *id = NULL;
            // int session;

            // char *tmp = malloc(1000);

            // char **tab = split(data, '&');

            // char **tab1 = split(tab[0], '=');
            // search = tab1[1];

            // char **tab2 = split(tab[1], '=');
            // page = atoi(tab2[1]);

            // char **tab3 = split(tab[2], '=');
            // id = tab3[1];
            
            // char **tab4 = split(tab[3], '=');
            // session = atoi(tab4[1]);
            
            // if(strcmp(search , "") == 0) search = NULL;

            // // sscanf(data, "search=%m[^&]&page=%d&id=%m[^&]&session=%d", &search, &page , &id , &session);            
            // if (global.session == 0)
            // {
            //     display_fichier(HTML_HOME);
            // }
            // else{
            //    //Affiche par page
            //     display_fichier(HTML_HOME_HEAD);
            //     affiche_connected(search, page, id, session, LINE_PER_PAGE);
            //     display_fichier(HTML_FOOT);
            // }


    }


  

    return 0;
}