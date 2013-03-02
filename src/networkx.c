/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkx.h"

//
// References to NetworkX classes and methods
//
/*** Graph Types ***/
NX_object* nxGraph = NULL;
NX_object* nxDiGraph = NULL;
NX_object* nxMultiGraph = NULL;
NX_object* nxMultiDiGraph = NULL;

/*** NX basic methods ***/
NX_object* nx_len = NULL;
NX_object* nx_add_node = NULL;
NX_object* nx_add_edge = NULL;
NX_object* nx_order = NULL;
NX_object* nx_pagerank = NULL;

//
//  Loading NetworkX functions
//
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

//
// Callable functions TODO: Edit functions to match pointer: double (*func_t) (stack*)
//
/*** Graph creation functions ***/
NX_object* Graph (stack *p) {
    NX_object* graph = NULL;
    graph = (NX_object*) malloc (sizeof (NX_object));
    if (graph->py_object = PyObject_CallObject (nxGraph->py_object, NULL)) {
        graph->parent = nxGraph->name;
    } else {
        printf ("Graph creation failed.\n");
    }
    return graph;
}

NX_object* DiGraph (stack *p) {
    NX_object* digraph = NULL;
    digraph = (NX_object*) malloc (sizeof (NX_object));
    if (digraph->py_object = PyObject_CallObject (nxDiGraph->py_object, NULL)) {
        digraph->parent = nxDiGraph->name;
    } else {
        printf ("DiGraph creation failed.\n");
    }
    return digraph;
}

NX_object* MultiGraph (stack *p) {
    NX_object* multigraph = NULL;
    multigraph = (NX_object*) malloc (sizeof (NX_object));
    if (multigraph->py_object = PyObject_CallObject (nxMultiGraph->py_object, NULL)) {
        multigraph->parent = nxMultiGraph->name;
    } else {
        printf ("MultiGraph creation failed.\n");
    }
    return multigraph;
}

NX_object* MultiDiGraph (stack *p) {
    NX_object* multidigraph = NULL;
    multidigraph = (NX_object*) malloc (sizeof (NX_object));
    if (multidigraph->py_object = PyObject_CallObject (nxMultiDiGraph->py_object, NULL)) {
        multidigraph->parent = nxMultiDiGraph->name;
    } else {
        printf ("MultiDiGraph creation failed.\n");
    }
    return multidigraph;
}

/*** Basic Methods for Graphs ***/
double len (stack *p) {
    stack *first = getitem (0);
    symrec *f = getsym (first->value.string);
    if (f != NULL) {
        PyObject* tuple = PyTuple_New (1);
        PyTuple_SetItem (tuple, 0, f->value.var.data.obj->py_object);
        PyObject* value = PyObject_CallObject (nx_len->py_object, tuple);
        if (value) return PyInt_AsLong (value);
    } else {
        fprintf (stderr, ">>> Graph %s not found.\n", first->value.string);
        return 0;
    }
}

/* TODO: Handle addition of node attributes */ /* TODO: Allow non integer nodes */
NX_object* add_node (stack *p) {
    if (p->top != 1) fprintf(stderr, ">>> Usage: add_node (<graph_name>,<number>).\n");
    stack *first = getitem (0);
    symrec *f = getsym (first->value.string);
    if ( f != NULL ) {
        PyObject* tuple = PyTuple_New (2);
        PyTuple_SetItem (tuple, 0, f->value.var.data.obj->py_object);
        PyTuple_SetItem (tuple, 1, PyInt_FromLong (p->value.number)); 
        PyObject_CallObject (nx_add_node->py_object, tuple);
    } else {
        fprintf (stderr, ">>> Graph %s not found.\n", first->value.string);
    }
    return NULL;
}

/* TODO: Handle attributes */ /* TODO: Allow non intenger nodes */
/*NX_object* add_edge (params p) {
    hash_var *f = find_variable (p.cmd_val[0]);
    if (f != NULL) {
        PyObject* tuple = PyTuple_New (3);
        PyTuple_SetItem (tuple, 0, f->object->py_object);
        PyTuple_SetItem (tuple, 1, PyInt_FromLong (atoi (p.cmd_val[1])));
        PyTuple_SetItem (tuple, 2, PyInt_FromLong (atoi (p.cmd_val[2])));
        PyObject_CallObject (nx_add_edge->py_object, tuple);
    } else {
        fprintf (stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
    return NULL;
}*/

/*NX_object* order (params p) {
    hash_var *f = find_variable (p.cmd_val[0]);
    if ( f != NULL ) {
        PyObject* tuple = PyTuple_New (1);
        PyTuple_SetItem (tuple, 0, f->object->py_object);
        PyObject* value = PyObject_CallObject (nx_order->py_object, tuple);
        if (value) printf ("%ld\n", PyInt_AsLong (value));
    } else {
        fprintf (stderr, "Graph %s not found.\n", p.cmd_val[0]);
    }
}*/
