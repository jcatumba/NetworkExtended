/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "uthash.h"

typedef struct{
    int cmd_size;
    char *var_name;
    char **cmd_val;
} params;

// Hashing functions

// Variables

typedef struct {
    char id[10];
    int value;
    UT_hash_handle hh;
} hash_var;

hash_var *cli_vars = NULL;

hash_var *find_variable(char key[10]) {
    hash_var *s;

    HASH_FIND_STR(cli_vars, key, s);
    return s;
}

void delete_variable(hash_var *variable) {
    HASH_DEL(cli_vars, variable);
    free(variable);
}

void add_variable(char repr[10], int amount) {
    hash_var *s;
    hash_var *t = find_variable(repr);

    if ( t == NULL ) {
        s = (hash_var*)malloc(sizeof(hash_var));
        strcpy(s->id, repr);
        s->value = amount;
        HASH_ADD_STR(cli_vars, id, s);
    } else {
        delete_variable(t);
        s = (hash_var*)malloc(sizeof(hash_var));
        strcpy(s->id, repr);
        s->value = amount;
        HASH_ADD_STR(cli_vars, id, s);
    }
}

void delete_all_variables() {
    hash_var *current_var, *tmp;

    HASH_ITER(hh, cli_vars, current_var, tmp) {
        HASH_DEL(cli_vars, current_var);
        free(current_var);
    }
}

void print_vars() {
    hash_var *s;

    for(s = cli_vars; s != NULL; s=s->hh.next){
        printf("variable name %s: value %d\n", s->id, s->value);
    }
}

// Functions

typedef struct {
    char name[25];
    int (*func_call)(params);
    UT_hash_handle hh;
} hash_func;

hash_func *cli_functs = NULL;

hash_func *find_function(char key[25]) {
    hash_func *s;

    HASH_FIND_STR(cli_functs, key, s);
    return s;
}

void delete_function(hash_func *function) {
    HASH_DEL(cli_functs, function);
    free(function);
}

void add_function(char name[25], int (*funct)(params)) {
    hash_func *s;
    hash_func *t = find_function(name);

    if ( t == NULL ) {
        s = (hash_func*)malloc(sizeof(hash_func));
        strcpy(s->name, name);
        s->func_call = funct;
        HASH_ADD_STR(cli_functs, name, s);
    } else {
        delete_function(t);
        s = (hash_func*)malloc(sizeof(hash_func));
        strcpy(s->name, name);
        s->func_call = funct;
        HASH_ADD_STR(cli_functs, name, s);
    }
}

void delete_all_functions() {
    hash_func *current_func, *tmp;

    HASH_ITER(hh, cli_functs, current_func, tmp) {
        HASH_DEL(cli_functs, current_func);
        free(current_func);
    }
}

void print_functions() {
    hash_func *s;

    for(s = cli_functs; s != NULL; s=s->hh.next){
        printf("variable name %s", s->name);
    }
}

// Internal

void parsecommand (char *command, char **p_parsed, int *i) {
    int j;
    char *result = NULL;

    if ( *i==0 ) {
        result = strtok(command, "(");
        p_parsed[0] = result;
    } else {
        result = strtok(command, "=");
        p_parsed[0] = result;
        if (result != NULL) {
            result = strtok(NULL, "(");
            p_parsed[1] = result;
        }
    }
    while (result != NULL) {
        ++*i;
        result = strtok(NULL, ",");
        p_parsed[*i] = result;
    }
    result = strtok(p_parsed[*i-1],")");
    p_parsed[*i-1] = result;

}

// Internal callable functions

int add(params p) {
    int result = atoi(p.cmd_val[0]) + atoi(p.cmd_val[1]);
    add_variable(p.var_name, result);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
}
int deduct(params p) {
    int result = atoi(p.cmd_val[0]) - atoi(p.cmd_val[1]);
    add_variable(p.var_name, result);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
}
int multiply(params p) {
    int result = atoi(p.cmd_val[0]) * atoi(p.cmd_val[1]);
    add_variable(p.var_name, result);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
}
int exit_cli(params p) { exit(0); return 0;}
int value(params p) {
    hash_var *s = find_variable(p.var_name);
    if ( s != NULL ) {
        printf("%s=\n\t%d\n", s->id, s->value);
    } else {
        printf("Value of %s not found.\n", p.var_name);
    }
    return 0;
}

int compute(int (*func_arit)(params), params p){ int d = (*func_arit)(p); return d; };

// Principal

int main( int argc, char *argv[] ) {
    char cmdStr[256], *user, hostname[256], *cmd_val[10];
    int index=0, begin, end;
    
    if ( argc > 1 ) {
        printf("Options given.\n");
    }

    add_function("add", &add);
    add_function("deduct", &deduct);
    add_function("multiply", &multiply);
    add_function("exit", &exit_cli);
    add_function("value", &value);
    //memset(hostname, 0x00, sizeof(hostname));
    //gethostname(hostname, sizeof(hostname));
    //user = (char *)getenv("USER");

    //if( user == NULL ) {
    //	strcpy(user, "unknown");
    //}

    while(1) {
        printf("[NetworkExtended]: ");
    	memset(cmdStr, 0x00, sizeof(cmdStr));
	    gets(cmdStr);
        char *p;
        int index, j=0;
        params pmain;

        p = strchr(cmdStr, '=');
        if (p != NULL) {
            index = 2;
        } else {
            index = 1;
        }

        int size_cmd = index-1;
	    parsecommand(cmdStr, cmd_val, &size_cmd);

        if ( index == 2 ) {
            pmain.var_name = cmd_val[0];
        } else {
            pmain.var_name = "ans";
        }

        int margc = size_cmd-index;

        pmain.cmd_size = margc;
        if ( margc != 0 ) {
            char *cmd_val_tmp[8];
            for ( j=0; j<margc; j++ ) {
                cmd_val_tmp[j] = cmd_val[j+index];
            }
            pmain.cmd_val = cmd_val_tmp;
        }


        hash_func *instance = find_function(cmd_val[index-1]);

        if ( instance != NULL ) {
            int output = compute(instance->func_call, pmain);
        } else {
            printf("Command not found. Try again.\n");
        }
    }
    return 0;
}
