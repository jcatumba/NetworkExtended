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
#include "parser.tab.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//--- Callable
double max (stack*);
double min (stack*);
NX_object* exit_cli(stack*); /* TODO: Improve exit_cli function */

void init_table (void);

//--- Internal functions

#endif // NETWORKEXTENDED_H
