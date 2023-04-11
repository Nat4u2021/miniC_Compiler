prog = miniC
$(prog).out: $(prog).l $(prog).y
	yacc -d -v $(prog).y
	lex $(prog).l
	gcc -o $(prog).out lex.yy.c y.tab.c
clean:
	rm lex.yy.c y.tab.c y.tab.h $(prog).out y.output