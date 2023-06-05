#ifndef REGISTER_ALLOC_H
#define REGISTER_ALLOC_H

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


using namespace std;

extern unordered_map<LLVMValueRef, int> inst_index;
extern unordered_map<LLVMValueRef, pair<int, int>> live_range;

void codegen(LLVMModuleRef module, char* output_filename);

#endif // REGISTER_ALLOC_H
