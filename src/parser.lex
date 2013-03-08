/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

%{
    #include "parser.h"
    #include "parser.tab.h"
%}

%option noyywrap

digit   [0-9]
posint  {digit}+
int     "-"?{posint}
long    {int}(""|("."{posint}))

char    [a-zA-z]
all     [[:alnum:][:blank:]]
%%

{long}         { yylval.val.data.num = atof (yytext); return NUM; }
"+"            { yylval.sym = yytext[0]; return PLUS; }
"-"            { yylval.sym = yytext[0]; return MINUS; }
"*"            { yylval.sym = yytext[0]; return TIMES; }
"/"            { yylval.sym = yytext[0]; return OVER; }
"^"            { yylval.sym = yytext[0]; return TO; }
"="            { yylval.sym = yytext[0]; return EQ; }
"'{all}*'"     { strcpy(yylval.val.data.str, yytext); return STR; }
"\"{all}*\""   { strcpy(yylval.val.data.str, yytext); return STR; }
{char}+        { symrec *sym = getsym (yytext); if (sym==0) sym = putsym (yytext, VAR) ; yylval.tptr = sym; return sym->type; }
"("            { return LP; }
")"            { return RP; }
"\["            { return LS; }
"\]"            { return RS; }
"{"            { return LB; }
"}"            { return RB; }
","            { return COMMA; }
":"            { return COLON; }
[ \t]+         { }
"\n"           { return STOP; }

%%
