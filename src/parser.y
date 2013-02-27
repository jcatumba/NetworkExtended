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
    #include "parser.h"
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

%token <val> NUM STR /* Simple double precision number */
%token <sym> LP RP LA RA LB RB COMMA COLON PLUS MINUS TIMES OVER EQ TO STOP
%token <tptr> VAR FNCT FNCP /* Variable and function */
%type <val> /*exp*/ basicexp genericexp csv

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
            | genericexp STOP { printf ( ">>> %.10g\n", $1 ); }
            | error STOP      { yyerrok; }
;

genericexp  : basicexp
            | FNCP LP csv RP    { $$ = (*($1->value.fncpptr))(s); }
;

basicexp    : NUM                     { $$ = $1; }
            | VAR                     { $$ = $1->value.var; }
            | VAR EQ basicexp         { $$ = $3; $1->value.var = $3; }
            | FNCT LP basicexp RP     { $$ = (*($1->value.fnctptr))($3); }
            | basicexp PLUS basicexp  { $$ = $1 + $3; }
            | basicexp MINUS basicexp { $$ = $1 - $3; }
            | basicexp TIMES basicexp { $$ = $1 * $3; }
            | basicexp OVER basicexp  { $$ = $1 / $3; }
            | basicexp TO basicexp    { $$ = pow ($1, $3); }
            | LP basicexp RP          { $$ = $2; }
;

csv         : basicexp           { push (NUM, $1); }
            | csv COMMA basicexp { push (NUM, $3); }
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

//--- Functions for handle struct
void push (int type, double val) {
    if (s->top == MAXSIZE - 1 ) {
        return; /* stack is full */
    } else {
        switch (type)  {
            //case STR:
            //    s = putitem (s->top+1, STR);
            //    strcpy (s->value.string, val.string);
            //    break;
            case NUM:
                s = putitem (s->top+1, NUM);
                s->value.number = val;
                break;
            default:
                break;
        }
    }
    return;
}

int pop () {
    int type;
    if (s->top == -1) {
        return s->top; /* stack is empty */
    } else {
        type = s->type;
        s = s->next;
    }
    return s->top;
}

void display () {
    int i, type;
    if (s->top == -1)
        return; /* stack is empty */
    else {
        for (i=s->top; i>=0; i--) {
            stack *ptr = getitem (i);
            type = ptr->type;
            if (type == STR)
                printf ("%s\n", ptr->value.string);
            else if (type == NUM )
                printf ("%.10g\n", ptr->value.number);
        }
    }
    printf("\n");
}

stack * putitem (int top, int type) {
    stack *ptr = getitem (top);
    if (ptr == 0)
        ptr = (stack*) malloc (sizeof (stack));
    ptr->top = top;
    ptr->type = type;
    ptr->next = s;
    s = ptr;
    return ptr;
}

stack * getitem (int top) {
    stack *ptr;
    for (ptr = s; ptr != (stack *)0; ptr = (stack*)ptr->next) {
        if (ptr->top == top)
            return ptr;
    }
    return 0;
}

void clear_stack () {
    int i, j;
    for (i=s->top; i>=0; i--)
        pop ();
    return;
}
