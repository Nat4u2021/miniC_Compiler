#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unordered_map>
#include <unordered_set>
#include <llvm-c/Core.h>
#include <llvm-c/IRReader.h>
#include <llvm-c/Types.h>

LLVMModuleRef createLLVMModel(char* filename);

bool walkBBInstructions_subexp_elimi(LLVMBasicBlockRef bb);

bool walkBBInstructions_constant_folding(LLVMBasicBlockRef bb); 

bool walkBBInstructions_deadcode_elimiation(LLVMBasicBlockRef bb);

bool ConstantPropagation(LLVMValueRef function);

void OptimizeLLVM(LLVMModuleRef module);