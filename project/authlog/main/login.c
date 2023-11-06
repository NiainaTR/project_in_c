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
                    code = 1 => acces home
                -error
                    1 - id inexistant
                    2 - mdp incorrect
                    3 - both

    */

    printf("Content-Type:text/html\n\n");
    
    display_fichier("./HTML/head_login.html");
    
    
    //error
    if(strcmp(status , "error") == 0){
        if(code == 1){
            display_fichier("./HTML/LOGIN/error_1.html");
        }
        else if(code == 2){
             display_fichier("./HTML/LOGIN/error_2.html");
        }
        else if(code == 3){
            display_fichier("./HTML/LOGIN/error_3.html");
        }
        else{
            display_fichier("./HTML/LOGIN/error_4.html");    
        }
    }
    
    //succes
    else{
        if(code == 1){
            printf("Location: http://www.webc.com/cgi-bin/authlog/signup.cgi?status=succes&code=1");
            printf("Content-Type:text/html\n\n");    
        }
        else{
            display_fichier("./HTML/LOGIN/login.html");
        }
    }



    return 0;
}