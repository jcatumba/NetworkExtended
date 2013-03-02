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
    #include <math.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <ctype.h>
    #define YYDEBUG 1
    #define YYPRINT(file, type, value) yyprint(file, type, value)
    int yylex (void);
    void yyerror (char const*);
    void yyprint ();
    void put_output (datatype);
    datatype nxobj_to_datatype (NX_object*);
    datatype num_to_datatype (double);
%}

%union {
    datatype val;
    char sym;
    symrec *tptr;
}

%token <val> NUM STR NXO /* Double, String or NXO */
%token <sym> LP RP LA RA LB RB COMMA COLON PLUS MINUS TIMES OVER EQ TO STOP
%token <tptr> VAR FNCT FNCP FNCNX /* Variable and functions */
%type <val> /*exp*/ basicexp genericexp /*csv*/

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
            | genericexp STOP { put_output ( $1 ); }
            | error STOP      { yyerrok; }
;

genericexp  : basicexp
;

basicexp    : NUM                     { double num = $1.data.num; $$ = num_to_datatype (num); }
            | VAR                     { $$ = $1->value.var; }
            | VAR EQ basicexp         { $$ = $3; $1->value.var = $3; }
            | FNCT LP basicexp RP     { $$.data.num = (*($1->value.fnctptr))($3.data.num); $$.type = NUM; }
            | FNCP LP csv RP          { double num = (*($1->value.fncpptr))(s); $$ = num_to_datatype (num); }
            | FNCNX LP csv RP         { NX_object *obj = (*($1->value.fnxptr))(s); $$ = nxobj_to_datatype (obj); }
            | basicexp PLUS basicexp  { $$.data.num = $1.data.num + $3.data.num; $$.type = NUM; }
            | basicexp MINUS basicexp { $$.data.num = $1.data.num - $3.data.num; $$.type = NUM; }
            | basicexp TIMES basicexp { $$.data.num = $1.data.num * $3.data.num; $$.type = NUM; }
            | basicexp OVER basicexp  { $$.data.num = $1.data.num / $3.data.num; $$.type = NUM; }
            | basicexp TO basicexp    { $$.data.num = pow ($1.data.num, $3.data.num); $$.type = NUM; }
            | LP basicexp RP          { $$.data.num = $2.data.num; $$.type = NUM; }
;

csv         : basicexp           { push ($1); }
            | csv COMMA basicexp { push ($3); }
;
/* End of grammar */
%%

//
// Functions for parser
//
void yyerror (char const *s) {
    fprintf ( stderr, "NetworkExtended: %s\n", s );
}

void yyprint (FILE *file, int type, YYSTYPE value) {
    if (type == VAR)
        fprintf(file, " %s", value.tptr->name);
    else if (type == NUM)
        fprintf(file, " %g", value.val);
}

void put_output (datatype val) {
    int type = val.type;
    switch (type) {
        case NUM:
            printf (">>> %.10g\n", val.data.num);
            break;
        case STR:
            printf (">>> %s\n", val.data.str);
            break;
        case NXO:
            //printf (">>> Blur Object: %s", val.data.obj->name);
            break;
        default:
            break;
    }
}

datatype nxobj_to_datatype (NX_object *obj) {
    datatype ptr;
    ptr.type = NXO;
    ptr.data.obj = obj;
    return ptr;
}

datatype num_to_datatype (double num) {
    datatype ptr;
    ptr.type = NUM;
    ptr.data.num = num;
    return ptr;
}

//
// Functions for handle table of symbols `struct symrec'
//
symrec *putsym (char const *sym_name, int sym_type) {
    symrec *ptr = (symrec*) malloc (sizeof (symrec));
    ptr->name = (char*) malloc (strlen (sym_name) + 1);
    strcpy (ptr->name, sym_name);
    ptr->type = sym_type;
    ptr->value.var.data.num = 0; /* Set value to 0 even if fctn */
    ptr->next = (struct symrec *) sym_table;
    sym_table = ptr;
    return ptr;
}

symrec *getsym (char const *sym_name) {
    symrec *ptr;
    for (ptr = sym_table; ptr != (symrec *) 0; ptr = (symrec *) ptr->next) {
        if (strcmp (ptr->name, sym_name) == 0) {
            return ptr;
        }
    }
    return 0;
}

//
// Functions for handle stack
//
void push (datatype val) {
    if (s->top == MAXSIZE - 1 ) {
        return; /* stack is full */
    } else {
        switch (val.type) {
            case STR:
                s = putitem (s->top+1, STR);
                strcpy (s->value.string, val.data.str);
                break;
            case NUM:
                s = putitem (s->top+1, NUM);
                s->value.number = val.data.num;
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

void clear_stack () {
    int i, j;
    for (i=s->top; i>=0; i--)
        pop ();
    return;
}

//
// Functions for handle stack chain
//
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
