/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkextended.h"

// Classes
extern NX_object* nxGraph,* nxDiGraph,* nxMultiGraph,* nxMultiDiGraph;
// Generic Methods
extern NX_object* nx_pagerank;
// Graph Methods
extern NX_object* nx_len,* nx_add_node,* nx_add_edge,* nx_order;

// Functions for add functions and variables to symrec

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
    ptr->next = (struct symrec *)sym_table;
    sym_table = ptr;
    return ptr;
}

symrec * getsym (char const *sym_name) {
    symrec *ptr;
    for (ptr = sym_table; ptr != (symrec *) 0; ptr = (symrec *)ptr->next) {
        if (strcmp (ptr->name, sym_name) == 0) {
            return ptr;
        }
    }
    return 0;
}

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

void add_variable(const char repr[10], int amount, NX_object *nxobj) {
    hash_var *s;
    hash_var *t = find_variable((char *)repr);

    if ( t != NULL ) {
        delete_variable(t);
    }
    s = (hash_var*)malloc(sizeof(hash_var));
    strcpy(s->id, (char *)repr);
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

void add_function(char name[25], nxfunction funct) {
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

int compute(nxfunction function, params p){
    NX_object* d = (*function)(p);
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

// Callable functions TODO: Edit functions to match the pointer: double (*func_t) (params)

NX_object* add(params p) {
    int result = atoi(p.cmd_val[0]) + atoi(p.cmd_val[1]);
    add_variable(p.var_name, result, NULL);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
    return NULL;
}
NX_object* deduct(params p) {
    int result = atoi(p.cmd_val[0]) - atoi(p.cmd_val[1]);
    add_variable(p.var_name, result, NULL);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
    return NULL;
}
NX_object* multiply(params p) {
    int result = atoi(p.cmd_val[0]) * atoi(p.cmd_val[1]);
    add_variable(p.var_name, result, NULL);
    printf("%s=\n", p.var_name);
    printf("\t%d\n", result);
    return NULL;
}
/* Graphs creation functions */
NX_object* Graph(params p) {
    NX_object* graph = NULL;
    graph = (NX_object*)malloc(sizeof(NX_object));
    if(graph->py_object = PyObject_CallObject(nxGraph->py_object, NULL)) {
        graph->name = p.var_name;
        graph->parent = nxGraph->name;
        add_variable(graph->name, 0, graph);
    } else {
        printf("Graph creation failed.\n");
    }
    return graph;
}
NX_object* DiGraph(params p) {
    NX_object* digraph = NULL;
    digraph = (NX_object*)malloc(sizeof(NX_object));
    if(digraph->py_object = PyObject_CallObject(nxDiGraph->py_object, NULL)) {
        digraph->name = p.var_name;
        digraph->parent = nxDiGraph->name;
        add_variable(digraph->name, 0, digraph);
    } else {
        printf("DiGraph creation failed.\n");
    }
    return digraph;
}
NX_object* MultiGraph(params p) {
    NX_object* multigraph = NULL;
    multigraph = (NX_object*)malloc(sizeof(NX_object));
    if(multigraph->py_object = PyObject_CallObject(nxMultiGraph->py_object, NULL)) {
        multigraph->name = p.var_name;
        multigraph->parent = nxMultiGraph->name;
        add_variable(multigraph->name, 0, multigraph);
    } else {
        printf("MultiGraph creation failed.\n");
    }
    return multigraph;
}
NX_object* MultiDiGraph(params p) {
    NX_object* multidigraph = NULL;
    multidigraph = (NX_object*)malloc(sizeof(NX_object));
    if(multidigraph->py_object = PyObject_CallObject(nxMultiDiGraph->py_object, NULL)) {
        multidigraph->name = p.var_name;
        multidigraph->parent = nxMultiDiGraph->name;
        add_variable(multidigraph->name, 0, multidigraph);
    } else {
        printf("MultiDiGraph creation failed.\n");
    }
    return multidigraph;
}
/* Basic Methods for Graphs */
NX_object* len(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = PyTuple_New(1);
        PyTuple_SetItem(tuple, 0, f->object->py_object);
        PyObject* value = PyObject_CallObject(nx_len->py_object, tuple);
        if (value) printf("%ld\n", PyInt_AsLong(value));
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}
NX_object* add_node(params p) { /* TODO: Handle addition of node attributes */
    hash_var *f = find_variable(p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = PyTuple_New(2);
        PyTuple_SetItem(tuple, 0, f->object->py_object);
        PyTuple_SetItem(tuple, 1, PyInt_FromLong(atoi(p.cmd_val[1]))); /* TODO: Allow non integer nodes */
        PyObject_CallObject(nx_add_node->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* add_edge(params p) { /* TODO: Handle attributes */
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = PyTuple_New(3);
        PyTuple_SetItem(tuple, 0, f->object->py_object);
        PyTuple_SetItem(tuple, 1, PyInt_FromLong(atoi(p.cmd_val[1]))); /* TODO: Allow non intenger nodes */
        PyTuple_SetItem(tuple, 2, PyInt_FromLong(atoi(p.cmd_val[2])));
        PyObject_CallObject(nx_add_edge->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* order(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = PyTuple_New(1);
        PyTuple_SetItem(tuple, 0, f->object->py_object);
        PyObject* value = PyObject_CallObject(nx_order->py_object, tuple);
        if (value) printf("%ld\n", PyInt_AsLong(value));
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}
NX_object* value(params p) { /* TODO: Replace by simple variable call */
    hash_var *s = find_variable(p.cmd_val[0]);
    if ( s != NULL ) {
        printf("%s=\n\t%d\n", s->id, s->value);
    } else {
        printf("Value of %s not found.\n", p.cmd_val[0]);
        return NULL;
    }
}
NX_object* exit_cli(params p) {
    exit(0);
    return NULL;
}
