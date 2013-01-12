/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include <Python.h>
#include "libnetworkx/networkx_load.h"

void main(int argc, char** argv)
{
    bool nxmod_flag;
    PyObject* nx_module, * nx_name;
    
    // Intialization and load reference to NetworkX library.
    Py_SetProgramName("NetworkExtended");
    Py_Initialize();
    nx_name = PyString_FromString("networkx");
    if (nx_module = PyImport_Import(nx_name)) {
        nxmod_flag = true;
    } else {
        nxmod_flag = false;
    }
    Py_DECREF(nx_name);
    if (nxmod_flag) printf("NetworkX reference loaded. \n");

    // Loading references to basic NX classes.
    bool graph_flag;
    PyObject* nxGraph = load_nx(nx_module, "Graph", &graph_flag);
    if (graph_flag) printf("Graph reference loaded.\n");
    bool digraph_flag;
    PyObject* nxDiGraph = load_nx(nx_module, "DiGraph", &digraph_flag);
    if (digraph_flag) printf("DiGraph reference loaded.\n");
    bool multigraph_flag;
    PyObject* nxMultiGraph = load_nx(nx_module, "MultiGraph", &multigraph_flag);
    if (multigraph_flag) printf("MultiGraph reference loaded.\n");
    bool multidigraph_flag;
    PyObject* nxMultiDiGraph = load_nx(nx_module, "MultiDiGraph", &multidigraph_flag);
    if (multidigraph_flag) printf("MultiDiGraph reference loaded.\n");
    
    // Loading references to NX general methods.
    bool pagerank_flag;
    PyObject* nxG_pagerank = load_nx(nx_module, "pagerank", &pagerank_flag);
    if (pagerank_flag) printf("pagerank for Graph loaded.\n");
    bool pwp_flag;
    /*PyObject* nxG_pwprank = load_nx(nx_module, "pwp", &pwp_flag);
    if (pwp_flag) printf("pwp for Graph loaded.\n");*/
    
    // Loading references to NX methods of basic classes.
    bool add_node_flag;
    PyObject* nxG_add_node = load_nx(nxGraph, "add_node", &add_node_flag);
    if (add_node_flag) printf("add_node for Graph loaded.\n");
    bool order_flag;
    PyObject* nxG_order = load_nx(nxGraph, "order", &order_flag);
    if (order_flag) printf("order for Graph loaded.\n");
    
    // Creating two references to instances of Graph.
    PyObject* nxG;
    if (nxG = PyObject_CallObject(nxGraph, NULL)) printf("nxG created.\n");
    PyObject* nxH;
    if (nxH = PyObject_CallObject(nxGraph, NULL)) printf("nxH created.\n");
    
    // Adding nodes to graphs and check size of them.
    PyObject* pAttrTuple1 = PyTuple_New(2);
    PyTuple_SetItem(pAttrTuple1, 0, nxG);
    PyTuple_SetItem(pAttrTuple1, 1, PyInt_FromLong(1));
    PyObject* pAttrTuple2 = PyTuple_New(2);
    PyTuple_SetItem(pAttrTuple2, 0, nxH);
    PyTuple_SetItem(pAttrTuple2, 1, PyInt_FromLong(2));
    PyObject* pAttrTuple3 = PyTuple_New(2);
    PyTuple_SetItem(pAttrTuple3, 0, nxG);
    PyTuple_SetItem(pAttrTuple3, 1, PyInt_FromLong(3));
    
    PyObject_CallObject(nxG_add_node, pAttrTuple1);
    PyObject_CallObject(nxG_add_node, pAttrTuple2);
    PyObject_CallObject(nxG_add_node, pAttrTuple3);
    
    PyObject* pGraphTuple1 = PyTuple_New(1);
    PyTuple_SetItem(pGraphTuple1, 0, nxG);
    PyObject* pGraphTuple2 = PyTuple_New(1);
    PyTuple_SetItem(pGraphTuple2, 0, nxH);
    
    PyObject* nodes1 = PyObject_CallObject(nxG_order, pGraphTuple1);
    if (nodes1) printf("nxG has %ld nodes.\n", PyInt_AsLong(nodes1));
    PyObject* nxPRdict = PyObject_CallObject(nxG_pagerank, pGraphTuple1);
    if (nxPRdict) printf("nxG pagerank dict has %d items.\n", PyDict_Size(nxPRdict));
    PyObject* nodes2 = PyObject_CallObject(nxG_order, pGraphTuple2);
    if (nodes2) printf("nxH has %ld nodes.\n", PyInt_AsLong(nodes2));
    
    /*Py_XDECREF(nxG_add_node);
    Py_XDECREF(pAttrTuple1);
    Py_XDECREF(pAttrTuple2);
    Py_XDECREF(pAttrTuple3);
    Py_XDECREF(pGraphTuple1);
    Py_XDECREF(pGraphTuple1);
    Py_XDECREF(nxG);
    Py_XDECREF(nxH);*/
    
    Py_Finalize();
}
