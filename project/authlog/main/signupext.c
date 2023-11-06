#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int is_valide(char *str){
    int val = 1;

    if(strcmp(str , "")==0){
        val = 0;
        return val;
    }

    if (*str >= '0' && *str <= '9')
    {
        val = 0;
        return val;
    }
    
      while (*str) {
        if (!((*str >= 'a' && *str <= 'z') ||
              (*str >= 'A' && *str <= 'Z') ||
              (*str >= '0' && *str <= '9'))){
                val = 0;
                return val; // Caractère non valide
        }
        str++;
    }

    return val;
}


/*
return    1 si mdp moins de 8 caractères
          2 si mdp ne contient pas de majuscule
          3 si mdp ne contient pas de caractère speciaux
          4 si mdp ne contient pas de chiffre
          5 si all
*/
char *crypt_pwd(char *pwd){
    char *mdp_crypt = malloc(1000);
    char *cmd = malloc(1000);

    sprintf(cmd, "echo %s |sha256sum", pwd);

    FILE *fichier = popen(cmd, "r");

    fgets(mdp_crypt, 1000, fichier);

    return mdp_crypt;
}

int password_match(char *pwd , char *pwd2){

    if(strlen(pwd) <= 8){
        return 1;
    }  
    
    //count caractère maj , speciaux , nombre
    int maj = 0;
    int spec = 0;
    int nbr = 0;

    while (*pwd)
    {   
        if(*pwd >= 'A' && *pwd <= 'Z'){
            maj++;
        }

        if (!((*pwd >= 'a' && *pwd <= 'z') ||
              (*pwd >= 'A' && *pwd <= 'Z') ||
              (*pwd >= '0' && *pwd <= '9'))){
             spec++;
        }

        if((*pwd >= '0' && *pwd <= '9')) nbr++;
        pwd++;
    }   

    if((maj == 0 || spec == 0 || nbr == 0) && (strcmp(pwd , pwd2) == 0)){
        return 3;
    }


    if(maj == 0 || spec == 0 || nbr == 0){
        return 1;
    }

    if(strcmp(pwd , pwd2) == 0){
       return 2;
    }
    
    return 0;
}


int main(){

  
    int taille =  atoi(getenv("CONTENT_LENGTH"));

    char *data = malloc(taille + 1);

    
    if(fgets(data, taille + 1, stdin) != NULL){
   
       
        /*
        char id[] = "a";
        char pwd1[] = "A12azeze!";
        char pwd2[] = "A12azeze!";
        

          */
    char *id;
    char *pwd1;
    char *pwd2;

    sscanf(data, "%*[^=]=%m[^&]&%*[^=]=%m[^&]&%*[^=]=%ms", &id, &pwd1, &pwd2);
    /*
    // error id et mdp error
    if (is_valide(id) == 0 && password_match(pwd1, pwd2) != 0)
    {
        printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=1\n\n");
    }
    //error id et mdp ok
    else if(is_valide(id) == 0 && password_match(pwd1 , pwd2) == 0){
        printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=2\n\n");

    }
    //id ok et mdp error
    else if(is_valide(id) != 0 && password_match(pwd1 , pwd2) != 0){
        //mdp invalid
        if(password_match(pwd1 , pwd2) == 1){
            printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=31\n\n");
        }
        //pwd1 != pwd2
        else if(password_match(pwd1 , pwd2) == 2){
            printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=32\n\n");

        }
        //both
        else{
            printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=33\n\n");

        }

    }
    */
    if(is_valide(id) == 0){
            printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=2\n\n");
    }
    else if(strcmp(pwd1 , pwd2) != 0){
        printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=error&code=32\n\n");
    }
    else{
        FILE *fichier = fopen("users_table.txt", "a");
        if (fichier != NULL)
        {
            fprintf(fichier, "%s;%s", id, crypt_pwd(pwd1));
            printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=succes&code=1\n\n");
        }
        fclose(fichier);
    }
    
     }
      return 0;
}

    