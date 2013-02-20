/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

%{
    #include "networkextended.h"
    #include "parser.tab.h"
    #include <stdio.h>
%}

%option noyywrap

digit   [0-9]
posint  {digit}+
int     "-"?{posint}
long    {int}(""|("."{posint}))

char    [a-zA-z]

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
