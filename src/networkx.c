/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkx.h"

// NX_objects definitions of NetworkX module, classes and methods

NX_object* load_networkx() {
    NX_object* nx_module = NULL;
    nx_module = (NX_object*)malloc(sizeof(NX_object));
    PyObject* nx_name = PyString_FromString("networkx");
    if (nx_module->py_object = PyImport_Import(nx_name)) {
        nx_module->name = "NetworkX";
        nx_module->parent = "Python";
        printf("NetworkX reference loaded.\n");
        return nx_module;
    } else {
        printf("NetworkX reference load failed.\n");
        return NULL;
    }
    Py_DECREF(nx_name);
}

NX_object* load_nx(NX_object *nxobject, const char* attr_name) {
    NX_object* pFun;
    pFun = (NX_object*)malloc(sizeof(NX_object));
    if (pFun->py_object = PyObject_GetAttrString(nxobject->py_object, attr_name)) {
        pFun->name = attr_name;
        pFun->parent = nxobject->name;
        //printf("Reference of %s at %s loaded.\n", pFun->name, nxobject->name);
        return pFun;
    } else {
        //printf("Reference of %s at %s load failed.\n", attr_name, nxobject->name);
        return NULL;
    }
}

void load_objects(NX_object *nx_module) {
    // Classes
    nxGraph = load_nx(nx_module, "Graph");
    nxDiGraph = load_nx(nx_module, "DiGraph");
    nxMultiGraph = load_nx(nx_module, "MultiGraph");
    nxMultiDiGraph = load_nx(nx_module, "MultiDiGraph");

    // Generic Methods
    //nx_pagerank = load_nx(nx_module, "pagerank");

    // Graph Methods
}
