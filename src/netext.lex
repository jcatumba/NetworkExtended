%{
#include "netext.h"
#include "netext.tab.h"
#include <stdio.h>
%}

%option noyywrap

digit   [0-9]
posint  {digit}+
int     "-"?{posint}
long    {int}(""|("."{posint}))

char    [a-zA-z]
 /* "-"?[0-9]+(""|"."([0-9]+)) */
%%

{long}         { yylval.val = atof(yytext); return NUM; }
"+"            { yylval.sym = yytext[0]; return PLUS; }
"-"            { yylval.sym = yytext[0]; return MINUS; }
"*"            { yylval.sym = yytext[0]; return TIMES; }
"/"            { yylval.sym = yytext[0]; return OVER; }
"^"            { yylval.sym = yytext[0]; return TO; }
"="            { yylval.sym = yytext[0]; return EQ; }
{char}+        { symrec *s = getsym(yytext); if (s==0) s = putsym(yytext, VAR) ; yylval.tptr = s; return s->type; }
"("            { return LP; }
")"            { return RP; }
"["            { return LA; }
"]"            { return RA; }
"{"            { return LB; }
"}"            { return RB; }
","            { return COMMA; }
":"            { return COLON; }
[ \t]+         { }
"\n"           { return STOP; }

%%
