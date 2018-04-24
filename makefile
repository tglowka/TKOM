lexer		:	lex.yy.c parser.tab.c ErrorHandling.cpp main.cpp parser.cpp
			g++ -o lexer lex.yy.c parser.tab.c ErrorHandling.cpp main.cpp parser.cpp -std=c++11

lex.yy.c	:	lexer.l
			flex lexer.l

parser.tab.c:	parser.y
		    bison -d parser.y

clean		:
		rm lexer lex.yy.c parser.tab.c parser.tab.h
