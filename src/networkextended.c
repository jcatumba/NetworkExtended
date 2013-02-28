/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkextended.h"

// The table of symbols: chain of `struct symrec'
symrec *sym_table;

// Initialize the table of symbols with functions
struct init {
    char const *fname;
    union {
        double (*fnc1) (double);
        double (*fnc2) (stack *);
        NX_object* (*fnc3) (stack *);
    } fnct;
};

struct init const arith_fncts[] =
{
    {"sin", sin},
    {"cos", cos},
    {"atan", atan},
    {"ln", log},
    {"exp", exp},
    {"sqrt", sqrt},
    {"max", {.fnc2 = max}},
    {"min", {.fnc2 = min}},
    {"Graph", {.fnc3 = Graph}},
    {0, 0}
};

void init_table (void) {
    int i;
    for (i=0; arith_fncts[i].fname != 0; i++) {
        if (i <= 5) {
            symrec *ptr = putsym (arith_fncts[i].fname, FNCT);
            ptr->value.fnctptr = arith_fncts[i].fnct.fnc1;
        } else if (i <= 7){
            symrec *ptr = putsym (arith_fncts[i].fname, FNCP);
            ptr->value.fncpptr = arith_fncts[i].fnct.fnc2;
        } else {
            symrec *ptr = putsym (arith_fncts[i].fname, FNCNX);
            ptr->value.fnxptr = arith_fncts[i].fnct.fnc2;
        }
    }
}

//
// Internal functions
//

int compute (nxfunction function, params p){ /* XXX: Remove (bison parser will call functions) */
    NX_object* d = (*function)(p);
    if ( d != NULL ) {
        return 0;
    } else {
        return 1;
    }
}

void parsecommand (char *command, char **p_parsed, int *i) { /* XXX: Replace by yyparse */
    int j;
    char *result = NULL;

    if ( *i==0 ) {
        result = strtok (command, "(");
        p_parsed[0] = result;
    } else {
        result = strtok (command, "=");
        p_parsed[0] = result;
        if (result != NULL) {
            result = strtok (NULL, "(");
            p_parsed[1] = result;
        }
    }
    while (result != NULL) {
        ++*i;
        result = strtok (NULL, ",");
        p_parsed[*i] = result;
    }
    result = strtok (p_parsed[*i-1],")");
    p_parsed[*i-1] = result;
}

//
// CLI functions
//

double max (stack *p) {
    int i;
    double max;
    max = s->value.number;
    for (i=s->top; i>=1; i--) {
        if (max < s->next->value.number)
            max = s->next->value.number;
        pop ();
    }
    return max;
}

double min (stack *p) {
    int i;
    double min;
    min = s->value.number;
    for (i=s->top; i>=1; i--) {
        if (min > s->next->value.number)
            min = s->next->value.number;
        pop ();
    }
    return min;
}

/* TODO: Replace by simple variable call */
/*NX_object* value (params p) {
    hash_var *s = find_variable (p.cmd_val[0]);
    if ( s != NULL ) {
        printf ("%s=\n\t%d\n", s->id, s->value);
    } else {
        printf ("Value of %s not found.\n", p.cmd_val[0]);
        return NULL;
    }
}

NX_object* exit_cli (params p) {
    exit (0);
    return NULL;
}*/
