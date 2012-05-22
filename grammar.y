
%{

#include <stdio.h>
#include <string.h>

#include "ted.h"

ted_VM *vm;


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

void
_debug_builtins()
{
    printf("\n----------- builtins ------------\n");
    ted_print(vm->builtins);
}

void
_debug_stack()
{
    int i;

    for (i=0; i<ted_List_len(vm->closures); ++i) {
        printf("\n----------- stack level %d ------------\n", i);
        ted_print(vm->closures);
    }
}

main()
{
    vm = ted_VM_new();

    fprintf(stdout,
        "           Welcome to TED language shell!\n"
        "Type .s for stack print and .b to print all builtins.\n"
        "\n");
    yyparse();
}


%}

%token DEBUG_STACK DEBUG_BUILTINS
%token CALL_BEG CALL_END LIST_BEG LIST_END SEP CMD_END TOK_ASSIGN

%union
{
    int number;
    char *string;
}
%token <string> VAR_NAME
%token <string> VAL_STR
%token <number> VAL_INT

%%

commands:
        |
        commands command CMD_END
        ;


command:
        |
        debug_cmd
        |
        assign
        |
        object_call
        ;

debug_cmd:
        DEBUG_STACK
            { _debug_stack(); }
        |
        DEBUG_BUILTINS
            { _debug_builtins(); }
        ;

assign:
        assign_str | assign_int | assign_var
        ;

assign_str:
        VAR_NAME TOK_ASSIGN VAL_STR
        {
            ted_VM_setvar(vm,
                ted_Str_new($1), ted_Str_new($3));
        }
        ;
assign_int:
        VAR_NAME TOK_ASSIGN VAL_INT
        {
            ted_VM_setvar(vm,
                ted_Str_new($1), ted_Int_new($3));
        }
        ;
assign_var:
        VAR_NAME TOK_ASSIGN VAR_NAME
        {
            ted_Obj *o;
            o = ted_VM_getvar(vm, ted_Str_new($3));
            if (o == NULL) {
                ted_panic("Variable not found: %s\n", $3);
            }
            ted_VM_setvar(vm, ted_Str_new($1), o);
        }
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
