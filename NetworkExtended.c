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
    int int1, int2, int3, int4, int5;
    char *str1, *str2, *str3, *str4, *str5;
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

void delete_all() {
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

hash_func *find_function(char key[10]) {
    hash_func *s;

    HASH_FIND_STR(cli_functs, key, s);
    return s;
}

void delete_function(hash_func *function) {
    HASH_DEL(cli_functs, function);
    free(function);
}

void add_function(char name[10], int (*funct)(params)) {
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

void parsecommand (char *command, char **p_parsed, int i) {
    int j;
    char *result = NULL;

    if ( i==0 ) {
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
        ++i;
        result = strtok(NULL, ",");
        p_parsed[i] = result;
    }
    result = strtok(p_parsed[i-1],")");
    p_parsed[i-1] = result;

    for (j=0;j<i;j++) {
        printf("[%d : %s]\n", j, p_parsed[j]);
    }
}

// Internal functions and structs

int add(params p) {return p.int1 + p.int2;}
int deduct(params p) {return p.int1 - p.int2;}
int multiply(params p) {return p.int1 * p.int2;}

int compute(int (*func_arit)(params), params p){ int d = (*func_arit)(p); return d; };

// Principal

int main( int argc, char *argv[] ) {
    char cmdStr[256], *user, hostname[256], *cmd_val[5];
    int index=0, begin, end;
    
    if ( argc > 1 ) {
        printf("Options given.\n");
    }

    memset(hostname, 0x00, sizeof(hostname));
    gethostname(hostname, sizeof(hostname));
    user = (char *)getenv("USER");

    if( user == NULL ) {
    	strcpy(user, "unknown");
    }

    while(1) {
        printf("[NetworkExtended]: ");
    	memset(cmdStr, 0x00, sizeof(cmdStr));
	    gets(cmdStr);
        char *p;
        int index;
        p = strchr(cmdStr, '=');
        if (p != NULL) {
            index = 2;
        } else {
            index = 1;
        }
	    parsecommand(cmdStr, cmd_val, index-1);
        params pmain;
	    if ( strncmp("exit", cmd_val[0], 4) == 0 ) {
	        return 0;
	    } else if ( strncmp("add", cmd_val[index-1], 5) == 0 ) {
            pmain.int1 = atoi(cmd_val[index]);
            pmain.int2 = atoi(cmd_val[index+1]);
	        int result = compute(&add, pmain);
            if ( index == 2 ) {
                add_variable(cmd_val[0], result);
                printf("%s=\n", cmd_val[0]);
            } else {
                add_variable("ans", result);
                printf("ans=\n");
            }
	        printf("\t%d\n", result);
	    } else if ( strncmp("deduct", cmd_val[index-1], 6) == 0 ) {
            pmain.int1 = atoi(cmd_val[index]);
            pmain.int2 = atoi(cmd_val[index+1]);
	        int result = compute(&deduct, pmain);
            if ( index == 2 ) {
                add_variable(cmd_val[0], result);
                printf("%s=\n", cmd_val[0]);
            } else {
                add_variable("ans", result);
                printf("ans=\n");
            }
	        printf("\t%d\n", result);
	    } else if ( strncmp("multiply", cmd_val[index-1], 11) == 0 ) {
            pmain.int1 = atoi(cmd_val[index]);
            pmain.int2 = atoi(cmd_val[index+1]);
	        int result = compute(&multiply, pmain);
            if ( index == 2 ) {
                add_variable(cmd_val[0], result);
                printf("%s=\n", cmd_val[0]);
            } else {
                add_variable("ans", result);
                printf("ans=\n");
            }
	        printf("\t%d\n", result);
        } else if ( strncmp("value", cmd_val[index-1], 5) == 0 ) {
            hash_var *s = find_variable(cmd_val[index]);
            if ( s != NULL ) {
                printf("%s=\n\t%d\n", cmd_val[index], s->value);
            } else {
                printf("Value of %s not found.\n", cmd_val[index]);
            }
	    } else {
	        printf("Unknown command. Try again.\n");
	    }
    }
    return 0;
}
