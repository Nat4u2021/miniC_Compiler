#include<stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include "Parser/semantic_analysis.h"
#include "Optimizer/Optimization.h"
#include "Codegen/RegisterAlloc.h"
using namespace std;


extern void yyparse();
extern int yylex_destroy();
extern FILE *yyin;
extern char* yytext;


astNode* root;


int main(int argc, char** argv){
	
	if (argc == 4){
		yyin = fopen(argv[1], "r");
	}
    else{
        printf("Usage: /compiler.out [name].c [name].ll [name].s\n");
        return 1;
    }

	//generate the AST
	yyparse();

	//check semantics
	bool valid = valid_semantic_analysis(root->prog.func);

	if(!valid) {
		freeNode(root);
		printf("FAILURE: Semantics Failed\n");
		return 1;
	}

	//generate LLVM_IR FILE
	string command =  "clang++ -S -emit-llvm -o " + string(argv[2]) + " " + string(argv[1]);   
    int result = system(command.c_str());
    if (result != 0) {
        std::cout << "Error: Failed to generate LLVM IR." << std::endl;
        return 1;
    }

    //Optimizing generated LLVM_IR
	LLVMModuleRef llvm_ir;
	llvm_ir = createLLVMModel(argv[2]);
	OptimizeLLVM(llvm_ir);

    LLVMPrintModuleToFile(llvm_ir, argv[2], NULL);

    printf(".ll file is the optmized llvm_ir\n");


    //assembly code generation
	codegen(llvm_ir, argv[3]);
    printf("Code Generation Successful");
    
	freeNode(root);

	// close
	if (yyin != stdin) {
		fclose(yyin);
		yylex_destroy();
	}
	
	return 0;
}