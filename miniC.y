%{
#include <stdio.h>
#include "ast.h"
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
%}

%union{
	int ival;
	char* sname;
	astNode *nptr;
	vector<astNode*> *svec_ptr;
}

%token INT EXTERN IF WHILE ELSE RETURN VOID
%token <ival> NUM 
%token <sname> STR READ PRINT
%type <nptr> expression program declaration definition1 definition2 func_def if_block while_block else_block return_statement eq_cond lt_cond gt_cond gteq_cond lteq_cond neq_cond func_call comparison assign stmt comnd_block add subtract multiply divide term
%type <svec_ptr> stmts 
%start program

%%
declaration : INT STR ';' {$$ = createDecl($2);}

definition1 : EXTERN VOID PRINT '(' INT ')' ';' {$$ = createExtern($3);} 

definition2 : EXTERN INT READ '(' ')' ';' {$$ = createExtern($3);} 

return_statement : RETURN term ';' {$$ = createRet($2);} | RETURN expression {$$ = createRet($2);}

term: NUM {$$ = createCnst($1);} | STR  {$$ = createVar($1);}

eq_cond : term '=''=' term {$$ = createRExpr($1, $4, eq);}

lt_cond : term '<' term  {$$ = createRExpr($1, $3, lt);}

gt_cond : term '>' term  {$$ = createRExpr($1, $3, gt);}

gteq_cond : term '>''=' term {$$ = createRExpr($1, $4, ge);}

lteq_cond : term '<''=' term {$$ = createRExpr($1, $4, le);}

neq_cond : term '!''=' term {$$ = createRExpr($1, $4, neq);}

comparison : eq_cond {$$ = $1;} | lt_cond {$$ = $1;} | lteq_cond {$$ = $1;} | gteq_cond {$$ = $1;}| gt_cond {$$ = $1;} | neq_cond {$$ = $1;}

add : term '+' term ';' {$$ = createBExpr($1, $3, add);}

subtract : term '-' term ';'  {$$ = createBExpr($1, $3, sub);}

multiply : term '*' term ';'  {$$ = createBExpr($1, $3, mul);}

divide : term '/' term ';'    {$$ = createBExpr($1, $3, divide);}

expression : add {$$ = $1;}| subtract {$$ = $1;} | multiply {$$ = $1;}  | divide {$$ = $1;}

assign : STR '=' expression {astNode* tnptr = createVar($1); $$ = createAsgn(tnptr, $3);}
		| STR '=' NUM ';'  {astNode* tnptr = createVar($1); astNode* tnptr2 = createCnst($3); $$ = createAsgn(tnptr, tnptr2);}
		| STR '=' STR ';'  {astNode* tnptr = createVar($1); astNode* tnptr2 = createVar($3); $$ = createAsgn(tnptr, tnptr2);}
		| STR '=' func_call {astNode* tnptr = createVar($1); $$ = createAsgn(tnptr, $3);}

func_call :  PRINT '(' STR ')' ';' {astNode* tnptr = createVar($3); $$ = createCall($1, tnptr);} 
			| PRINT '(' NUM ')' ';' {astNode* tnptr = createCnst($3); $$ = createCall($1, tnptr);} 
			| READ '('')' ';' {$$ = createCall($1);} 

if_block : IF '(' comparison ')' stmt {$$ = createIf($3, $5);} | IF '(' comparison ')' stmt else_block {$$ = createIf($3, $5, $6);}

while_block : WHILE '(' comparison ')' stmt {$$ = createWhile($3, $5);}

else_block : ELSE stmt {$$ = $2;}

stmt : func_call {$$ = $1;} | return_statement {$$ = $1;} | assign {$$ = $1;} | declaration  {$$ = $1;}| if_block  {$$ = $1;} | while_block  {$$ = $1;} | comnd_block {$$ = $1;}

stmts : stmts stmt {$$ = $1; $$->push_back($2);} | stmt {$$ = new vector<astNode*> (); $$->push_back($1);}

comnd_block : '{' stmts '}' {$$ = createBlock($2); printNode($$);}

func_def : INT STR '(' INT STR ')' comnd_block {astNode* tnptr = createVar($5); $$ = createFunc($2, tnptr , $7);}

program : definition1 definition2 func_def {$$ = createProg($1, $2, $3); printNode($$);}
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
