source = final
lib = Parser/ast
folder = Tests
test_file = p1


clang_flags = `llvm-config-15 --cxxflags --ldflags --libs core` -I /usr/include/llvm-c-15/ -ggdb -gdwarf-4 -g
syntax_files = Parser/semantic_analysis.c Parser/y.tab.c Parser/lex.yy.c
optimizer_files = Optimizer/Optimization.c
assembler_files = Codegen/RegisterAlloc.c


build: $(assembler_files) final.c
	clang++ $(clang_flags) -o $(source).out $(syntax_files) $(optimizer_files) $(assembler_files) $(lib).c final.c

assemble: main.c
	$(source).out $(folder)/$(test_file).c $(test_file).s
	as --32 $(test_file).s -o $(test_file).o
	clang -m32 main.c $(test_file).s -o $(test_file).out
	./"$(test_file).out"

clean:
	rm *.o *.s *.out