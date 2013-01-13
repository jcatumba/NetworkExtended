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

#include "uthash.h"
#include "networkx.h"

typedef NX_object (*netext_function)(params, NX_object);

typedef struct{
    int cmd_size;
    char *var_name;
    char **cmd_val;
} params;

typedef struct {
    char id[10];
    int value;
    NX_object object;
    UT_hash_handle hh;
} hash_var;

typedef struct {
    char name[25];
    netext_function func_call;
    UT_hash_handle hh;
} hash_func;

// Functions for hashing variables
hash_var *find_variable(char key[10]);
void delete_variable(hash_var *variable);
void add_variable(char repr[10], int amount, NX_object nxobj);
void delete_all_variables();
void print_vars();

// Functions for hashing internals
hash_func *find_function(char key[25]);
void delete_function(hash_func *function);
void add_function(char name[25], netext_function function);
void print_functions();

// Internal functions
int compute(netext_function function, params p, NX_object nxobj);
void parsecommand(char *command, char **p_parsed, int *i);

// Callable functions
NX_object add(params p, NX_object nxobj);
NX_object deduct(params p, NX_object nxobj);
NX_object multiply(params p, NX_object nxobj);
NX_object value(params p, NX_object nxobj);
NX_object exit_cliparams p, NX_object nxobj);

#endif // NETWORKEXTENDED_H