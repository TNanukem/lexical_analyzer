all: lex out

lex: analyzer.l
	lex analyzer.l

out: lex.yy.c
	cc lex.yy.c src/radix_tree.c src/entry.c -ll -o out
