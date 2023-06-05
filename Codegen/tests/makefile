TEST = test1

llvm_file: $(TEST).c
	clang -S -emit-llvm $(TEST).c -o $(TEST).ll

clean: 
	rm -rf $(TEST).ll
