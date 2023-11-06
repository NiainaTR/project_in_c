#include <stdio.h> 
#include "/home/tsanta/webC/authlog/header/util.h"

int main(){

    printf("Content-Type:text/html\n\n");

    display_fichier("./HTML/index.html");
    
    return 0;
}