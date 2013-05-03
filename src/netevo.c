/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "netevo.h"

// Loading NetEvo-Py Functions
//
void init_netevo () {
    PyObject *ne_module;
    if((ne_module = load_module ("netevo")))
        load_ne_objects (ne_module);
    else
        printf ("Load of NetEvo-Py failed.\n");
}

void load_ne_objects (PyObject *parent) {
    // TODO
}
