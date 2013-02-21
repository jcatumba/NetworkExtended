/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkextended.h"

//--- Functions for add functions and variables to symrec

symrec *sym_table;

void init_table (void) {
    int i;
    for (i=0; arith_fncts[i].fname != 0; i++) {
        symrec *ptr = putsym (arith_fncts[i].fname, FNCT);
        ptr->value.fnctptr = arith_fncts[i].fnct;
    }
}

symrec * putsym (char const *sym_name, int sym_type) {
    symrec *ptr = (symrec*) malloc (sizeof (symrec));
    ptr->name = (char*) malloc (strlen (sym_name) + 1);
    strcpy (ptr->name, sym_name);
    ptr->type = sym_type;
    ptr->value.var = 0; /* Set value to 0 even if fctn */
    ptr->next = (struct symrec *) sym_table;
    sym_table = ptr;
    return ptr;
}

symrec * getsym (char const *sym_name) {
    symrec *ptr;
    for (ptr = sym_table; ptr != (symrec *) 0; ptr = (symrec *) ptr->next) {
        if (strcmp (ptr->name, sym_name) == 0) {
            return ptr;
        }
    }
    return 0;
}

// Internal functions

/* XXX: Remove (bison parser will call functions) */
int compute (nxfunction function, params p){
    NX_object* d = (*function)(p);
    if ( d != NULL ) {
        return 0;
    } else {
        return 1;
    }
}

/* XXX: Replace by yyparse */
void parsecommand (char *command, char **p_parsed, int *i) {
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

//--- Callable

/* TODO: Replace by simple variable call */
NX_object* value (params p) {
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
}
