all: lex out

lex: analyzer.l
	lex analyzer.l

out: lex.yy.c
	cc lex.yy.c -ll -o out
