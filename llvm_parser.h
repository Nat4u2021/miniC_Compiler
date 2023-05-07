#ifndef LLVM_UTILS_H
#define LLVM_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>
#include <unordered_map>

using std::unordered_map;

// Creates LLVM module from given file and returns the module reference
LLVMModuleRef createLLVMModel(char *filename);

//
bool compareInstructions(LLVMValueRef a, LLVMValueRef b, unordered_map<LLVMValueRef, int> instructions, unordered_map<int, LLVMValueRef> stores);

//
bool hasNoUses(LLVMValueRef instruction);

// Walks through instructions in a basic block
void walkBBInstructions_subexp_elimi(LLVMBasicBlockRef bb);

// Walks through instructions in a basic block
void walkBBInstructions_constant_folding(LLVMBasicBlockRef bb);

// Walks through instructions in a basic block
void walkBBInstructions_deadcode_elimiation(LLVMBasicBlockRef bb);

// Walks through basic blocks in a function and calls walkBBInstructions() on each
void walkBasicblocks(LLVMValueRef function);

// Walks through functions in a module and calls walkBasicblocks() on each
void walkFunctions(LLVMModuleRef module);

// Walks through global values in a module and prints their names
void walkGlobalValues(LLVMModuleRef module);

#endif /* LLVM_UTILS_H */