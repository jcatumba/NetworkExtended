/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkx.h"

//--- References to NetworkX classes and methods
/* Graph Types */
NX_object* nxGraph = NULL;
NX_object* nxDiGraph = NULL;
NX_object* nxMultiGraph = NULL;
NX_object* nxMultiDiGraph = NULL;

/* NX basic methods */
NX_object* nx_len = NULL;
NX_object* nx_add_node = NULL;
NX_object* nx_add_edge = NULL;
NX_object* nx_order = NULL;
NX_object* nx_pagerank = NULL;

//--- NX_objects definitions of NetworkX module, classes and methods

void init_networkx () {
    NX_object* nx_module = load_networkx ();
    load_objects (nx_module);
}

NX_object* load_networkx () {
    NX_object* nx_module = NULL;
    nx_module = (NX_object*) malloc (sizeof (NX_object));
    PyObject* nx_name = PyString_FromString ("networkx");
    if (nx_module->py_object = PyImport_Import (nx_name)) {
        nx_module->name = "NetworkX";
        nx_module->parent = "Python";
        printf ("NetworkX reference loaded.\n");
        return nx_module;
    } else {
        printf ("NetworkX reference load failed.\n");
        return NULL;
    }
    Py_DECREF (nx_name);
}

NX_object* load_nx (NX_object *nxobject, const char* attr_name) {
    NX_object* pFun;
    pFun = (NX_object*) malloc (sizeof (NX_object));
    if (pFun->py_object = PyObject_GetAttrString (nxobject->py_object, attr_name)) {
        pFun->name = attr_name;
        pFun->parent = nxobject->name;
        //printf ("Reference of %s at %s loaded.\n", pFun->name, nxobject->name);
        return pFun;
    } else {
        //printf ("Reference of %s at %s load failed.\n", attr_name, nxobject->name);
        return NULL;
    }
}

void load_objects (NX_object *nx_module) {
    // Classes
    nxGraph = load_nx (nx_module, "Graph");
    nxDiGraph = load_nx (nx_module, "DiGraph");
    nxMultiGraph = load_nx (nx_module, "MultiGraph");
    nxMultiDiGraph = load_nx (nx_module, "MultiDiGraph");

    // Generic Methods
    //nx_pagerank = load_nx (nx_module, "pagerank");

    // Graph Methods
    nx_len = load_nx (nxGraph, "__len__");
    nx_add_node = load_nx (nxGraph, "add_node");
    nx_add_edge = load_nx (nxGraph, "add_edge");
    nx_order = load_nx (nxGraph, "order");
}

//--- Functions for hashing variables

hash_var *cli_vars = NULL;

hash_var *find_variable (char key[10]) {
    hash_var *s;
    HASH_FIND_STR (cli_vars, key, s);
    return s;
}

void delete_variable (hash_var *variable) {
    HASH_DEL (cli_vars, variable);
    free (variable);
}

void add_variable (const char repr[10], int amount, NX_object *nxobj) {
    hash_var *s;
    hash_var *t = find_variable ((char *) repr);

    if ( t != NULL ) {
        delete_variable (t);
    }
    s = (hash_var*) malloc (sizeof(hash_var));
    strcpy (s->id, (char *) repr);
    s->value = amount;
    s->object = nxobj;
    HASH_ADD_STR(cli_vars, id, s);
}

void delete_all_variables () {
    hash_var *current_var, *tmp;

    HASH_ITER(hh, cli_vars, current_var, tmp) {
        HASH_DEL(cli_vars, current_var);
        free (current_var);
    }
}

void print_vars () {
    hash_var *s;
    for (s = cli_vars; s != NULL; s=s->hh.next){
        printf ("variable name %s: value %d\n", s->id, s->value);
    }
}

//--- Functions for hashing callables

hash_func *cli_functs = NULL;

hash_func *find_function (char key[25]) {
    hash_func *s;
    HASH_FIND_STR (cli_functs, key, s);
    return s;
}

void delete_function (hash_func *function) {
    HASH_DEL (cli_functs, function);
    free (function);
}

void add_function (char name[25], nxfunction funct) {
    hash_func *s;
    hash_func *t = find_function (name);

    if ( t != NULL ) {
        delete_function (t);
    }
    s = (hash_func*) malloc (sizeof(hash_func));
    strcpy (s->name, name);
    s->func_call = funct;
    HASH_ADD_STR (cli_functs, name, s);
}

void print_functions () {
    hash_func *s;
    for (s = cli_functs; s != NULL; s=s->hh.next) {
        printf ("variable name %s", s->name);
    }
}

//--- Callable functions TODO: Edit functions to match pointer: double (*func_t) (params)

/* Graph creation functions */
NX_object* Graph (params p) {
    NX_object* graph = NULL;
    graph = (NX_object*) malloc (sizeof (NX_object));
    if (graph->py_object = PyObject_CallObject (nxGraph->py_object, NULL)) {
        graph->name = p.var_name;
        graph->parent = nxGraph->name;
        add_variable (graph->name, 0, graph);
    } else {
        printf ("Graph creation failed.\n");
    }
    return graph;
}

NX_object* DiGraph (params p) {
    NX_object* digraph = NULL;
    digraph = (NX_object*) malloc (sizeof (NX_object));
    if (digraph->py_object = PyObject_CallObject (nxDiGraph->py_object, NULL)) {
        digraph->name = p.var_name;
        digraph->parent = nxDiGraph->name;
        add_variable (digraph->name, 0, digraph);
    } else {
        printf ("DiGraph creation failed.\n");
    }
    return digraph;
}

NX_object* MultiGraph (params p) {
    NX_object* multigraph = NULL;
    multigraph = (NX_object*) malloc (sizeof (NX_object));
    if (multigraph->py_object = PyObject_CallObject (nxMultiGraph->py_object, NULL)) {
        multigraph->name = p.var_name;
        multigraph->parent = nxMultiGraph->name;
        add_variable (multigraph->name, 0, multigraph);
    } else {
        printf ("MultiGraph creation failed.\n");
    }
    return multigraph;
}

NX_object* MultiDiGraph (params p) {
    NX_object* multidigraph = NULL;
    multidigraph = (NX_object*) malloc (sizeof (NX_object));
    if (multidigraph->py_object = PyObject_CallObject (nxMultiDiGraph->py_object, NULL)) {
        multidigraph->name = p.var_name;
        multidigraph->parent = nxMultiDiGraph->name;
        add_variable (multidigraph->name, 0, multidigraph);
    } else {
        printf ("MultiDiGraph creation failed.\n");
    }
    return multidigraph;
}

/* Basic Methods for Graphs */
NX_object* len (params p) {
    hash_var *f = find_variable (p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = PyTuple_New (1);
        PyTuple_SetItem (tuple, 0, f->object->py_object);
        PyObject* value = PyObject_CallObject (nx_len->py_object, tuple);
        if (value) printf ("%ld\n", PyInt_AsLong (value));
    } else {
        fprintf (stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}

NX_object* add_node (params p) { /* TODO: Handle addition of node attributes */
    hash_var *f = find_variable (p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = PyTuple_New (2);
        PyTuple_SetItem (tuple, 0, f->object->py_object);
        PyTuple_SetItem (tuple, 1, PyInt_FromLong (atoi (p.cmd_val[1]))); /* TODO: Allow non integer nodes */
        PyObject_CallObject (nx_add_node->py_object, tuple);
    } else {
        fprintf (stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}

NX_object* add_edge (params p) { /* TODO: Handle attributes */
    hash_var *f = find_variable (p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = PyTuple_New (3);
        PyTuple_SetItem (tuple, 0, f->object->py_object);
        PyTuple_SetItem (tuple, 1, PyInt_FromLong (atoi (p.cmd_val[1]))); /* TODO: Allow non intenger nodes */
        PyTuple_SetItem (tuple, 2, PyInt_FromLong (atoi (p.cmd_val[2])));
        PyObject_CallObject (nx_add_edge->py_object, tuple);
    } else {
        fprintf (stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}

NX_object* order (params p) {
    hash_var *f = find_variable (p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = PyTuple_New (1);
        PyTuple_SetItem (tuple, 0, f->object->py_object);
        PyObject* value = PyObject_CallObject (nx_order->py_object, tuple);
        if (value) printf ("%ld\n", PyInt_AsLong (value));
    } else {
        fprintf (stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}
