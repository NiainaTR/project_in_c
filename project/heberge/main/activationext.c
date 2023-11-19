#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int activate(char *site){
    char *cmd = malloc(200);

    sprintf(cmd , "a2ensite %s" , site);
    
    popen(cmd , "r");
    
    system("systemctl reload apache2");
    
}

int desactivate(char *site){
    char *cmd = malloc(200);
    
    sprintf(cmd , "a2dissite %s" , site);
    
    popen(cmd , "r");
    
    system("systemctl reload apache2");
    
}


int main(){
    char *url = getenv("QUERY_STRING");

    char *search = NULL;
    int is_premier = 0;
    int page = 1;

    char *site = malloc(200);
    int a = 0;
    
    sscanf(url , "is=%d&search=%s&page=%d&site=%[^&]&a=%d" , &is_premier , search , &page ,  site , &a);
    
    sscanf(strstr(url , "site=") , "site=%[^&]" , site);
    sscanf(strstr(url , "a=") , "a=%d" , &a);
    
    a == 0 ? desactivate(site) : activate(site);

    is_premier == 1 ? printf("Location:http://www.configure.com/cgi/activation.cgi?is=1&search=&page=%d\n\n" , page):printf("Location:http://www.configure.com/cgi/activation.cgi?is=0&search=%s&page=%d\n\n" , search , page);
    
    return 0;
}