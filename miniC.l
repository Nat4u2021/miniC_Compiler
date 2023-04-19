%{
#include "ast.h"
#include <stdio.h>
#include <math.h>
#include "y.tab.h"
#include <string.h>
%}

%option yylineno
letter	[a-zA-Z]
num     [0-9]
alphanum_us 	[a-zA-Z0-9_]

%%
"int"		{yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return INT;}
"extern"	{yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return EXTERN;}
"while"	 {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return WHILE;}
"if"	 {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return IF;}
"else"	 {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return ELSE;}
"return" {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return RETURN;}
"read" {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return READ;}
"print" {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return PRINT;}
"void" {yylval.sname = strdup(yytext); printf("%s", yytext); 
				 return VOID;}

{letter}{alphanum_us}* {yylval.sname = strdup(yytext); printf("%s", yytext); 
						return STR;}
{num}+ {yylval.ival= atoi(yytext); printf("%s", yytext);
                    return NUM;}

"<"		{printf("%s", yytext); 
			 return yytext[0];}
">"		{printf("%s", yytext); 
			 return yytext[0];}
"=="		{printf("%s", yytext); 
			 return yytext[0];}
">="		{printf("%s", yytext); 
			 return yytext[0];}
"<="		{printf("%s", yytext); 
			 return yytext[0];}
"!="		{printf("%s", yytext); 
			 return yytext[0];}
"+"		{printf("%s", yytext); 
			 return yytext[0];}
"-"		{printf("%s", yytext); 
			 return yytext[0];}
"/"		{printf("%s", yytext); 
			 return yytext[0];}
"*"		{printf("%s", yytext); 
			 return yytext[0];}

"{" 	{printf("%s", yytext); 
			 return yytext[0];}
"}"		{printf("%s", yytext); 
			 return yytext[0];}
";"		{printf("%s", yytext); 
			 return yytext[0];}  
"="		{printf("%s", yytext); 
			 return yytext[0];}
"("		{printf("%s", yytext); 
			 return yytext[0];}
")"		{printf("%s", yytext); 
             return yytext[0];}

%%

int yywrap(){
	return 1;
}
