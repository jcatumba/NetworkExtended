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
    datatype str_to_datatype (char[50]);
    datatype do_arith (datatype, datatype, int);
%}

%union {
    datatype val;
    char sym;
    symrec *tptr;
}

%token <val> NUM STR NXO /* Double, String or NXO */
%token <sym> LP RP LS RS LB RB  COMMA COLON PLUS MINUS TIMES OVER EQ TO STOP
%token <tptr> VAR FNCT FNCP FNCNX /* Variable and functions */
%type <val> basic hashable

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
            | basic STOP { put_output ( $1 ); }
            | error STOP { yyerrok; }
            ;

hashable    : NUM        { double num = $1.data.num; $$ = num_to_datatype (num); }
            | STR        { char *str = $1.data.str; $$ = str_to_datatype (str); }
            | NXO        { NX_object *obj = $1.data.obj; $$ = nxobj_to_datatype (obj); }
/*            | tuple      {}*/
            ;

basic       : hashable
/*            | list
            | dict */
            | VAR               { $$ = $1->value.var; }
            | VAR EQ basic      { $$ = $3; $1->value.var = $3; }
            | FNCT LP basic RP  { $$.data.num = (*($1->value.fnctptr))($3.data.num); $$.type = NUM; }
            | FNCP LP csv RP    { $$.data.num = (*($1->value.fncpptr))(s); $$.type = NUM; }
            | FNCNX LP csv RP   { NX_object *obj = (*($1->value.fnxptr))(s); if (obj != NULL ) $$ = nxobj_to_datatype (obj); }
            | basic PLUS basic  { $$ = do_arith ($1, $3, PLUS); }
            | basic MINUS basic { $$ = do_arith ($1, $3, MINUS); }
            | basic TIMES basic { $$ = do_arith ($1, $3, TIMES); }
            | basic OVER basic  { $$ = do_arith ($1, $3, OVER); }
            | basic TO basic    { $$ = do_arith ($1, $3, TO); }
            | LP basic RP       { $$.data.num = $2.data.num; $$.type = NUM; }
            ;

/* Only match comma separated values of basic type (non colon separated values) */
csv         : basic           { push ($1); }
            | csv COMMA basic { push ($3); }
            ;

/* Only match comma separated values of colon separated values */
/*cscv        : colsv
            | cscv COMMA colsv
            ;

colsv       : hashable COLON basic
            ;

tuple       : LP RP
            | LP csv RS
            ;

list        : LS RS
            | LS csv RS
            ;

dict        : LB RB
            | LB cscv RB
            ;*/
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
    clear_stack ();
}

datatype do_arith (datatype one, datatype two, int operator) {
    datatype result;
    if (one.type == NUM && two.type == NUM) {
        switch (operator) {
            case PLUS:
                result.data.num = one.data.num + two.data.num;
                break;
            case MINUS:
                result.data.num = one.data.num - two.data.num;
                break;
            case TIMES:
                result.data.num = one.data.num * two.data.num;
                break;
            case OVER:
                result.data.num = one.data.num / two.data.num;
                break;
            case TO:
                result.data.num = pow (one.data.num, two.data.num);
                break;
        }
        result.type = NUM;
    } else if (one.type == STR && two.type == STR) {
        switch (operator) {
            case PLUS:
                strcpy (result.data.str, one.data.str);
                strcat (result.data.str, two.data.str);
                break;
            default:
                strcpy (result.data.str, "Invalid types (strings). Use numbers instead.");
                break;
        }
        result.type = STR;
    }
    return result;
}

datatype nxobj_to_datatype (NX_object *obj) {
    datatype ptr;
    ptr.type = NXO;
    ptr.data.obj = obj;
    obj->name = sym_table->name;
    return ptr;
}

datatype num_to_datatype (double num) {
    datatype ptr;
    ptr.type = NUM;
    ptr.data.num = num;
    return ptr;
}

datatype str_to_datatype (char str[50]) {
    datatype ptr;
    ptr.type = NUM;
    strcpy (ptr.data.str, str);
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
            case NXO:
                s = putitem (s->top+1, NXO);
                strcpy (s->value.string, val.data.obj->name);
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
                printf ("%d: %s\n", i, ptr->value.string);
            else if (type == NUM )
                printf ("%d: %.10g\n", i, ptr->value.number);
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
