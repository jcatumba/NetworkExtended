/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include <stdio.h>
//#include <unistd.h>
#include <stdlib.h>
#include <string.h>
//#include <regex.h>
#include "uthash.h"
#include "networkx.h"
#include "networkextended.h"

// Functions for hashing variables

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

void add_variable(char repr[10], int amount, NX_object nxobj) {
    hash_var *s;
    hash_var *t = find_variable(repr);

    if ( t != NULL ) {
        delete_variable(t);
    }
    s = (hash_var*)malloc(sizeof(hash_var));
    strcpy(s->id, repr);
    s->value = amount;
    s->object = nxobj;
    HASH_ADD_STR(cli_vars, id, s);
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

// Functions for hashing internals

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

void add_function(char name[25], netext_function funct) {
    hash_func *s;
    hash_func *t = find_function(name);

    if ( t != NULL ) {
        delete_function(t);
    }
    s = (hash_func*)malloc(sizeof(hash_func));
    strcpy(s->name, name);
    s->func_call = funct;
    HASH_ADD_STR(cli_functs, name, s);
}

void print_functions() {
    hash_func *s;

    for(s = cli_functs; s != NULL; s=s->hh.next){
        printf("variable name %s", s->name);
    }
}

// Internal functions

int compute(netext_function function, params p, NX_object nxobj){
    NX_object d = (*function)(p, nxobj);
    if ( d != NULL ) {
        return 0;
    } else {
        return 1;
    }
}

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

// Callable functions

NX_object add(params p, NX_object nxobj) {
    int result = atoi(p.cmd_val[0]) + atoi(p.cmd_val[1]);
    add_variable(p.var_name, result, NULL);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
    return NULL;
}
NX_object deduct(params p, NX_object nxobj) {
    int result = atoi(p.cmd_val[0]) - atoi(p.cmd_val[1]);
    add_variable(p.var_name, result, NULL);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
    return NULL;
}
NX_object multiply(params p, NX_object nxobj) {
    int result = atoi(p.cmd_val[0]) * atoi(p.cmd_val[1]);
    add_variable(p.var_name, result, NULL);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
    return NULL;
}
NX_object Graph(params p, NX_object callable) {
    //p.var_name = h
    //p.cmd_size = 0
    //p.cmd_val = []
    NX_object graph;
    if(graph.py_object = PyObject_CallObject(nxGraph.py_object, NULL)) {
        graph.name = p.var_name;
        graph.parent = nxGraph.name;
        add_variable(graph.name, 0, graph);
        return graph;
    } else {
        printf("Graph creation failed.\n");
        return NULL;
    }
}
NX_object value(params p, NX_object nxobj) {
    hash_var *s = find_variable(p.var_name);
    if ( s != NULL ) {
        printf("%s=\n\t%d\n", s->id, s->value);
    } else {
        printf("Value of %s not found.\n", p.var_name);
    }
    return NULL;
}
NX_object exit_cli(params p, NX_object nxobj) {
    exit(0);
    return NULL;
}

// Principal

int main( int argc, char *argv[] ) {
    char cmdStr[256], *user, hostname[256], *cmd_val[10];
    int index=0, begin, end;
    
    if ( argc > 1 ) {
        printf("Options given.\n");
    }

    //memset(hostname, 0x00, sizeof(hostname));
    //gethostname(hostname, sizeof(hostname));
    //user = (char *)getenv("USER");

    //if( user == NULL ) {
    //	strcpy(user, "unknown");
    //}

    add_function("add", &add);
    add_function("deduct", &deduct);
    add_function("multiply", &multiply);
    add_function("exit", &exit_cli);
    add_function("value", &value);
    add_function("Graph", &Graph);

    Py_SetProgramName("NetworkExtended");
    Py_Initialize();
    NX_object nx_module = load_networkx();
    load_objects();

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
            int output = compute(instance->func_call, pmain, NX_object nxobj);
        } else {
            printf("Command not found. Try again.\n");
        }
    }
    Py_Finalize();
    return 0;
}
