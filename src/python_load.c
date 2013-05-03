/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "python_load.h"

PyObject* load_module (const char *module_name) {
    PyObject* PyModule = NULL;
    PyModule = (PyObject*) malloc (sizeof(PyObject));
    PyModule = PyImport_ImportModuleEx (module_name, NULL, NULL, NULL);
    return PyModule;
}

PyObject* load_attr (PyObject *object, const char* attr_name) {
    PyObject* PyAttr;
    PyAttr = (PyObject*) malloc (sizeof (PyObject));
    PyAttr = PyObject_GetAttrString (object, attr_name);
    return PyAttr;
}
