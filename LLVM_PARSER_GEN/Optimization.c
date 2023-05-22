#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unordered_map>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include "Optimization.h"

using namespace std;

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
		int pos1 = instructions.at(b);

		for (auto i = stores.begin(); i != stores.end(); ++i){
			int j = i->first; 
			LLVMValueRef store = stores.at(j);
			if ((pos1 < j) && (operandMap[LLVMGetOperand(store, 1)])){
				return false;
			}
		}
	}
    return true;
}

bool hasNoUses(LLVMValueRef instruction) {

    for (LLVMUseRef user = LLVMGetFirstUse(instruction); user != NULL; user = LLVMGetNextUse(user)) {
        LLVMValueRef userValue = LLVMGetUser(user);
        if (LLVMIsAInstruction(userValue)) {
            return false; // Found an instruction user
        }
    }
    return true; // No instruction users found
}

// Common subexpression function
bool walkBBInstructions_subexp_elimi(LLVMBasicBlockRef bb) {
    unordered_map<LLVMValueRef, int> myMap;
	unordered_map<int, LLVMValueRef> stores;
    LLVMValueRef lastInstruction = NULL;
	int i = 0;

	bool executed = false;

    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction;
            instruction = LLVMGetNextInstruction(instruction)) {
		if (LLVMGetInstructionOpcode(instruction) == LLVMAlloca) continue;
        // Check if the instruction matches a previous one
        for (auto it = myMap.begin(); it != myMap.end(); ++it) {
            if (compareInstructions(instruction, it->first, myMap, stores)) {
                LLVMReplaceAllUsesWith(instruction, it->first);
                lastInstruction = instruction;
				executed = true;
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
	return executed;
}

bool walkBBInstructions_constant_folding(LLVMBasicBlockRef bb) {
	bool executed = false;

	//looping through instructions in block
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		
		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
		LLVMValueRef operand1 = LLVMGetOperand(instruction, 0);
		LLVMValueRef operand2 = LLVMGetOperand(instruction, 1);

		
		if (op >= LLVMAdd && op <= LLVMFMul){
			if (LLVMIsConstant(operand1) && LLVMIsConstant(operand2)){
				LLVMValueRef result;
				if (op == LLVMAdd) result = LLVMConstAdd(operand1, operand2);
				else if (op == LLVMSub) result = LLVMConstSub(operand1, operand2);
				else if (op == LLVMMul) result = LLVMConstMul(operand1, operand2);
				LLVMReplaceAllUsesWith(instruction, result);
				executed = true;
			}
		}
    }
	return executed;
}

bool walkBBInstructions_deadcode_elimiation(LLVMBasicBlockRef bb) {
	bool executed = false;

	//looping through instructions in block
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
		if (op == LLVMStore || op == LLVMAlloca || op == LLVMCall || LLVMIsATerminatorInst(instruction)) continue;
		if (hasNoUses(instruction)){
			LLVMInstructionEraseFromParent(instruction);
			executed = true;
		}
    }
	return executed;
}

unordered_map<LLVMValueRef, LLVMValueRef> generate(LLVMBasicBlockRef bb) {
	unordered_map<LLVMValueRef, int> myMap;

    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		if (LLVMGetInstructionOpcode(instruction) == LLVMStore) {
			LLVMValueRef operand = LLVMGetOperand(instruction, 1);
			myMap[operand] = instruction;
		}
	}
	return myMap;	
}

unordered_set<LLVMValueRef> kill (LLVMBasicBlockRef, unordered_set<LLVMValueRef> stores){
	unordered_map<LLVMValueRef> mySet;
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		if (LLVMGetInstructionOpcode(instruction) == LLVMStore) {
			LLVMValueRef operand = LLVMGetOperand(instruction, 1);
			for (auto it = stores.begin(); it != stores.end(); ++it){
				if (operand == LLVMGetOperand(*it, 1)){
					mySet.insert(*it);
				}
			}
		}
	}
	return mySet;
}

bool ConstantPropagation(LLVMValueRef function) {

}

void walkBasicblocks(LLVMValueRef function){
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function);
 			 basicBlock;
  			 basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		
		printf("\nIn basic block\n");
		int change = 1;

		while (change >= 1){
			change = 0;
			if (walkBBInstructions_subexp_elimi(basicBlock)) change++;
			if (walkBBInstructions_constant_folding(basicBlock)) change++;
			if (walkBBInstructions_deadcode_elimiation(basicBlock)) change++;
			
		}

	}
}

void walkFunctions(LLVMModuleRef module){
	for (LLVMValueRef function =  LLVMGetFirstFunction(module); 
			function; 
			function = LLVMGetNextFunction(function)) {

		const char* funcName = LLVMGetValueName(function);	

		walkBasicblocks(function);
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
		walkFunctions(m);
		//LLVMDumpModule(m);
	}
	else {
	    printf("m is NULL\n");
	}
	
	return 0;
}
