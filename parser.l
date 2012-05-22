%{

#include <stdio.h>
#include "y.tab.h"

%}

%%
\.s                         return DEBUG_STACK;
\.b                         return DEBUG_BUILTINS;

[0-9]+                      yylval.number = atoi(yytext); return VAL_INT;
\".*\"                      yylval.string = strdup(yytext); return VAL_STR;
[a-z][a-zA-Z0-9]*           yylval.string = strdup(yytext); return VAR_NAME;
\(                          return CALL_BEG;
\)                          return CALL_END;
=                           return TOK_ASSIGN;
,                           return SEP;
\[                          return LIST_BEG;
\]                          return LIST_END;

\n                          return CMD_END;
[ \t]+                      /* ignore whitespace */

%%
