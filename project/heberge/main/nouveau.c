#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "formulaire.h"


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

VirtualHost split_url(char* url){

	VirtualHost virtual;
		
	strcpy(virtual.servername,"");
	strcpy(virtual.document_root,"");
	strcpy(virtual.script_alias,"");
	strcpy(virtual.directory,"");
	
	for(int i = 0; i<3 ; i++){
		virtual.principale.script[i] = 0;
		virtual.secondaire.script[i] = 0;
	}
	
	sscanf(strstr(url,"documentroot="),"%*[^=]=%[^&]",virtual.document_root);
	sscanf(strstr(url,"servername="),"%*[^=]=%[^&]",virtual.servername);
	sscanf(strstr(url,"scriptalias="),"%*[^=]=%[^&]",virtual.script_alias);
	sscanf(strstr(url,"directory="),"%*[^=]=%[^&]",virtual.directory);
		
	dir_treatment(virtual.document_root);
	dir_treatment(virtual.servername);
	dir_treatment(virtual.script_alias);
	dir_treatment(virtual.directory);
	
	/// Principale
	if(strstr(url,"dr_indexes=") || strstr(url,"dr_execCGI=") || (strstr(url,"dr_followsymlinks="))) sprintf(virtual.principale.Options,"Options");
	else strcpy(virtual.principale.Options,"");
	if(strstr(url,"dr_indexes=")) strcat(virtual.principale.Options," Indexes");
	if(strstr(url,"dr_followsymlinks=")) strcat(virtual.principale.Options," FollowSymLinks");
	strcpy(virtual.principale.cgi_script,"");
	if(strstr(url,"dr_execCGI=")){
		strcat(virtual.principale.Options," ExecCGI");
		if(strstr(url,"cgi=") || strstr(url,"pl=") || strstr(url,"py=")) sprintf(virtual.principale.cgi_script,"AddHandler cgi-script ");
		if(strstr(url,"cgi=")) strcat(virtual.principale.cgi_script,".cgi ");
		if(strstr(url,"pl=")) strcat(virtual.principale.cgi_script,".pl ");
		if(strstr(url,"py=")) strcat(virtual.principale.cgi_script,".py ");
	}
	if(strstr(url,"dr_allow=all")) sprintf(virtual.principale.AllowOveride,"AllowOveride All");
	else sprintf(virtual.principale.AllowOveride,"AllowOveride None");	
	
	/// Secondaire
	if(strstr(url,"sa_indexes=") || strstr(url,"sa_execCGI=") || (strstr(url,"sa_followsymlinks="))) sprintf(virtual.secondaire.Options,"Options");
	else strcpy(virtual.secondaire.Options,"");
	if(strcmp(virtual.principale.Options,"") == 0){
		if(strstr(url,"sa_indexes=")) strcat(virtual.secondaire.Options," Indexes");
		if(strstr(url,"sa_followsymlinks=")) strcat(virtual.secondaire.Options," FollowSymLinks");
		strcpy(virtual.secondaire.cgi_script,"");
		if(strstr(url,"sa_execCGI=")){
			strcat(virtual.secondaire.Options," ExecCGI");
			if(strstr(url,"cgi=") || strstr(url,"pl=") || strstr(url,"py=")) sprintf(virtual.secondaire.cgi_script,"AddHandler cgi-script ");
			if(strstr(url,"cgi=")) strcat(virtual.secondaire.cgi_script,".cgi ");
			if(strstr(url,"pl=")) strcat(virtual.secondaire.cgi_script,".pl ");
			if(strstr(url,"py=")) strcat(virtual.secondaire.cgi_script,".py");
		}
	}
	else{
		if(strstr(url,"sa_indexes=")) strcat(virtual.secondaire.Options," +Indexes");
		else strcat(virtual.secondaire.Options," -Indexes");
		if(strstr(url,"sa_followsymlinks=")) strcat(virtual.secondaire.Options," +FollowSymLinks");
		else strcat(virtual.secondaire.Options," -FollowSymLinks");
		strcpy(virtual.secondaire.cgi_script,"");
		if(strstr(url,"sa_execCGI=")){
			strcat(virtual.secondaire.Options," +ExecCGI");
			if(strstr(url,"sa_cgi=") || strstr(url,"sa_pl=") || strstr(url,"sa_py=")) sprintf(virtual.secondaire.cgi_script,"AddHandler cgi-script ");
			if(strstr(url,"cgi=")) strcat(virtual.secondaire.cgi_script,".cgi ");
			if(strstr(url,"pl=")) strcat(virtual.secondaire.cgi_script,".pl ");
			if(strstr(url,"py=")) strcat(virtual.secondaire.cgi_script,".py");
		}
		else strcat(virtual.secondaire.Options," -ExecCGI");
	}
	if(strstr(url,"sa_allow=all")) sprintf(virtual.secondaire.AllowOveride,"AllowOveride All");
	else sprintf(virtual.secondaire.AllowOveride,"AllowOveride None");
	
	return virtual;
}

int main(){
	
	char* url = calloc(500,sizeof(char));
	
	url = getenv("QUERY_STRING");
	
	printf("Content-type: text/html\n\n");
	
	VirtualHost virtual = split_url(url);
	
	char* path = calloc(200,sizeof(char));
		
	sprintf(path,"/etc/apache2/sites-available/%s.conf",virtual.servername);
	
	FILE* file = fopen(path,"w");
	fprintf(file,"<VirtualHost *:80>\n\n");
	
	fprintf(file,"	Servername %s\n",virtual.servername);
	fprintf(file,"	ServerAdmin webmaster@localhost\n");
	
	fprintf(file,"	DocumentRoot %s\n",virtual.document_root);
	
	fprintf(file,"	<Directory %s>\n",virtual.document_root);
	fprintf(file,"		%s\n",virtual.principale.Options);
	fprintf(file,"		%s\n",virtual.principale.cgi_script);
	fprintf(file,"		%s\n",virtual.principale.AllowOveride);
	fprintf(file,"		Require all granted\n");
	fprintf(file,"	</Directory>\n\n");
	
	if(strcmp(virtual.directory,"") != 0){
		if(strcmp(virtual.script_alias,"") != 0){
			fprintf(file,"	ScriptAlias %s %s\n",virtual.script_alias,virtual.directory);
		}
		fprintf(file,"	<Directory %s>\n",virtual.directory);
		fprintf(file,"		%s\n",virtual.secondaire.Options);
		fprintf(file,"		%s\n",virtual.secondaire.cgi_script);
		fprintf(file,"		%s\n",virtual.secondaire.AllowOveride);
		fprintf(file,"		Require all granted\n");
		fprintf(file,"	</Directory>\n\n");
	}
	
	fprintf(file,"	CustomLog /etc/apache2/access/%s.log\n",virtual.servername);
	
	fprintf(file,"\n</VirtualHost>");
	fclose(file);

	
	//~ free(url);
	
	free(path);
	
	return 0;
}
