#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "semantic_analysis.h"
using namespace std;


extern void yyparse();
extern int yylex_destroy();
extern FILE *yyin;
extern char* yytext;


astNode* root; // root of the AST


int main(int argc, char** argv){
	if (argc == 2){
		yyin = fopen(argv[1], "r");
	}


    // generate the AST
	yyparse();

    // check semantics of the program
    bool validSemantics = valid_semantic_analysis(root->prog.func); 

    freeNode(root);

    // close
	if (yyin != stdin)
		fclose(yyin);
	yylex_destroy();
	
    // return if failure
    if(!validSemantics) return 1;

    printf("Semantics valid");

	return 0;
}