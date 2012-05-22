CFLAGS= -g


parser:
	lex parser.l
	yacc -d grammar.y

vm: *.c
	${CC} ${CFLAGS} -o $@ $^

all: vm

clean:
	rm lex.yy.c 2> /dev/null
	rm y.tab.* 2> /dev/null
	rm parser.c 2> /dev/null
	rm vm 2> /dev/null


.PHONY: parser vm clean all
