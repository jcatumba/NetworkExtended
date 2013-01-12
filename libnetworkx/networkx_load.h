/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef NETWORKX_LOAD_H
#define NETWORKX_LOAD_H

typedef int bool;
enum { false, true };

PyObject* load_nx(PyObject* object, const char* attr_name, bool* flag);

#endif //NETWORKX_LOAD_H
