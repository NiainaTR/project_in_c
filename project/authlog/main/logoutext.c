#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "/home/tsanta/webC/authlog/header/util.h"


int main(){
    
    
    int taille =  atoi(getenv("CONTENT_LENGTH"));
    char *data = malloc(taille + 1);
    
   if(fgets(data, taille + 1, stdin) != NULL){
        
        FILE *fichier = fopen("connected.txt" , "r");
        FILE *f = fopen("tempo", "w");

        char *id_find;
        char *id;

        sscanf(data, "%*[^=]=%ms", &id_find);


        char *line = malloc(1000);

        if (fichier != NULL && f != NULL)
        {
            
            while (fgets(line, 1000, fichier) != NULL)
            {
                sscanf(line, "%m[^\n]", &id);

                if (strcmp(id_find, id) != 0)
                {
                    fprintf(f, "%s", line);
                }
            }
        }

            fclose(fichier);
            fclose(f);

            FILE *f1 = fopen("connected.txt" , "w");
            FILE *f2 = fopen("tempo", "r");
            
           if (fichier != NULL && f != NULL)
            {
            
                while(fgets(line , 1000, f2) != NULL)
                {
                    fprintf(f1 , "%s", line); 
                }

            }


            fclose(fichier);
            fclose(f);
       }

        printf("Location: http://www.webc.com\n\n");

        return 0;
}