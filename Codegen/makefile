lib = ../Parser/ast
main = compiler
source = assembly
folder = tests
test_file = test2.c

clang_flags = `llvm-config-15 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-15/ -ggdb -gdwarf-4 -g
syntax_files = ../Parser/semantic_analysis.c ../Parser/y.tab.c ../Parser/lex.yy.c
optimizer_files = ../Optimizer/Optimization.c

build: RegisterAlloc.c $(main).c
	clang++ $(clang_flags) -o $(source).out $(syntax_files) $(optimizer_files) $(lib).c RegisterAlloc.c $(main).c

test:
	./$(source).out build $(folder)/$(test_file).c $(folder)/assembly/$(test_file).s

clean:
	rm *.out







# LLVMCODE = RegisterAlloc
# TEST = test

# $(LLVMCODE): $(LLVMCODE).c 
# 	clang++ -g `llvm-config-15 --cflags` -I /usr/include/llvm-c-15/ -c $(LLVMCODE).c
# 	clang++ `llvm-config-15 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-15/ $(LLVMCODE).o -o $@

# llvm_file: $(TEST).c 
# 	clang -S -emit-llvm $(TEST).c -o $(TEST).ll

# clean: 
# 	rm -rf $(TEST).ll
# 	rm -rf $(LLVMCODE)
# 	rm -rf *.o
