#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/home/tsanta/heberge/header/formulaire.h"
#include "/home/tsanta/heberge/header/virtualhost.h"


void dir_treatment(char* dir){
	char* tmp = calloc(100,sizeof(char));
	strcpy(tmp,dir);
	strcpy(dir,"");
	int j = 0;
	for(int i=0; tmp[i] != ' ' && tmp[i] != 0 ; i++, j++){
		if(tmp[i] == '%'){
			i+=2;
			dir[j] = '/';
		}
		else dir[j] = tmp[i];
	}
	dir[j] = 0;	
}

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


VirtualHost split_url(char* url , char *servername , int *nbr){

    
	VirtualHost virtual;

    //initialisation
    strcpy(virtual.servername,"");
    strcpy(virtual.document_root,"");
    strcpy(virtual.principale.directory,"");
    strcpy(virtual.principale.scriptAlias,"");
    
	
    for(int i = 0; i < 100 ; i++){
	    strcpy(virtual.secondaire[i].directory,"");
        strcpy(virtual.secondaire[i].scriptAlias,"");
    }
    
	
    char *str_directory_number = malloc(1000);
    char *str_tab_index = malloc(1000);
	

    sscanf(strstr(url,"directory_number="),"%*[^=]=%[^&]", str_directory_number);
    sscanf(strstr(url,"tab_index="),"%*[^=]=%[^&]", str_tab_index);
	

    int directory_number  = atoi(str_directory_number);
	
	*nbr = directory_number;

    str_tab_index[strlen(str_tab_index) - 1] = '\0';

    char **tab_index = split(str_tab_index , '+');

	
    for(int i = 0; i<3 ; i++){
		virtual.principale.script[i] = 0;
	}

	for(int i = 0 ; i < directory_number ; i++){
        for(int j = 0; j< 3 ; j++){
		    virtual.secondaire[i].script[j] = 0;
	    }
    }
	
	char *tmp = malloc(100);

	for(int i = 0 ; i < strlen(url) ; i++){
		tmp[i] = url[i];
		if(url[i] == '&') break;
	}	

	sscanf(tmp , "%*[^=]=%[^&]" , servername);

	sscanf(strstr(url,"DocumentRoot="),"%*[^=]=%[^&]",virtual.document_root);
	sscanf(strstr(url,"Directory1="),"%*[^=]=%[^&]",virtual.principale.directory);
    sscanf(strstr(url,"Scriptalias1="),"%*[^=]=%[^&]",virtual.principale.scriptAlias);
    
	
	dir_treatment(virtual.servername);
	dir_treatment(virtual.document_root);
	dir_treatment(virtual.principale.directory);
	dir_treatment(virtual.principale.scriptAlias);

	char *directory = malloc(100);
	char *scriptalias = malloc(100);

	for(int i = 0 ; i < directory_number ; i++){	
		sprintf(directory , "Directory%s=" , tab_index[i]);
		sprintf(scriptalias , "Scriptalias%s=" , tab_index[i]);
		
		sscanf(strstr(url,directory),"%*[^=]=%[^&]",virtual.secondaire[i].directory);
    	sscanf(strstr(url,scriptalias),"%*[^=]=%[^&]",virtual.secondaire[i].scriptAlias);
	
		strcpy(directory , "");
		strcpy(scriptalias , "");
	}


	for(int i = 0 ; i < directory_number ; i++){
		dir_treatment(virtual.secondaire[i].directory);	
		dir_treatment(virtual.secondaire[i].scriptAlias);	
	}
	

    //principale
    if(strstr(url,"index1=") || strstr(url,"follow1=") || strstr(url,"exec1=")) sprintf(virtual.principale.Options,"Options");
    else strcpy(virtual.principale.Options,"");
	if(strstr(url,"index1=")) strcat(virtual.principale.Options," Indexes");
	if(strstr(url,"follow1=")) strcat(virtual.principale.Options," FollowSymLinks");
	if(strstr(url,"exec1=")){
		strcat(virtual.principale.Options," ExecCGI");
		if(strstr(url,"cgi1=") || strstr(url,"pl1=") || strstr(url,"py1=")) sprintf(virtual.principale.cgi_script,"AddHandler cgi-script ");
		if(strstr(url,"cgi1=")) strcat(virtual.principale.cgi_script,".cgi ");
		if(strstr(url,"pl1=")) strcat(virtual.principale.cgi_script,".pl ");
		if(strstr(url,"py1=")) strcat(virtual.principale.cgi_script,".py ");
	}
	if(strstr(url,"allow1=all")) sprintf(virtual.principale.AllowOveride ,"AllowOveride All");
	else sprintf(virtual.principale.AllowOveride,"AllowOveride None");	
	
	//secondaire
	for(int i = 0 ; i < directory_number ; i++){
		char index[] = "index";
		char follow[] = "follow";
		char exec[] = "exec";
		char cgi[] = "cgi";
		char pl[] = "pl";
		char py[] = "py";
		char allow[] = "allow";
		
		strcat(index , tab_index[i]);
		strcat(follow , tab_index[i]);
		strcat(exec , tab_index[i]);
		strcat(cgi , tab_index[i]);
		strcat(pl , tab_index[i]);
		strcat(py , tab_index[i]);
		
		strcat(allow , tab_index[i]);
		strcat(allow , "=all");
		

		if(strstr(url, index) || strstr(url,follow) || strstr(url,exec)) sprintf(virtual.secondaire[i].Options,"Options");
		else strcpy(virtual.secondaire[i].Options,"");
		if(strstr(url, index)) strcat(virtual.secondaire[i].Options," Indexes");
		if(strstr(url,follow)) strcat(virtual.secondaire[i].Options," FollowSymLinks");
		if(strstr(url,exec)){
			strcat(virtual.secondaire[i].Options," ExecCGI");
			if(strstr(url,cgi) || strstr(url,pl) || strstr(url,py)) sprintf(virtual.secondaire[i].cgi_script,"AddHandler cgi-script ");
			if(strstr(url,cgi)) strcat(virtual.secondaire[i].cgi_script,".cgi ");
			if(strstr(url,pl)) strcat(virtual.secondaire[i].cgi_script,".pl ");
			if(strstr(url,exec)) strcat(virtual.secondaire[i].cgi_script,".py ");
		}
		if(strstr(url,allow)) sprintf(virtual.secondaire[i].AllowOveride,"AllowOveride All");
		else sprintf(virtual.secondaire[i].AllowOveride,"AllowOveride None");

		strcpy(index , "index");
		strcpy(follow , "follow");
		strcpy(exec , "exec");
		strcpy(cgi , "cgi");
		strcpy(pl , "pl");
		strcpy(py , "py");                                                                                                                                              
		strcpy(allow , "allow");
		

	}


	return virtual;
}
