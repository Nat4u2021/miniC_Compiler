%{
#include <stdio.h>
#include <math.h>
#include "y.tab.h"
%}

%option yylineno
letter	[a-zA-Z]
num     [0-9]
alphanum_us 	[a-zA-Z0-9_]

%%
"int"		{printf("%s", yytext); 
				 return INT;}
"extern"	 {printf("%s", yytext); 
				 return EXTERN;}
"while"	 {printf("%s", yytext); 
				 return COMND;}
"if"	 {printf("%s", yytext); 
				 return COMND;}
"else if"	 {printf("%s", yytext); 
				 return COMND;}
"else"	 {printf("%s", yytext); 
				 return COMND;}
"return" {printf("%s", yytext); 
				 return COMND;}

{letter}{alphanum_us}* {printf("%s", yytext); 
						return STR;}
{num}+ {printf("%s", yytext);
                    return NUM;}

"<"		{printf("%s", yytext); 
			 return OPERATOR;}
">"		{printf("%s", yytext); 
			 return OPERATOR;}
"=="		{printf("%s", yytext); 
			 return OPERATOR;}
">="		{printf("%s", yytext); 
			 return OPERATOR;}
"<="		{printf("%s", yytext); 
			 return OPERATOR;}

"+"		{printf("%s", yytext); 
			 return LOGIC;}
"-"		{printf("%s", yytext); 
			 return LOGIC;}
"/"		{printf("%s", yytext); 
			 return LOGIC;}
"*"		{printf("%s", yytext); 
			 return LOGIC;}

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

int main(){
	yylex();
    return 0;
}