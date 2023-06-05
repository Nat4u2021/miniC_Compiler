#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include "RegisterAlloc.h"


using namespace std;

#define prt(x) if(x) { printf("%s\n", x); }

unordered_map<LLVMValueRef, int> inst_index;
unordered_map<LLVMValueRef, pair<int, int>> live_range;
unordered_map<LLVMValueRef, int> offset_map;
unordered_map<LLVMBasicBlockRef, string> bb_labels;
int local_mem;

FILE *fptr;

bool generates_value(LLVMValueRef instruction) {
    LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
    return (op == LLVMAdd) || (op == LLVMSub) || (op == LLVMMul) || (op == LLVMLoad) || (op == LLVMICmp);
}


void compute_liveness(LLVMBasicBlockRef bb){
    inst_index.clear();
    live_range.clear();
    int index = 0;

    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
        LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
        inst_index[instruction] = index;
        if ((generates_value(instruction)) && (op != LLVMAlloca)){
            live_range[instruction] = {index, index};
            if (op != LLVMLoad){
		        LLVMValueRef operand1 = LLVMGetOperand(instruction, 0);
		        LLVMValueRef operand2 = LLVMGetOperand(instruction, 1);

			    if (live_range.find(operand1) != live_range.end()) {
    			    live_range[operand1] = {live_range[operand1].first, index};
			    }
			    if (live_range.find(operand2) != live_range.end()) {
    			    live_range[operand2] = {live_range[operand2].first, index};
			    }
            }
        }
        index++;
    }

}

bool end(LLVMValueRef operand, LLVMValueRef instruction){
    int curr_pos = inst_index.at(instruction);

    int end_pos = live_range[operand].second;

    return curr_pos >= end_pos;

}

bool adsubmul(LLVMValueRef instruction){
    LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
    return (op == LLVMAdd) || (op == LLVMSub) || (op == LLVMMul);
}

bool exact_end(LLVMValueRef operand, LLVMValueRef instruction){
    int curr_pos = inst_index.at(instruction);
    int end_pos = live_range[operand].second;
    return curr_pos == end_pos;
}

bool has_register(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef operand){
    if (reg_map.find(operand) != reg_map.end()){
        if (reg_map[operand] != "-1") {
            return true;
        }
    } 
    return false;
}

unsigned int LLVMGetNumUses(LLVMValueRef instruction){

    unsigned int numUses = 0;
    for (LLVMUseRef use = LLVMGetFirstUse(instruction); use; use = LLVMGetNextUse(use)) {
        numUses++;
    }
    return numUses;
}

// Custom comparison function
bool compareNumUses(LLVMValueRef a, LLVMValueRef b) {
    unsigned int numUsesA = LLVMGetNumUses(a);
    unsigned int numUsesB = LLVMGetNumUses(b);
    return numUsesA < numUsesB;
}

vector<LLVMValueRef> get_sorted_instructions(LLVMBasicBlockRef bb){
    vector<LLVMValueRef> sorted_instructions;
    for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
        if (generates_value(instruction)) sorted_instructions.push_back(instruction);
    }
    sort(sorted_instructions.begin(), sorted_instructions.end(), compareNumUses);

    return sorted_instructions;

}

LLVMValueRef find_spill(unordered_map<LLVMValueRef, string> reg_map, vector<LLVMValueRef> list){
    for (LLVMValueRef element: list){
        if (has_register(reg_map, element)){
            return element;
        } 
    }
    return NULL;

}


void printMap(unordered_map<LLVMValueRef, string> reg_map) {
    for (const auto& pair : reg_map) {
        LLVMValueRef value = pair.first;
        string str = pair.second;

        // Casting LLVMValueRef to the appropriate LLVM type
        if (LLVMIsAInstruction(value)) {
            std::cout << "Instruction: " << LLVMGetValueName(value) << ", Value: " << str << std::endl;
        } 
    }
}


unordered_map<LLVMValueRef, string> reg_alloc(LLVMValueRef function){

    unordered_map<LLVMValueRef, string> reg_map;

    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(function); bb; bb = LLVMGetNextBasicBlock(bb)) {
        vector<string> available_registers = {"ebx", "ecx", "edx"};

        compute_liveness(bb);
        for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
            if (LLVMGetInstructionOpcode(instruction) != LLVMAlloca){
                if (!generates_value(instruction)){
                    for (unsigned i = 0; i < LLVMGetNumOperands(instruction); ++i) {
                        LLVMValueRef operand = LLVMGetOperand(instruction, i);
                        if (end(operand, instruction) && has_register(reg_map, operand)){
                            available_registers.push_back(reg_map[operand]);
                        }
                    }
                }
                else{
                    if (adsubmul(instruction) && has_register(reg_map, LLVMGetOperand(instruction, 0)) && exact_end(LLVMGetOperand(instruction, 0), instruction)){
                        reg_map[instruction] = reg_map[LLVMGetOperand(instruction, 0)];
                        if ( end(LLVMGetOperand(instruction, 1), instruction) && has_register(reg_map, LLVMGetOperand(instruction, 1)) ){
                            available_registers.push_back(reg_map[LLVMGetOperand(instruction, 1)]);
                        }
                    }
                    else if (available_registers.size() > 0){
                        string avail = available_registers[0];
                        reg_map[instruction] = avail;
                        available_registers.erase(remove(available_registers.begin(), available_registers.end(), avail), available_registers.end());
                        for (unsigned i = 0; i < LLVMGetNumOperands(instruction); ++i) {
                            LLVMValueRef operand = LLVMGetOperand(instruction, i);
                            if (end(operand, instruction) && has_register(reg_map, operand)){
                                available_registers.push_back(reg_map.at(operand));
                            }
                        }
                    }
                    else if (available_registers.size() <= 0){
                        vector<LLVMValueRef> sorted_list = get_sorted_instructions(bb);
                        LLVMValueRef V = find_spill(reg_map, sorted_list);

                        if (LLVMGetNumUses(V) > LLVMGetNumUses(instruction)){
                            reg_map[instruction] = "-1";
                        }
                        else{
                            string R = reg_map.at(V);
                            reg_map[instruction] = R;
                            reg_map[V] = "-1";
                        }
                        for (unsigned i = 0; i < LLVMGetNumOperands(instruction); ++i) {
                            LLVMValueRef operand = LLVMGetOperand(instruction, i);
                            if (end(operand, instruction) && has_register(reg_map, operand)){
                                available_registers.push_back(reg_map.at(operand));
                            }
                        }
                    }
                }

            }
        }
    }
    return reg_map;
}

void createBBLabels(LLVMValueRef function){
    bb_labels.clear();

    string bbName;
    unsigned int count = 0;

    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(function); bb; bb = LLVMGetNextBasicBlock(bb)) {
		bbName = ".L" + to_string(count);
		count++;
        bb_labels[bb] = bbName;
    }
}

void printDirectives(LLVMValueRef function, char* filename) {
    if (function == NULL) return;

    const char* funcName = LLVMGetValueName(function);

    // print directives
    fprintf(fptr, "\t.file\t\"%s\"\n", filename);
    fprintf(fptr, "\t.text\n");
    fprintf(fptr, "\t.globl %s\n", funcName);
    fprintf(fptr, "\t.type %s, @function\n", funcName);
    fprintf(fptr, "%s:\n", funcName);

}

void printFunctionEnd(){
    
    fprintf(fptr, "\tpopl %%ebx\n");
    fprintf(fptr, "\tmovl %%ebp, %%esp\n");
    fprintf(fptr, "\tpopl %%ebp\n");
    fprintf(fptr, "\tret\n");
}

void printStack() {

    fprintf(fptr, "\tpushl %%ebp\n");
    fprintf(fptr, "\tmovl %%esp, %%ebp\n");
    fprintf(fptr, "\tsubl $%d, %%esp\n", local_mem);
    fprintf(fptr, "\tpushl %%ebx\n");
}


void getOffsetMap(LLVMValueRef function, unordered_map<LLVMValueRef, string> reg_map){
    offset_map.clear();
    int offset = 0;
    int allocCount = 0;
    for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(function); bb; bb = LLVMGetNextBasicBlock(bb)) {
        for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
            LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
            if (op == LLVMAlloca){
                allocCount++;
                offset -= 4;
                offset_map[instruction] = offset;
            }
            else if (op == LLVMStore){
                LLVMValueRef operand1 = LLVMGetOperand(instruction, 0);
                LLVMValueRef operand2 = LLVMGetOperand(instruction, 1);
                if (LLVMIsAArgument(operand1)){
                    offset_map[operand2] = 8;
                }
                else if (LLVMIsConstant(operand1)){
                    continue;
                }
                else if (!has_register(reg_map, operand1)){
                    offset_map[operand1] = offset_map[operand2];
                }
            }
            else if (op == LLVMLoad){
                LLVMValueRef operand1 = LLVMGetOperand(instruction, 0);

                if (!has_register(reg_map, instruction)){
                    offset_map[instruction] = offset_map[operand1];
                }
            }
        }
    }

    local_mem = 4*allocCount;    
}


void return_inst(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef instruction){
    LLVMValueRef A = LLVMGetOperand(instruction, 0);

    if (LLVMIsConstant(A)){
        int const_val = LLVMConstIntGetSExtValue(A);
        fprintf(fptr, "\tmovl %d, %%eax\n", const_val);
    }
    else if (reg_map.find(A) != reg_map.end() && reg_map[A] == "-1"){  // in memory
        int k = offset_map[A];
        fprintf(fptr, "\tmovl %d(%%ebp), %%eax\n", k);
    }

    else if (reg_map.find(A) != reg_map.end() && reg_map[A] != "-1"){  // in register
        string reg = reg_map[A];
        fprintf(fptr, "\tmovl %%%s , %%eax\n", reg.c_str());
    }
    printFunctionEnd();
}

void load_inst(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef instruction){
    if (has_register(reg_map, instruction)){
        string exx = reg_map[instruction];
        LLVMValueRef b = LLVMGetOperand(instruction, 0);
        int c = offset_map[b];
        fprintf(fptr, "\tmovl %d(%%ebp), %%%s\n", c, exx.c_str());
    }
    else {
        // load register to register
        LLVMValueRef b = LLVMGetOperand(instruction, 0);
        int c1 = offset_map[b];
        int c2 = offset_map[instruction];
        fprintf(fptr, "\tmovl %d(%%ebp), %d(%%ebp)\n", c1, c2);
    }
}

void store_inst(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef instruction){
    LLVMValueRef A = LLVMGetOperand(instruction, 0);
    LLVMValueRef b = LLVMGetOperand(instruction, 1);

    if (LLVMIsConstant(A)){
        int c = offset_map[b];
        int const_val = LLVMConstIntGetSExtValue(A);
        fprintf(fptr, "\tmovl $%d, %d(%%ebp)\n", const_val, c);
    }
    else if (reg_map.find(A) != reg_map.end()){
        if (reg_map[A] != "-1"){
            string reg = reg_map[A];
            int c = offset_map[b];
            fprintf(fptr, "\tmovl %%%s, %d(%%ebp)\n", reg.c_str(), c);
        }
        else{
            int c1 = offset_map[A];
            fprintf(fptr, "\tmovl %d(%%ebp), %%eax\n", c1);
            int c2 = offset_map[b];
            fprintf(fptr, "\tmovl %%eax, %d(%%ebp),\n", c2);
        }
    }
}

void call_inst(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef instruction){
    fprintf(fptr, "\tpushl %%ebx\n");
    fprintf(fptr, "\tpushl %%ecx\n");
    fprintf(fptr, "\tpushl %%edx\n");

    LLVMValueRef call_func = LLVMGetCalledValue(instruction);
    int numParams = LLVMCountParams(call_func);

    const char* funcName = LLVMGetValueName(call_func);

    //call function has a parameter
    if (numParams == 1){
        LLVMValueRef P = LLVMGetParam(call_func, 0);
        if (LLVMIsConstant(P)){
            int const_val = LLVMConstIntGetSExtValue(P);
            fprintf(fptr, "\tpushl $%d\n", const_val);
        }

        else if (reg_map.find(P) != reg_map.end()){
            if (reg_map[P] == "-1"){ // in memory
                int k = offset_map[P];
                fprintf(fptr, "\tpushl %d(%%ebp)\n", k);
            }
            else{                   //in register
                string reg = reg_map[P];
                fprintf(fptr, "\tpushl %%%s\n", reg.c_str());
            }
        }
    }

    //call the function
    fprintf(fptr, "\tcall %s\n", funcName);

    if (numParams == 1){
        fprintf(fptr, "\taddl $4, %%esp\n"); 
    }

    //pop off all registers
    fprintf(fptr, "\tpopl %%edx\n");
    fprintf(fptr, "\tpopl %%ecx\n");
    fprintf(fptr, "\tpopl %%ebx\n");

    if (numParams == 0){
        if (has_register(reg_map, instruction)){
            string reg = reg_map[instruction];
            fprintf(fptr, "\tmovl %%eax, %%%s\n", reg.c_str());
        }
        else if (reg_map.find(instruction) != reg_map.end()){
            int k = offset_map[instruction];
            fprintf(fptr, "\tmovl %%eax, %d(%%ebp),\n", k);
        }
    }

}

void arithmetic_inst(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef instruction){
    string X;
    LLVMValueRef A = LLVMGetOperand(instruction, 0);
    LLVMValueRef B = LLVMGetOperand(instruction, 1);
    string operation;

    LLVMOpcode op = LLVMGetInstructionOpcode(instruction);

    if (op == LLVMAdd){
        operation = "addl";
    }
    else if (op == LLVMSub){
        operation = "subl";
    }
    else if (op == LLVMMul){
        operation = "imull";
    }
    else if (op == LLVMICmp){
        operation = "cmpl";
    }

    if (has_register(reg_map, instruction)){
        X = reg_map[instruction];
    }
    else{
        X = "eax";
    }

    if (LLVMIsAConstant(A)){
        int const_val = LLVMConstIntGetSExtValue(A);
        fprintf(fptr, "\tmovl $%d, %%%s\n", const_val, X.c_str());
    }
    else if (reg_map.find(A) != reg_map.end()){
        if (reg_map[A] == "-1"){ // in memory
            int n = offset_map[A];
            fprintf(fptr, "\tmovl %d(%%ebp), %%%s\n", n, X.c_str());
        }
        else {                   //in register
            string reg = reg_map[A];
            if (X != reg) {
                fprintf(fptr, "\tmovl %%%s, %%%s\n", reg.c_str(), X.c_str());
            }
        }
    }

    if (LLVMIsAConstant(B)){
        int const_val = LLVMConstIntGetSExtValue(B);
        fprintf(fptr, "\t%s $%d, %%%s\n", operation.c_str(), const_val, X.c_str());

    }
    else if (reg_map.find(B) != reg_map.end() && reg_map[B] == "-1"){  // in memory
        int m = offset_map[B];
        fprintf(fptr, "\t%s %d(%%ebp), %%%s\n", operation.c_str(), m, X.c_str());
    }
    else if (reg_map.find(B) != reg_map.end() && reg_map[B] != "-1"){  // in register
        string reg = reg_map[B];
        fprintf(fptr, "\t%s %%%s, %%%s\n", operation.c_str(), reg.c_str(), X.c_str());
    }

    if (reg_map.find(instruction) != reg_map.end() && reg_map[instruction] == "-1"){  // in memory
        int k = offset_map[instruction];
        fprintf(fptr, "\tmovl %%eax, %d(%%ebp)\n", k);
    }

}

void branch_inst(unordered_map<LLVMValueRef, string> reg_map, LLVMValueRef instruction){
    if (!LLVMIsConditional(instruction)){
        LLVMBasicBlockRef block = (LLVMBasicBlockRef) LLVMGetOperand(instruction, 0);
        string L = bb_labels.at(block);
        fprintf(fptr, "\tjmp %s\n", L.c_str());
    }
    else{
        LLVMValueRef cmp = LLVMGetOperand(instruction, 0);
        LLVMIntPredicate predicate = LLVMGetICmpPredicate(cmp);
        LLVMBasicBlockRef operand1 = (LLVMBasicBlockRef) (LLVMGetOperand(instruction, 1));
        LLVMBasicBlockRef operand2 = (LLVMBasicBlockRef) (LLVMGetOperand(instruction, 2));
        string L1, L2;
        if (bb_labels.find(operand1) != bb_labels.end()){
            L1 = bb_labels[operand1]; 
        }
        if (bb_labels.find(operand2) != bb_labels.end()){
            L2 = bb_labels[operand2]; 
        }

        if (predicate == LLVMIntEQ){
            fprintf(fptr, "\tje %s\n", L1.c_str());
        }
        else if (predicate == LLVMIntNE){
            fprintf(fptr, "\tjne %s\n", L1.c_str());
        }
        else if (predicate == LLVMIntSGT){
            fprintf(fptr, "\tjg %s\n", L1.c_str());
        }
        else if (predicate == LLVMIntSGE){
            fprintf(fptr, "\tjge %s\n", L1.c_str());
        }
        else if (predicate == LLVMIntSLT){
            fprintf(fptr, "\tjl %s\n", L1.c_str());
        }
        else if (predicate == LLVMIntSLE){
            fprintf(fptr, "\tjle %s\n", L1.c_str());
        }

        fprintf(fptr, "\tjmp %s\n", L2.c_str());
    }
}

void codegen(LLVMModuleRef module, char* output_filename){
    if (output_filename == NULL) return;

    unordered_map<LLVMValueRef, string> reg;
    fptr = fopen(output_filename, "w");

	for (LLVMValueRef function =  LLVMGetFirstFunction(module); function; function = LLVMGetNextFunction(function)) {
 
        reg = reg_alloc(function);
        printDirectives(function, output_filename);
        getOffsetMap(function, reg);
        createBBLabels(function);

        for (LLVMBasicBlockRef bb = LLVMGetFirstBasicBlock(function); bb; bb = LLVMGetNextBasicBlock(bb)) {
            fprintf(fptr, "%s:\n", bb_labels[bb].c_str());

            if(bb == LLVMGetFirstBasicBlock(function)) {
                printStack();
            }

            for (LLVMValueRef instruction = LLVMGetFirstInstruction(bb); instruction; instruction = LLVMGetNextInstruction(instruction)) {
                LLVMOpcode op = LLVMGetInstructionOpcode(instruction);
                if (op == LLVMLoad) load_inst(reg, instruction);
                else if (op == LLVMStore) store_inst(reg, instruction);
                else if (op == LLVMCall) call_inst(reg, instruction);
                else if (op == LLVMRet) return_inst(reg, instruction);
                else if (op == LLVMBr) branch_inst(reg, instruction);
                else if (op == LLVMAdd) arithmetic_inst(reg, instruction);
                else if (op == LLVMSub) arithmetic_inst(reg, instruction);
                else if (op == LLVMICmp)arithmetic_inst(reg, instruction);

            }
        }

        fprintf(fptr, "\n");
    }

    if (fptr != NULL){
        fclose(fptr);
    }
    

}

void walkFunctions(LLVMModuleRef module){

	for (LLVMValueRef function =  LLVMGetFirstFunction(module); 
			function; 
			function = LLVMGetNextFunction(function)) {

		const char* funcName = LLVMGetValueName(function);	
         
 	}
}