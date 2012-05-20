CFLAGS= -g


vm: *.c

# vm:
# 	lex parser.l
# 	yacc -d grammar.y
# 	${CC} lex.yy.c y.tab.c -o vm

all: vm

clean:
	rm lex.yy.c 2> /dev/null
	rm y.tab.* 2> /dev/null
	rm parser.c 2> /dev/null
	rm vm 2> /dev/null
