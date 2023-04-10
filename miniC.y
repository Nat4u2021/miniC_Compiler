%{
#include <stdio.h>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
%}

%token INT EXTERN COMND STR NUM OPERATOR LOGIC
%start PROGRAM

%%
DECLARATION : DECLARATION ';' | INT STR

EXT : EXTERN STR STR '(' INT ')' ';' | EXTERN INT STR'(' ')' ';' 

COMPARISON : STR OPERATOR STR 

EXPRESSION : NUM LOGIC NUM ';'| NUM LOGIC NUM LOGIC EXPRESSION ';'| STR LOGIC STR ';'| STR LOGIC STR LOGIC EXPRESSION ';' | STR LOGIC NUM ';'| STR LOGIC NUM LOGIC EXPRESSION ';'| NUM LOGIC STR ';'| NUM LOGIC STR LOGIC EXPRESSION ';'

ASSIGN : STR '=' EXPRESSION | STR '=' NUM ';'

STARTCOMND : COMND '(' COMPARISON ')' '{' | INT STR '(' DECLARATION ')' '{' | INT STR '(' ')' '{' | COMND 

LINE : STARTCOMND | ASSIGN | DECLARATION | EXT | '}'

PROGRAM : PROGRAM LINE | LINE
%%

int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}

	yyparse();

	if (yyin != stdin)
		fclose(yyin);

	yylex_destroy();
	
	return 0;
}


void yyerror(const char *){
	fprintf(stdout, "Syntax error %d\n", yylineno);
}
