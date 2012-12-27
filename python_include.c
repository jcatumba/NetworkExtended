/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <assert.h>

void main(int argc, char** argv)
{
    int i;
    PyObject* nx_module, * pFunc, *pNXName, * pNodes, * pNodesTuple;
    PyObject* pObject, * graphNodes, * output, * pInt, * pItem;

    Py_SetProgramName("NetworkExtended");
    Py_Initialize();
    pNXName = PyString_FromString("networkx");
    nx_module = PyImport_Import(pNXName);
    Py_DECREF(pNXName);

    if (nx_module != NULL) {
        // Obteniendo nombre de la función
        pFunc = PyObject_GetAttrString(nx_module, "Graph");

        if (pFunc && PyCallable_Check(pFunc)) {
            /*pNodes = PyList_New(4);
            for (i=0;i<4;i++){
                PyObject* pTuple = PyTuple_New(2);
                PyTuple_SetItem(pTuple, 0, PyInt_FromLong(i));
                PyTuple_SetItem(pTuple, 1, PyInt_FromLong(i+1));
                PyList_Insert(pNodes, i, PyInt_FromLong(i));
                Py_DECREF(pTuple);
            }
            pNodesTuple = PyTuple_New(1);
            PyTuple_SetItem(pNodesTuple, 0, pNodes);*/
            pObject = PyObject_CallObject(pFunc, NULL);

            if (pObject != NULL) {
                printf("Object created succesfully.\n");
                graphNodes = PyObject_GetAttrString(pObject, "add_node");
                if (graphNodes && PyCallable_Check(graphNodes)) {
                    /*pNodes = PyList_New(4);
                    for (i=0;i<4;i++) {
                        PyList_Insert(pNodes, i, PyInt_FromLong(i));
                        pItem = PyList_GetItem(pNodes, i);
                    }
                    pNodesTuple = PyTuple_New(1);
                    PyTuple_SetItem(pNodesTuple, 0, pNodes);
                    if (PyTuple_Check(pNodesTuple)) printf("Its ok.\n");*/
                    pNodesTuple = PyTuple_New(1);
                    PyTuple_SetItem(pNodesTuple, 0, PyInt_FromLong(2));
                    PyObject_CallObject(graphNodes, pNodesTuple);

                    if (output != NULL) {
                        //if (PyList_Check(output)) printf("There are %i nodes.\n", PyList_Size(output));
                        printf("Graph created.\n");
                    } else {
                        Py_DECREF(pNodesTuple);
                        Py_DECREF(pNodes);
                        Py_DECREF(graphNodes);
                        Py_DECREF(pObject);
                        PyErr_Print();
                        fprintf(stderr, "Call failed.\n");
                    }
                    //printf("Object is callable.\n");
                }
                Py_DECREF(pObject);
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(nx_module);
                PyErr_Print();
                fprintf(stderr, "Call failed.\n");
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find funcion \"%s\".\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(nx_module);

    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\".\n", argv[1]);
    }

    Py_Finalize();
}
