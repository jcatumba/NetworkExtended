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
PyObject* nxGraph = NULL;
PyObject* nxDiGraph = NULL;
PyObject* nxMultiGraph = NULL;
PyObject* nxMultiDiGraph = NULL;

/*** NX basic methods ***/
PyObject* nx_len = NULL;
PyObject* nx_add_node = NULL;
PyObject* nx_remove_node = NULL;
PyObject* nx_add_edge = NULL;
PyObject* nx_remove_edge = NULL;
PyObject* nx_order = NULL;
PyObject* nx_write_gml = NULL;
//PyObject* nx_pagerank = NULL;

//
//  Loading NetworkX functions
//
void init_networkx () {
    PyObject* nx_module;
    if(nx_module = load_module ("networkx"))
        load_nx_objects (nx_module);
    else
        printf ("Load of NetworkX failed.");
}

void load_nx_objects (PyObject *parent) {
    // Classes
    nxGraph = load_attr (parent, "Graph");
    nxDiGraph = load_attr (parent, "DiGraph");
    nxMultiGraph = load_attr (parent, "MultiGraph");
    nxMultiDiGraph = load_attr (parent, "MultiDiGraph");

    // Generic Methods
    //nx_pagerank = load_nx (parent, "pagerank");

    // Graph Methods
    nx_len = load_attr (nxGraph, "__len__");
    nx_add_node = load_attr (nxGraph, "add_node");
    nx_remove_node = load_attr (nxGraph, "remove_node");
    nx_add_edge = load_attr (nxGraph, "add_edge");
    nx_remove_edge = load_attr (nxGraph, "remove_edge");
    nx_order = load_attr (nxGraph, "order");
    nx_write_gml = load_attr (parent, "write_gml");
}

//
// Callable functions
//
/*** Graph creation functions ***/
//PyObject* Graph (stack *p) {
//    PyObject* graph = NULL;
//    graph = (PyObject*) malloc (sizeof (PyObject));
//    if (graph->py_object = PyObject_CallObject (nxGraph->py_object, NULL)) {
//        graph->parent = nxGraph->name;
//    } else {
//        printf ("Graph creation failed.\n");
//    }
//    return graph;
//}
//
//PyObject* DiGraph (stack *p) {
//    PyObject* digraph = NULL;
//    digraph = (PyObject*) malloc (sizeof (PyObject));
//    if (digraph->py_object = PyObject_CallObject (nxDiGraph->py_object, NULL)) {
//        digraph->parent = nxDiGraph->name;
//    } else {
//        printf ("DiGraph creation failed.\n");
//    }
//    return digraph;
//}
//
//PyObject* MultiGraph (stack *p) {
//    PyObject* multigraph = NULL;
//    multigraph = (PyObject*) malloc (sizeof (PyObject));
//    if (multigraph->py_object = PyObject_CallObject (nxMultiGraph->py_object, NULL)) {
//        multigraph->parent = nxMultiGraph->name;
//    } else {
//        printf ("MultiGraph creation failed.\n");
//    }
//    return multigraph;
//}
//
//PyObject* MultiDiGraph (stack *p) {
//    PyObject* multidigraph = NULL;
//    multidigraph = (PyObject*) malloc (sizeof (PyObject));
//    if (multidigraph->py_object = PyObject_CallObject (nxMultiDiGraph->py_object, NULL)) {
//        multidigraph->parent = nxMultiDiGraph->name;
//    } else {
//        printf ("MultiDiGraph creation failed.\n");
//    }
//    return multidigraph;
//}
//
///*** Basic Methods for Graphs ***/
//double len (stack *p) {
//    stack *first = getitem (0);
//    symrec *f = getsym (first->value.string);
//    if (f != NULL) {
//        PyObject* tuple = PyTuple_New (1);
//        PyTuple_SetItem (tuple, 0, f->value.var.data.obj->py_object);
//        PyObject* value = PyObject_CallObject (nx_len->py_object, tuple);
//        if (value) return PyInt_AsLong (value);
//    } else {
//        fprintf (stderr, ">>> Graph %s not found.\n", first->value.string);
//        return 0;
//    }
//}
//
///* TODO: Handle addition of node attributes */ /* TODO: Allow non integer nodes */
//PyObject* add_node (stack *p) {
//    if (p->top != 1) fprintf (stderr, ">>> Usage: add_node (<graph_name>,<number>).\n");
//    stack *first = getitem (0);
//    symrec *f = getsym (first->value.string);
//    if ( f != NULL ) {
//        PyObject* tuple = PyTuple_New (2);
//        PyTuple_SetItem (tuple, 0, f->value.var.data.obj->py_object);
//        PyTuple_SetItem (tuple, 1, PyInt_FromLong (p->value.number)); 
//        PyObject_CallObject (nx_add_node->py_object, tuple);
//    } else {
//        fprintf (stderr, ">>> Graph %s not found.\n", first->value.string);
//    }
//    return NULL;
//}
//
///* TODO: Handle attributes */ /* TODO: Allow non intenger nodes */
//PyObject* add_edge (stack *p) {
//    if (p->top != 2) fprintf (stderr, ">>> Usage: add_edge (<graph_name>,<number>,<number>).\n");
//    stack *first = getitem (0);
//    symrec *f = getsym (first->value.string);
//    if (f != NULL) {
//        PyObject* tuple = PyTuple_New (3);
//        PyTuple_SetItem (tuple, 0, f->value.var.data.obj->py_object);
//        PyTuple_SetItem (tuple, 2, PyInt_FromLong (p->value.number));
//        PyTuple_SetItem (tuple, 1, PyInt_FromLong (p->next->value.number));
//        PyObject_CallObject (nx_add_edge->py_object, tuple);
//    } else {
//        fprintf (stderr, "Graph %s not found.\n", first->value.string);
//    }
//    return NULL;
//}
//
//double order (stack *p) {
//    if (p->top != 0) fprintf (stderr, ">>> Usage: add_edge (<graph_name>).\n");
//    stack *first = getitem (0);
//    symrec *f = getsym (first->value.string);
//    if ( f != NULL ) {
//        PyObject* tuple = PyTuple_New (1);
//        PyTuple_SetItem (tuple, 0, f->value.var.data.obj->py_object);
//        PyObject* value = PyObject_CallObject (nx_order->py_object, tuple);
//        if (value) return PyInt_AsLong (value);
//    } else {
//        fprintf (stderr, "Graph %s not found.\n", first->value.string);
//        return 0;
//    }
//}
