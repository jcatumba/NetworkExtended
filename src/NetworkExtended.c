/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkextended.h"

typedef int type;
enum {Int, Bool, Long, Float, Complex, ByteArray, String, Tuple, List, Dict};

// Classes
extern NX_object* nxGraph,* nxDiGraph,* nxMultiGraph,* nxMultiDiGraph;
// Generic Methods
extern NX_object* nx_pagerank;
// Graph Methods
extern NX_object* nx_len,* nx_add_node,* nx_remove_node,* nx_add_edge,* nx_remove_edge,* nx_clear,* nx_order;
extern NX_object* nx_nodes;

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

type nx_type_detection(PyObject* obj) {
    type typed;
    if(PyInt_Check(obj)) typed = Int;
    if(PyBool_Check(obj)) typed = Bool;
    if(PyLong_Check(obj)) typed = Long;
    if(PyFloat_Check(obj)) typed = Float;
    if(PyComplex_Check(obj)) typed = Complex;
    if(PyByteArray_Check(obj)) typed = ByteArray;
    if(PyString_Check(obj)) typed = String;
    if(PyTuple_Check(obj)) typed = Tuple;
    if(PyList_Check(obj)) typed = List;
    if(PyDict_Check(obj)) typed = Dict;
    return typed;
}

char* nx_parse_output(PyObject* output) {
    char* buffer;
    buffer = (char*)malloc(30);
    type rtype = nx_type_detection(output);
    if (rtype == Int || rtype == Long) {
        long int out;
        out = PyInt_AsLong(output);
        sprintf(buffer, "%d", out);
    } else if (rtype == Float) {
        double out;
        out = PyFloat_AsDouble(output);
        sprintf(buffer, "%lf", out);
    } else if (rtype == Complex) {
        double out1, out2;
        char out1_s[10], out2_s[10];
        out1 = PyComplex_RealAsDouble(output);
        out2 = PyComplex_ImagAsDouble(output);
        sprintf(out1_s, "%lf", out1);
        sprintf(out2_s, "%lf", out1);
        strcpy(buffer, out1_s);
        strcat(buffer, " + ");
        strcat(buffer, out2_s);
        strcat(buffer, "i");
    } else if (rtype == String) {
        char* out;
        out = (char*)PyString_AsString(output);
        strcpy(buffer, out);
    }
    switch (rtype) {
        case Int:
            break;
        case Bool:
            break;
        case Long:
            break;
        case Float:
            break;
        case Complex:
            break;
        case ByteArray:
            break;
        case String:
            break;
    }
    return buffer;
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
    //    strcpy(user, "unknown");
    //}

    add_function("add", &add);
    add_function("deduct", &deduct);
    add_function("multiply", &multiply);
    add_function("exit", &exit_cli);
    add_function("value", &value);
    add_function("Graph", &Graph);
    add_function("DiGraph", &DiGraph);
    add_function("MultiGraph", &MultiGraph);
    add_function("MultiDiGraph", &MultiDiGraph);
    add_function("len", &len);
    add_function("add_node", &add_node);
    add_function("remove_node", &remove_node);
    add_function("add_edge", &add_edge);
    add_function("remove_edge", &remove_edge);
    add_function("clear", &clear);
    add_function("order", &order);
    add_function("nodes", &nodes);

    Py_SetProgramName("NetworkExtended");
    Py_Initialize();
    NX_object* nx_module = load_networkx();
    load_objects(nx_module);

    while(1) {
        printf("[NetworkExtended]: ");
        memset(cmdStr, 0x00, sizeof(cmdStr));
        fgets(cmdStr, 100, stdin);
        /* Remove new line character TODO: Remove on bison-cli implementation */
        int len = strlen(cmdStr);
        if (cmdStr[len-1] == '\n')
            cmdStr[len-1] = '\0';
        /*gets(cmdStr);*/
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
        NX_object* nx_obj;

        if ( instance != NULL ) {
            int output = compute(instance->func_call, pmain);
        } else {
            printf("Command not found. Try again.\n");
        }
    }
    Py_Finalize();
    return 0;
}

// Callable functions

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
NX_object* nxgraph_creation(NX_object* nx_obj, params p) { /* Generalized constructor of graphs */
    NX_object* graph_const = NULL;
    graph_const = (NX_object*)malloc(sizeof(NX_object));
    if (graph_const->py_object = PyObject_CallObject(nx_obj->py_object, NULL)) {
        graph_const->name = p.var_name;
        graph_const->parent = nx_obj->name;
        add_variable(graph_const->name, 0, graph_const);
    }
    return graph_const;
    free(graph_const);
}
NX_object* Graph(params p) {
    NX_object* graph = nxgraph_creation(nxGraph, p);
    if (graph == NULL)
        fprintf(stderr, "Graph creation failed.\n");
    return graph;
}
NX_object* DiGraph(params p) {
    NX_object* digraph = nxgraph_creation(nxDiGraph, p);
    if (digraph == NULL)
        fprintf(stderr, "DiGraph creation failed.\n");
    return digraph;
}
NX_object* MultiGraph(params p) {
    NX_object* multigraph = nxgraph_creation(nxMultiGraph, p);
    if (multigraph == NULL)
        fprintf(stderr, "MultiGraph creation failed.\n");
    return multigraph;
}
NX_object* MultiDiGraph(params p) {
    NX_object* multidigraph = nxgraph_creation(nxMultiDiGraph, p);
    if (multidigraph == NULL)
        fprintf(stderr, "MultiDiGraph creation failed.\n");
    return multidigraph;
}
/* Basic Methods for Graphs */
PyObject* tuple_creation(PyObject* graph, params p){
    int i;
    PyObject* tuple = PyTuple_New(p.cmd_size);
    PyTuple_SetItem(tuple, 0, graph);
    for (i=1; i<p.cmd_size; i++) {
        /* TODO: p.cmd_val[i] is not allways an integer. Replace on bison-cli */
        PyTuple_SetItem(tuple, i, PyInt_FromLong(atoi(p.cmd_val[i])));
    }
    return tuple;
    free(tuple);
}
NX_object* len(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = tuple_creation(f->object->py_object,p);
        PyObject* value = PyObject_CallObject(nx_len->py_object, tuple);
        if (value) printf("%ld\n", PyInt_AsLong(value));
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}
NX_object* add_node(params p) { /* TODO: Handle addition of node attributes */
    hash_var *f = find_variable(p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = tuple_creation(f->object->py_object, p);
        PyObject_CallObject(nx_add_node->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* remove_node(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = tuple_creation(f->object->py_object, p);
        PyObject_CallObject(nx_remove_node->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* add_edge(params p) { /* TODO: Handle attributes */
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = tuple_creation(f->object->py_object, p);
        PyObject_CallObject(nx_add_edge->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* remove_edge(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = tuple_creation(f->object->py_object, p);
        PyObject_CallObject(nx_remove_edge->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* clear(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = tuple_creation(f->object->py_object, p);
        PyObject_CallObject(nx_clear->py_object, tuple);
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}
NX_object* nodes(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if (f != NULL) {
        int i;
        PyObject* tuple = tuple_creation(f->object->py_object, p);
        PyObject* result = PyObject_CallObject(nx_nodes->py_object, tuple);
        int size = PyList_Size(result);
        printf("[");
        for (i=0; i<size; i++) {
            PyObject* item = PyList_GetItem(result, i);
            char* parsed = nx_parse_output(item);
            if (i == size-1) {
                printf("%s", parsed);
            } else {
                printf("%s,", parsed);
            }
        }
        printf("]\n");
    } else {
        fprintf(stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}
NX_object* order(params p) {
    hash_var *f = find_variable(p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = tuple_creation(f->object->py_object, p);
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
        printf("Variable %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}
NX_object* exit_cli(params p) {
    exit(0);
}
