#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
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

		
		if ( (op == LLVMICmp)  || (op >= LLVMAdd && op <= LLVMFMul) ){
			if (LLVMIsConstant(operand1) && LLVMIsConstant(operand2)){
				LLVMValueRef result;
				if (op == LLVMAdd) result = LLVMConstAdd(operand1, operand2);
				else if (op == LLVMSub) result = LLVMConstSub(operand1, operand2);
				else if (op == LLVMMul) result = LLVMConstMul(operand1, operand2);
				else if (op == LLVMICmp) result = LLVMConstICmp(LLVMGetICmpPredicate(instruction), operand1, operand2);
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

void walkBBInstructions(LLVMBasicBlockRef bb){
	for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		// LLVMGetInstructionOpcode gives you LLVMOpcode that is a enum		
		LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
		LLVMDumpValue(instruction);	
	}			

}

unordered_set<LLVMValueRef> generate(LLVMBasicBlockRef bb) {
	unordered_map<LLVMValueRef, LLVMValueRef> myMap;

    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		if (LLVMGetInstructionOpcode(instruction) == LLVMStore) {
			LLVMValueRef operand = LLVMGetOperand(instruction, 1);
			myMap[operand] = instruction;
		}
	}
    unordered_set<LLVMValueRef> mySet; 

    // Convert and store the values in the set
    for (const auto& pair : myMap) {
        mySet.insert(pair.second);
    }
	return mySet;	
}

unordered_set<LLVMValueRef> kill (LLVMBasicBlockRef bb, unordered_set<LLVMValueRef> stores){
	unordered_set<LLVMValueRef> mySet;
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
		if (LLVMGetInstructionOpcode(instruction) == LLVMStore) {
			LLVMValueRef operand = LLVMGetOperand(instruction, 1);
			for (auto it = stores.begin(); it != stores.end(); ++it){
				if ( (*it != instruction) && (operand == LLVMGetOperand(*it, 1)) ){
					mySet.insert(*it);
				}
			}
		}
	}
	return mySet;
}

unordered_map<LLVMBasicBlockRef, vector<LLVMBasicBlockRef>> predecessors(LLVMValueRef function){
	unordered_map<LLVMBasicBlockRef, vector<LLVMBasicBlockRef>> predecessor;

	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		LLVMValueRef terminator = LLVMGetBasicBlockTerminator(basicBlock);
		unsigned int i = LLVMGetNumSuccessors(terminator);

		for (unsigned int j = 0; j < i; j=j+1){
			LLVMBasicBlockRef successor = LLVMGetSuccessor(terminator, j);
			if (predecessor.find(successor) != predecessor.end()){
				predecessor.at(successor).push_back(basicBlock);
			}
			else{
				//remember to free vector
				vector<LLVMBasicBlockRef> vec;
				predecessor[successor] = vec;
				predecessor.at(successor).push_back(basicBlock);
			}
		}
	}
	return predecessor;
}


bool areConstantStoresWithSameValue(unordered_set<LLVMValueRef> storeInstructions) {
    LLVMValueRef constantValue = nullptr;
    bool isFirstStore = true;

    // Iterate over the store instructions
    for (LLVMValueRef storeInstruction : storeInstructions) {
        LLVMValueRef storeValue = LLVMGetOperand(storeInstruction, 0);

        // Check if the store value is a constant
        if (LLVMIsConstant(storeValue)) {
            LLVMValueRef constant = LLVMGetOperand(storeValue, 0);

            // If it's the first store, set the constant value
            if (isFirstStore) {
                constantValue = constant;
                isFirstStore = false;
            }
            // If the constant value is different, return false
            else if (constant != constantValue) {
                return false;
            }
        }
        // If the store value is not a constant, return false
        else {
            return false;
        }
    }

    // Return true if all store instructions were constant and wrote the same value
    return !isFirstStore;
}

void print(unordered_set<LLVMValueRef> stores){
	for (LLVMValueRef s: stores){
		LLVMDumpValue(s);
		printf("   |   ");
	}	
}

void print_v(vector<LLVMBasicBlockRef> vector){
	for (LLVMBasicBlockRef s: vector){
		walkBBInstructions(s);
		printf("   |   ");
	}	
}

bool ConstantPropagation(LLVMValueRef function){


	unordered_set<LLVMValueRef> stores;
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		for (LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction; instruction = LLVMGetNextInstruction(instruction)) {
			if (LLVMGetInstructionOpcode(instruction) == LLVMStore){
				stores.insert(instruction);
				
			}
		}
	}	

	
	unordered_map<LLVMBasicBlockRef, unordered_set<LLVMValueRef>> in;
	unordered_map<LLVMBasicBlockRef, unordered_set<LLVMValueRef>> out;
	unordered_map<LLVMBasicBlockRef, vector<LLVMBasicBlockRef>> pred = predecessors(function);


	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		out[basicBlock] = generate(basicBlock);
	}

	bool change = true;

	while(change) {
		change = false;

		for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {

			vector<LLVMBasicBlockRef> vector_pred;

			if (pred.find(basicBlock) != pred.end()) {
    			vector_pred = pred.at(basicBlock);
				//print_v(vector_pred);
			}

			unordered_set<LLVMValueRef> in_set;

			for (LLVMBasicBlockRef s: vector_pred){
				unordered_set<LLVMValueRef> out_pred = out.at(s);
				
				for (const auto& element : out_pred) {
					in_set.insert(element);
				}
			}
			in[basicBlock] = in_set;

			unordered_set<LLVMValueRef> old_out = out.at(basicBlock); 

			unordered_set<LLVMValueRef> out_set;
			unordered_set<LLVMValueRef> temp_in = in_set;
			unordered_set<LLVMValueRef> kill_set = kill(basicBlock, stores);
			unordered_set<LLVMValueRef> gen_set = generate(basicBlock);

			for (const auto& element : temp_in){
				if (kill_set.find(element) == kill_set.end()){
					out_set.insert(element);
				}
			}

			for (const auto& element : gen_set){
				out_set.insert(element);
			}

			if (out_set != old_out) {
				change = true;
			}

			out[basicBlock] = out_set;
		}
	}

	unordered_set<LLVMValueRef> R;
	unordered_set<LLVMValueRef> deleted;
	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		R  = in.at(basicBlock);
		unordered_set<LLVMValueRef> kill_set = kill(basicBlock, stores);
		for (LLVMValueRef instruction = LLVMGetFirstInstruction(basicBlock); instruction; instruction = LLVMGetNextInstruction(instruction)) {
			if (LLVMGetInstructionOpcode(instruction) == LLVMStore){
				R.insert(instruction);
				for (LLVMValueRef ell : kill_set){
					R.erase(ell);
				}

				// unordered_set<LLVMValueRef> new_R;
				// for (const auto& element : R){
				// 	if ((LLVMGetOperand(instruction, 1) != LLVMGetOperand(element, 1))){
				//  		new_R.insert(element);
				// 	}
				// }
				// R = new_R;
			}
			if (LLVMGetInstructionOpcode(instruction) == LLVMLoad) {

				for (const auto& element : R) {
					LLVMValueRef loadoperand = LLVMGetOperand(instruction, 0);
					
					if ( loadoperand == LLVMGetOperand(element, 1) ) {

						printf("here");
						if (LLVMIsConstant(LLVMGetOperand(element, 0))){
							LLVMReplaceAllUsesWith(instruction, LLVMGetOperand(element, 0));
							deleted.insert(instruction);
						}
					}
				}

				// if (areConstantStoresWithSameValue(new_stores)){
				// 	LLVMReplaceAllUsesWith(instruction, LLVMGetOperand(temp_instruction, 0));
				// 	deleted.insert(instruction);
				// }
			}
		}
	}

	for (const auto& element : deleted){
		LLVMInstructionEraseFromParent(element);
	}

	return deleted.size() > 0;
}

void walkBasicblocks(LLVMValueRef function){

	for (LLVMBasicBlockRef basicBlock = LLVMGetFirstBasicBlock(function); basicBlock; basicBlock = LLVMGetNextBasicBlock(basicBlock)) {
		printf("\nIn basic block\n");
		
		int change = 1;
		
		while (change >= 1){
			change = 0;

			if (walkBBInstructions_subexp_elimi(basicBlock)) change++;
			
			if (walkBBInstructions_constant_folding(basicBlock)) change++;
			if (walkBBInstructions_deadcode_elimiation(basicBlock)) change++;

			if (ConstantPropagation(function)) change++;
			
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
		LLVMDumpModule(m);
	}
	else {
	    printf("m is NULL\n");
	}
	
	return 0;
}
