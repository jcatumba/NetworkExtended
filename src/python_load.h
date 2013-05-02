/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef PYTHON_LOAD_H
#define PYTHON_LOAD_H

#include <Python.h>

#ifdef __cplusplus
extern "C" {
#endif

PyObject* load_module (const char*);
PyObject* load_attr (PyObject*, const char*);

#ifdef __cplusplus
}
#endif

#endif
