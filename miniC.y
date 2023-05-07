%{
#include <stdio.h>
#include "ast.h"
#include <stack>
#include <iostream>
#include <cstring>
void yyerror(const char *);
extern int yylex();
extern int yylex_destroy();
extern FILE *yyin;
extern int yylineno;
extern char* yytext;
astNode *root;
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
%type <nptr> expression program declaration definition1 definition2 func_def if_block while_block else_block return_statement eq_cond lt_cond gt_cond gteq_cond lteq_cond neq_cond func_call comparison assign stmt comnd_block add subtract multiply divide unary term
%type <svec_ptr> stmts 
%start program

%%
declaration : INT STR ';' {$$ = createDecl($2); free($2);}

definition1 : EXTERN VOID PRINT '(' INT ')' ';' {$$ = createExtern($3); free($3);} 

definition2 : EXTERN INT READ '(' ')' ';' {$$ = createExtern($3); free($3);} 

return_statement : RETURN term ';' {$$ = createRet($2);} | RETURN expression {$$ = createRet($2);}

term: NUM {$$ = createCnst($1);} | STR  {$$ = createVar($1); free($1);}

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

unary: '-' term ';'  {$$ = createUExpr($2, sub);}

expression : add {$$ = $1;}| subtract {$$ = $1;} | multiply {$$ = $1;}  | divide {$$ = $1;} | unary {$$ = $1;} 

assign : STR '=' expression {astNode* tnptr = createVar($1); free($1); $$ = createAsgn(tnptr, $3);}
		| STR '=' NUM ';'  {astNode* tnptr = createVar($1); free($1); astNode* tnptr2 = createCnst($3); $$ = createAsgn(tnptr, tnptr2);}
		| STR '=' STR ';'  {astNode* tnptr = createVar($1); free($1); astNode* tnptr2 = createVar($3); free($3); $$ = createAsgn(tnptr, tnptr2);}
		| STR '=' func_call {astNode* tnptr = createVar($1); free($1); $$ = createAsgn(tnptr, $3);}

func_call :  PRINT '(' STR ')' ';' {astNode* tnptr = createVar($3); free($3); $$ = createCall($1, tnptr); free($1);} 
			| PRINT '(' NUM ')' ';' {astNode* tnptr = createCnst($3); $$ = createCall($1, tnptr); free($1);} 
			| READ '('')' ';' {$$ = createCall($1); free($1);} 

if_block : IF '(' comparison ')' stmt {$$ = createIf($3, $5);} | IF '(' comparison ')' stmt else_block {$$ = createIf($3, $5, $6);}

while_block : WHILE '(' comparison ')' stmt {$$ = createWhile($3, $5);}

else_block : ELSE stmt {$$ = $2;}

stmt : func_call {$$ = $1;} | return_statement {$$ = $1;} | assign {$$ = $1;} | declaration  {$$ = $1;}| if_block  {$$ = $1;} | while_block  {$$ = $1;} | comnd_block {$$ = $1;}

stmts : stmts stmt {$$ = $1; $$->push_back($2);} | stmt {$$ = new vector<astNode*>(); $$->push_back($1);}

comnd_block : '{' stmts '}' {$$ = createBlock($2);}

func_def : INT STR '(' INT STR ')' comnd_block  {astNode* tnptr = createVar($5); free($5); $$ = createFunc($2, tnptr , $7); free($2);} |  INT STR '('')' comnd_block {$$ = createFunc($2, NULL, $5); free($2);} 

program : definition1 definition2 func_def {$$ = createProg($1, $2, $3); root = $$;}
%%

bool check(vector<vector<char*>*> stackOfVectors, char* searchString) {
    for (vector<char*>* topVector: stackOfVectors) { // loop until stack is empty
        for (char* s : *topVector) { // loop through the elements of the top vector
            if (strcmp(s, searchString) == 0) { // if the search string is found in the top vector, return true
                return true;
            }
        }
    }
    return false; // if the search string was not found in any vector, return false
}

void helper(vector<astNode*> nodes, vector<vector<char*>*> temp){
	while (!nodes.empty()){
		astNode* currnode = nodes.front();
		nodes.erase(nodes.begin());
	
		if (currnode->type == ast_stmt){
			if (currnode->stmt.type == ast_block){
				vector<char*> *currvector = new vector<char*>();
				temp.push_back(currvector);
				helper(*currnode->stmt.block.stmt_list, temp);
				temp.pop_back();
				delete(currvector);
			}
			else if (currnode->stmt.type == ast_decl){
				vector<char*> *currvector;
				currvector = temp.back();
				currvector->push_back(currnode->stmt.decl.name);
			}
			else if (currnode->stmt.type == ast_call){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.call.param);
				helper(newnodes, temp);	
			}
			else if (currnode->stmt.type == ast_ret){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.ret.expr);
				helper(newnodes, temp);	
						
			}
			else if (currnode->stmt.type == ast_while){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.whilen.cond);
				newnodes.push_back(currnode->stmt.whilen.body);
				helper(newnodes, temp);		
					
			}
			else if (currnode->stmt.type == ast_if){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.ifn.cond);
				newnodes.push_back(currnode->stmt.ifn.if_body);
				if (currnode->stmt.ifn.else_body != NULL) newnodes.push_back(currnode->stmt.ifn.else_body);
				helper(newnodes, temp);	
							
			}
			else if (currnode->stmt.type == ast_asgn){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.asgn.lhs);
				newnodes.push_back(currnode->stmt.asgn.rhs);
				helper(newnodes, temp);		
					
			}						
		}
		else if (currnode->type == ast_var){
			bool declared = check(temp, currnode->var.name);
			if (!declared){
				printf("ERROR: variable %s has not been declared\n", currnode->var.name);
			}
		}
		else if (currnode->type == ast_rexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->rexpr.lhs);
			newnodes.push_back(currnode->rexpr.rhs);
			helper(newnodes, temp);
			
		}
		else if (currnode->type == ast_bexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->bexpr.lhs);
			newnodes.push_back(currnode->bexpr.rhs);
			helper(newnodes, temp);
			
		}
		else if (currnode->type == ast_uexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->uexpr.expr);
			helper(newnodes, temp);
			
		}
	}

	return;
}

void semantic_analysis(astNode *root){

	vector<vector<char*>*> symbol_table_stack;
	vector<char*> *currvector = new vector<char*> ();
	symbol_table_stack.push_back(currvector);

	if (root->func.param != NULL){
		currvector->push_back(root->func.param->var.name);
	}

	root = root->func.body;
	vector<astNode*> nodes = *root->stmt.block.stmt_list;

	helper(nodes, symbol_table_stack);

	symbol_table_stack.pop_back();
	delete(currvector); 
}

void optimizer_subexp_eli(char* filename){

	LLVMModuleRef module = createLLVMModel(filename);

}

void walkBBInstructions_subexp_eli(LLVMBasicBlockRef bb){
	
}

int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}

	yyparse();


	semantic_analysis(root->prog.func);

	freeProg(root);

	if (yyin != stdin)
		fclose(yyin);

	yylex_destroy();
	
	return 0;
}

void yyerror(const char *){
	fprintf(stdout, "Syntax error %d\n", yylineno);
}
