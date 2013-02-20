/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

%{
    #include <math.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include "networkextended.h"
    #define YYDEBUG 1
    #define YYPRINT(file, type, value) yyprint(file, type, value)
    int yylex(void);
    void yyerror(char const*s);
    void yyprint();
%}

%union {
    double val;
    char sym;
    symrec *tptr;
}

%token <val> NUM /* Simple double precision number */
%token <sym> LP RP LA RA LB RB COMMA COLON PLUS MINUS TIMES OVER EQ TO STOP
%token <tptr> VAR FNCT /* Variable and function */
%type <val> /*genexp*/ exp

%right EQ
%left PLUS MINUS
%left TIMES OVER
%right TO
%right COMMA
%right COLON

%% /* The grammar follows */

input       : /* empty */
            | input line
;

line        : STOP      
            | exp STOP { printf ( ">>> %.10g\n", $1 ); }
            | error STOP { yyerrok; }
;

exp         : NUM               { $$ = $1; }
            | VAR               { $$ = $1->value.var; }
            | VAR EQ exp        { $$ = $3; $1->value.var = $3; }
            | FNCT LP exp RP    { $$ = (*($1->value.fnctptr))($3); }
            | exp PLUS exp      { $$ = $1 + $3; }
            | exp MINUS exp     { $$ = $1 - $3; }
            | exp TIMES exp     { $$ = $1 * $3; }
            | exp OVER exp      { $$ = $1 / $3; }
            | exp TO exp        { $$ = pow ($1, $3); }
            | LP exp RP         { $$ = $2; }
;
/* End of grammar */
%%

void yyerror ( char const *s ) {
    fprintf ( stderr, "netext: %s\n", s );
}

void yyprint (FILE *file, int type, YYSTYPE value) {
    if (type == VAR)
        fprintf(file, " %s", value.tptr->name);
    else if (type == NUM)
        fprintf(file, " %g", value.val);
}
