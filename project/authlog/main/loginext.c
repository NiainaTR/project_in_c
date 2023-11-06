#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "/home/tsanta/webC/authlog/header/util.h"

char *crypt_pwd(char *pwd){
    char *mdp_crypt = malloc(1000);
    char *cmd = malloc(1000);
    
    sprintf(cmd, "echo %s |sha256sum", pwd);
    
    FILE *fichier = popen(cmd, "r");

    if(fichier == NULL){
        printf("ERROR");
        return NULL;
    }

    fgets(mdp_crypt, 1000, fichier);

    return mdp_crypt;
}



int find(char *chemin_fichier , char *user_find){
    char *ligne = malloc(1000);
    FILE *fichier = fopen(chemin_fichier, "r");

    if(fichier == NULL){        
        printf("Erreur d'ouverture du fichier\n");
        return 0;
    }
    while(fgets(ligne , 1000 , fichier) != NULL){
        
        if (strstr(ligne , user_find))
        {
            return 1;
        }
    }
    return 0;
}



int verify(char *chemin_fichier , char *id_find , char *pwd_find){
    int bool = 0;

    char *ligne = malloc(1000);
    char *id, *pwd;

    FILE *fichier = fopen(chemin_fichier, "r");

    if(fichier == NULL){        
        printf("Erreur d'ouverture du fichier\n");
        return 0;
    }
    pwd_find[strlen(pwd_find) - 1] = '\0';
    
    while(fgets(ligne , 1000 , fichier) != NULL){
        sscanf(ligne, "%m[^;];%m[^\n]\n", &id, &pwd);
      //  printf("%s %s\n", pwd_find , pwd);
        if (strcmp(id, id_find) == 0 && strcmp(pwd, pwd_find) == 0)
        {
            bool = 1;
        }
    }
    return bool;
}

int is_connected(char *chemin , char *user_find){
    
    FILE *fichier = fopen(chemin , "r");

    char *line = malloc(1000);

    char *user;
    //int bool;


    if (fichier != NULL)
    {

        while (fgets(line, 1000, fichier) != NULL)
        {
            
            sscanf(line , "%ms" , &user);
            if (strcmp(user , user_find) == 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

int set_user_connected(char *chemin , char *user){
    FILE *fichier = fopen(chemin , "a");
    
    if(fichier == NULL){
        return 0;
    }
    
    fprintf(fichier, "%s\n" , user);

    return 1;
}

int main(){
    int taille =  atoi(getenv("CONTENT_LENGTH"));
    char *data = malloc(taille + 1);
    
    char *id;
    char *pwd;
    
    //  char id[] = "b";
    //  char pwd[] = "b";
    
    if(fgets(data, taille + 1, stdin) != NULL){
        
    sscanf(data, "%*[^=]=%m[^&]&%*[^=]=%ms", &id , &pwd);
    /*
    status :    -succes
                    code = 0 => enter data
                    code = 1 => acces home
                -error
                1 - id inexistant
                2 - mdp incorrect
                3 - both
    */
    
    // id  inexistant pwd error
   
    if (verify("users_table.txt", id, crypt_pwd(pwd)) == 0)
    {
        printf("Location: http://www.webc.com/cgi-bin/authlog/login.cgi?status=error&code=3\n\n");
    }


    //user existant
    else{
        if(is_connected("connected.txt" , id) == 1){
            printf("Location: http://www.webc.com/cgi-bin/authlog/login.cgi?status=error&code=4\n\n");
        }
        else{
            if(set_user_connected("connected.txt" , id) == 1){
                printf("Location: http://www.webc.com/cgi-bin/authlog/connected.cgi?search=&page=1&id=%s\n\n",id);
            }
        }
    }
   
}
   

   return 0;
}