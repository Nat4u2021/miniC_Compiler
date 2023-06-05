prog = miniC
main = parser

$(prog).out: $(prog).l $(prog).y ast.c semantic_analysis.c $(main).c
	yacc -d -v $(prog).y
	lex $(prog).l
	g++ -o $(prog).out lex.yy.c y.tab.c ast.c semantic_analysis.c $(main).c
clean:
	rm lex.yy.c y.tab.c y.tab.h $(prog).out y.output