/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef NETWORKEXTENDED_H
#define NETWORKEXTENDED_H

#include "networkx.h"
#include "parser.h"
#include "parser.tab.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--- Callable
double max (stack*);
double min (stack*);
NX_object* value(params p); /* XXX: Replace value by simple variable input */
NX_object* exit_cli(params p); /* TODO: Improve exit_cli function */

struct init {
    char const *fname;
    union {
        double (*fnc1) (double);
        double (*fnc2) (stack *);
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
    {0, 0}
};

void init_table (void);

//--- Internal functions
int compute(nxfunction function, params p);
void parsecommand(char *command, char **p_parsed, int *i); /* XXX: Replace to yyparse */

#endif // NETWORKEXTENDED_H
