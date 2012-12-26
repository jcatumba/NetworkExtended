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
    PyObject* nx_module, * nx_dict, * expression;

    //We execute a simple command in the Python interpreter...
    Py_Initialize();
    //PyRun_SimpleString("print(\"Hello\\nWorld\")");

    //Reference to the main module
    //nx_module = PyImport_AddModule("networkx");
    nx_module = PyImport_ImportModule("networkx");
    //Main's dictionary and its copy
    nx_dict = PyModule_GetDict(nx_module);
    if (PyDict_Check(nx_dict)){
        printf("Its a Dict!\n");
    } else {
        printf("Its not a Dict!\n");
    }
    //Evaluation of functions
    //expression = PyDict_GetItemString(nx_dict, "print");
    //PyObject_CallFunction(expression, "s", "Hello again\n");
    //PyRun_SimpleString("import networkx");
    PyRun_SimpleString("G = networkx.DiGraph()");
    PyRun_SimpleString("print G.edges()");
    Py_Finalize();
}
