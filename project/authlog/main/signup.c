#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "/home/tsanta/webC/authlog/header/util.h"




int main(){

    char *data = getenv("QUERY_STRING");

    char *status;
    int code = 0;

    sscanf(data, "%*[^=]=%m[^&]&%*[^=]=%d", &status , &code);

    /*
    status :    -succes 
                    code = 0 => enter data
                    code = 1 => compte creer avec succès
                -error
                    1 - id invalide et mdp invalide
                    2 - id invalide et mdp ok
                    3 - mdp invalide
                        code = 31 =>   mdp invalide
                        code = 32 =>  pwd1 != pwd2
                        code = 33 =>  both
    */
    
    printf("Content-Type:text/html\n\n");

    display_fichier("./HTML/head_signup.html");
    
    
    //error
    if(strcmp(status , "error") == 0){
        if(code == 1){
            display_fichier("./HTML/SIGNUP/error_1.html");
        }
        else if(code == 2){
             display_fichier("./HTML/SIGNUP/error_2.html");
        }
        else{
             switch (code)
                {
                    case 31:
                         display_fichier("./HTML/SIGNUP/error_31.html");
                    break;
                    case 32:
                         display_fichier("./HTML/SIGNUP/error_32.html");
                    break;
                    default:
                         display_fichier("./HTML/SIGNUP/error_33.html");
                    break;
                }
        }
    }

    //succes
    else{
        if(code == 1){
            display_fichier("./HTML/SIGNUP/succes.html");
        }
        else{
            display_fichier("./HTML/SIGNUP/signup.html");
        }
    }
    


    return 0;
}