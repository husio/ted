
%{

#include <stdio.h>
#include <string.h>

#include "ted.h"



void
yyerror(const char *err)
{
    fprintf(stderr, "error: %s\n", err);
}

int
yywrap()
{
    return 1;
}

main()
{
    yyparse();
}

%}

%token CALL_BEG CALL_END LIST_BEG LIST_END SEP CMD_END

%union
{
    int number;
    char *string;
}
%token <string> VAR_NAME
%token <string> VAL_STR
%token <string> VAL_INT

%%

commands:
        |
        commands command CMD_END
        ;


command:
        object_call
        ;

object_call:
        callable args
        ;

callable:
        VAR_NAME CALL_BEG args CALL_END
        ;

args:
        |
        arg
        |
        args SEP arg
        ;

arg:
        |
        VAR_NAME
        |
        VAL_STR
        |
        VAL_INT
        ;
