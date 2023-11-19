#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "/home/tsanta/heberge/header/formulaire.h"
#include "/home/tsanta/heberge/header/virtualhost.h"



int main(){

    char *url = getenv("QUERY_STRING");
    
  
    char *servername = malloc(100);

    int nbr = 0;

    VirtualHost virtual = split_url(url , servername , &nbr);
   
    char* path = calloc(200,sizeof(char));
		
	sprintf(path,"/etc/apache2/sites-available/%s.conf", servername);

	FILE* file = fopen(path,"w");
	
    FILE *sites = fopen("sites" , "w");

    if(file == NULL && sites == NULL){
        printf("fichier non ouvert");
    }
    
    fprintf(file,"<VirtualHost *:80>\n\n");
    
	fprintf(file,"	Servername %s\n", servername);
    fprintf(sites,"	Servername %s\n", servername);

	fprintf(file,"	ServerAdmin webmaster@localhost\n");
	
	fprintf(file,"	DocumentRoot %s\n",virtual.document_root);
	
    fprintf(file,"  ScriptAlias %s %s\n", virtual.principale.scriptAlias , virtual.principale.directory);

    for(int i = 0 ; i < nbr ; i++){
        fprintf(file,"  ScriptAlias %s %s\n", virtual.secondaire[i].scriptAlias , virtual.secondaire[i].directory);
    }

	fprintf(file,"	<Directory %s>\n",virtual.principale.directory);
	fprintf(file,"		%s\n",virtual.principale.Options);
	fprintf(file,"		%s\n",virtual.principale.cgi_script);
	fprintf(file,"		%s\n",virtual.principale.AllowOveride);
	fprintf(file,"		Require all granted\n");
	fprintf(file,"	</Directory>\n\n");

    for(int i = 0 ; i < nbr ; i++){
        fprintf(file,"	<Directory %s>\n", virtual.secondaire[i].directory);
        fprintf(file,"		%s\n",virtual.secondaire[i].Options);
        fprintf(file,"		%s\n",virtual.secondaire[i].cgi_script);
        fprintf(file,"		%s\n",virtual.secondaire[i].AllowOveride);
        fprintf(file,"		Require all granted\n");
        fprintf(file,"	</Directory>\n\n");
    }
    
        
    fprintf(file,"ErrorLog ${APACHE_LOG_DIR}/%s.error.log\n" , servername);
    fprintf(file,"CustomLog ${APACHE_LOG_DIR}/%s.access.log combined\n" , servername);
    
    
    fprintf(file,"</VirtualHost>\n");
    
    printf("Location:http://www.configure.com\n\n");
       
    return 0;
}