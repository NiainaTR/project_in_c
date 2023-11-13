#include <stdio.h>
#include <string.h>
#include "css.c"

int main(){
	
	printf("Content-type: text/html\n\n");
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<TITLE>Sites d'hebergement</TITLE>\n");
	printf("<META charset=UTF-8>\n");
	printf("<STYLE>");
	print_css("./index.css");
	printf("</STYLE>");
	printf("</HEAD>\n");
	printf("<H1>Bienvenue sur notre site d'hebergement</H1>\n");
	
	printf("<BODY>\n");
	printf("<FORM action=\"./nouveau.cgi\" method=\"get\"/>\n");
		printf("<INPUT type=\"text\" name=\"servername\" placeholder=\"ServerName\" class=\"servername\" required/>");
		printf("<DIV class=\"box_dr\">");
			printf("<INPUT type=\"text\" name=\"documentroot\" placeholder=\"DocumentRoot\" required/>");
			/// Options
				
			printf("<DIV class=\"options\">");
				printf("<DIV><INPUT type=\"checkbox\" name=\"dr_indexes\"/><SPAN>Indexes</SPAN></DIV>");
				printf("<DIV><INPUT type=\"checkbox\" name=\"dr_followsymlinks\"/><SPAN>FollowSymLinks</SPAN></DIV>");
				printf("<INPUT type=\"checkbox\" class=\"dr_execCGI\"  name=\"dr_execCGI\"><SPAN>ExecCGI</SPAN>");
				/// AddHandler
					printf("<DIV class=\"addhandler\">");
						printf("<DIV><INPUT type=\"checkbox\" name=\"cgi\"/><SPAN>.cgi</SPAN></DIV>");
						printf("<DIV><INPUT type=\"checkbox\" name=\"pl\"/><SPAN>.pl</SPAN></DIV>");
						printf("<DIV><INPUT type=\"checkbox\" name=\"py\" /><SPAN>.py</SPAN></DIV>");
					printf("</DIV>");
						/// AllowOveride
			printf("<DIV class=\"allow\">");
				printf("<SPAN>AllowOveride :</SPAN><SELECT name=\"dr_allow\">");
					printf("<OPTION value=\"all\">All</OPTION>");
					printf("<OPTION value=\"none\">None</OPTION>");
				printf("</SELECT>");
			printf("</DIV>");
			printf("</DIV>");
		printf("</DIV>");
		
		printf("<DIV class=\"box_sa\">");
				printf("<INPUT type=\"text\" name=\"scriptalias\" placeholder=\"ScriptAlias\"/>");
				printf("<INPUT type=\"text\" name=\"directory\" placeholder=\"Directory\"/>");
				
				/// Options
				printf("<DIV class=\"options\">");
					printf("<DIV><INPUT type=\"checkbox\" name=\"sa_indexes\"/><SPAN>Indexes</SPAN></DIV>");
					printf("<DIV><INPUT type=\"checkbox\" name=\"sa_followsymlinks\"/><SPAN>FollowSymLinks</SPAN></DIV>");
					printf("<INPUT type=\"checkbox\" class=\"sa_execCGI\" name=\"sa_execCGI\" /><SPAN>ExecCGI</SPAN>");
						printf("<DIV class=\"addhandler\">");
							printf("<DIV><INPUT type=\"checkbox\" name=\"sa_cgi\"/><SPAN>.cgi</SPAN></DIV>");
							printf("<DIV><INPUT type=\"checkbox\" name=\"sa_pl\"/><SPAN>.pl</SPAN></DIV>");
							printf("<DIV><INPUT type=\"checkbox\" name=\"sa_py\" /><SPAN>.py</SPAN></DIV>");
						printf("</DIV>");
						/// AllowOveride
				printf("<DIV class=\"allow\">");
					printf("<SPAN>AllowOveride :</SPAN><SELECT name=\"sa_allow\">");
						printf("<OPTION value=\"all\">All</OPTION>");
						printf("<OPTION value=\"none\">None</OPTION>");
					printf("</SELECT>");
				printf("</DIV>");
				printf("</DIV>");
		printf("</DIV>");
		printf("<INPUT type=\"submit\" class=\"submit\" value=\"Create\"/>");
	printf("</FORM>\n");
	
	printf("</BODY>\n");
	printf("</HTML>\n");
	
	return 0;
}
