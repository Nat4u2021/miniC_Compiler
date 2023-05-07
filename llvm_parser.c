#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>

using std::unordered_map;

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

// Helper function to compare two instructions
bool compareInstructions(LLVMValueRef a, LLVMValueRef b, unordered_map<LLVMValueRef, int> instructions, unordered_map<int, LLVMValueRef> stores) {
    // Check that the instructions have the same opcode
    if (LLVMGetInstructionOpcode(a) != LLVMGetInstructionOpcode(b)) return false;
    

    // Check that the instructions have the same number of operands
    if (LLVMGetNumOperands(a) != LLVMGetNumOperands(b)) {
        return false;
    }

    // Check that all the operands of A are present in B (regardless of position)
    unordered_map<LLVMValueRef, bool> operandMap;
    for (unsigned i = 0; i < LLVMGetNumOperands(b); ++i) {
        LLVMValueRef operand = LLVMGetOperand(b, i);
        operandMap[operand] = true;
    }
    for (unsigned i = 0; i < LLVMGetNumOperands(a); ++i) {
        LLVMValueRef operand = LLVMGetOperand(a, i);
        if (!operandMap[operand]) {
            return false;
        }
    }

	if (LLVMGetInstructionOpcode(a) == LLVMLoad){
		int pos1 = instructions.at(a);
		int pos2 = instructions.at(b);

		for (auto i = stores.begin(); i != stores.end(); ++i){
			LLVMValueRef store = stores.at(i);
			if ((pos1 < i < pos2) && (operandMap[LLVMGetOperand(store, 1)])){
				return false;
			}
		}
	}
    return true;
}

bool hasNoUses(LLVMValueRef instruction) {
    for (LLVMValueRef user = LLVMGetFirstUse(instruction); user != NULL; user = LLVMGetNextUse(user)) {
        LLVMValueRef userValue = LLVMGetUser(user);
        if (LLVMIsAInstruction(userValue)) {
            return false; // Found an instruction user
        }
    }
    return true; // No instruction users found
}

// Common subexpression function
void walkBBInstructions_subexp_elimi(LLVMBasicBlockRef bb) {
    unordered_map<LLVMValueRef, int> myMap;
	unordered_map<int, LLVMValue> stores;
    LLVMValueRef lastInstruction = NULL;
	int i = 0;

    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction;
            instruction = LLVMGetNextInstruction(instruction)) {
        // Check if the instruction matches a previous one
        for (auto it = myMap.begin(); it != myMap.end(); ++it) {
            if (compareInstructions(instruction, it->first, myMap, stores)) {
                LLVMReplaceAllUsesWith(instruction, it->first);
                lastInstruction = instruction;
                break;
            }
        }
		i = i + 1;
        if (lastInstruction != instruction) {
            myMap[instruction] = i;
			if (LLVMGetInstructionOpcode(instruction) == LLVMStore) stores[i] = instruction;
            lastInstruction = instruction;
        }
    }
}

void walkBBInstructions_constant_folding(LLVMBasicBlockRef bb) {
	//looping through instructions in block
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {

		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
		LLVMValueRef operand1 = LLVMGetOperand(instruction, 0);
		LLVMValueRef operand2 = LLVMGetOperand(instruction, 1);

		//DO I NEED TO CHECK FOR DIVISION
		if (opcode >= LLVMAdd && opcode <= LLVMFDiv){
			if (LLVMIsAConstantInt(operand1) && LLVMIsAConstantInt(operand2)){
				LLVMValeuRef result;
				if (op == LLVMAdd) result = LLVMConstAdd(operand1, operand2);
				else if (op == LLVMSub) result = LLVMConstSub(operand1, operand2);
				else if (op == LLVMMul) result = LLVMConstMul(operand1, operand2);
				LLVMReplaceAllUsesWith(instruction, result);
			}
		}
    }
}

void walkBBInstructions_deadcode_elimiation(LLVMBasicBlockRef bb) {
	//looping through instructions in block
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		if (hasNoUses(instruction)){
			LLVMInstructionEraseFromParent(instruction);
		}
    }
}

void walkBasicblocks(LLVMValueRef function){
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
 			 basicBlock;
  			 basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		
		printf("\nIn basic block\n");
		walkBBInstructions(basicBlock);
	
	}
}

void walkFunctions(LLVMModuleRef module){
	for (LLVMValueRef function =  LLVMGetFirstFunction(module); 
			function; 
			function = LLVMGetNextFunction(function)) {

		const char* funcName = LLVMGetValueName(function);	

		printf("\nFunction Name: %s\n", funcName);

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
