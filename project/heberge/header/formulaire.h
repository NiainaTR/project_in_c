#ifndef FORMULAIRE_H

#define FORMULAIRE_H

#include <stdbool.h>

typedef struct Directive{
	char directory[100];
	char scriptAlias[100];
	char Options[100];
	bool indexes;
	bool followsymlinks;
	bool execCGI;
	char cgi_script[100];
	bool script[3];
	char AllowOveride[100];
	bool allow;
}Directive;


typedef struct VirtualHost{
	char servername[100];       
	char document_root[100];
	Directive principale;
	Directive secondaire[100];
}VirtualHost;




#endif

