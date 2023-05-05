#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>

#define prt(x) if(x) { printf("%s\n", x); }

LLVMModuleRef createLLVMModel(char * filename){
	char *err = 0;

	LLVMMemoryBufferRef ll_f = 0;
	LLVMModuleRef m = 0;

	LLVMCreateMemoryBufferWithContentsOfFile(filename, &ll_f, &err);

	if (err != NULL) { 
		prt(err);
		return NULL;
	}
	
	LLVMParseIRInContext(LLVMGetGlobalContext(), ll_f, &m, &err);

	if (err != NULL) {
		prt(err);
	}

	return m;
}

void walkBBInstructions(LLVMBasicBlockRef bb){
	for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction;
  				instruction = LLVMGetNextInstruction(instruction)) {
	
		// LLVMGetInstructionOpcode gives you LLVMOpcode that is a enum		
		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
        	

		if (LLVMIsACallInst(instruction)) {
		//if (op == LLVMCall) {
			LLVMDumpValue(instruction);		

			// Walking over all uses of an instruction
			LLVMUseRef y = LLVMGetFirstUse(instruction);
			if (y == NULL) printf("NULL\n");
			else printf("\n Exploring user instructions:\n");
			for (LLVMUseRef u = LLVMGetFirstUse(instruction);
					u;
					u = LLVMGetNextUse(u)){
				LLVMValueRef x = LLVMGetUser(u);
				LLVMDumpValue(x);
				printf("\n");

			}
		}
	}

}


void walkBasicblocks(LLVMValueRef function){
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
 			 basicBlock;
  			 basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		
		printf("In basic block\n");
		walkBBInstructions(basicBlock);
	
	}
}

void walkFunctions(LLVMModuleRef module){
	for (LLVMValueRef function =  LLVMGetFirstFunction(module); 
			function; 
			function = LLVMGetNextFunction(function)) {

		const char* funcName = LLVMGetValueName(function);	

		printf("Function Name: %s\n", funcName);

		walkBasicblocks(function);
 	}
}

void walkGlobalValues(LLVMModuleRef module){
	for (LLVMValueRef gVal =  LLVMGetFirstGlobal(module);
                        gVal;
                        gVal = LLVMGetNextGlobal(gVal)) {

                const char* gName = LLVMGetValueName(gVal);
                printf("Global variable name: %s\n", gName);
        }
}

int main(int argc, char** argv)
{
	LLVMModuleRef m;

	if (argc == 2){
		m = createLLVMModel(argv[1]);
	}
	else{
		m = NULL;
		return 1;
	}

	if (m != NULL){
		//LLVMDumpModule(m);
		walkFunctions(m);
	}
	else {
	    printf("m is NULL\n");
	}
	
	return 0;
}
