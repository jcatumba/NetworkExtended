%{
#include "mfcalc.h"
#include "mfcalc.tab.h"
#include <stdio.h>
%}

%option noyywrap

posint  [0-9]+
int     "-"?posint
long    int(""|("."posint))

 /* "-"?[0-9]+(""|"."([0-9]+)) */
%%

"-"?[0-9]+(""|"."([0-9]+))              { yylval.val = atof(yytext); return NUM; }
"+"                { yylval.sym = yytext[0]; return PLUS; }
"-"                { yylval.sym = yytext[0]; return MINUS; }
"*"                { yylval.sym = yytext[0]; return TIMES; }
"/"                { yylval.sym = yytext[0]; return OVER; }
"^"                { yylval.sym = yytext[0]; return TO; }
"="                { yylval.sym = yytext[0]; return EQ; }
[a-zA-Z]+           { symrec *s = getsym(yytext); if (s==0) s = putsym(yytext, VAR) ; yylval.tptr = s; return s->type; }
"("                 { return LP; }
")"                 { return RP; }
[ \t]+              { }
"\n"                { return STOP; }

%%
