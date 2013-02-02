/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef NETWORKX_H
#define NETWORKX_H

#include <Python.h>

typedef int bool;
enum { false, true };

typedef struct {
    const char* name;
    const char* parent;
    PyObject* py_object;
} NX_object;

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

NX_object* load_nx(NX_object *nxobject, const char* attr_name);
NX_object* load_networkx();
void load_objects(NX_object *nxobj);

#endif //NETWORKX_H
