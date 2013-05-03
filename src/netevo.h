/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef NETEVO_H
#define NETEVO_H

#include "python_load.h"

#ifdef __cplusplus
extern "C" {
#endif

// Loading NetEvo-Py functions
//
void init_netevo (void);
void load_ne_objects (PyObject*);

#ifdef __cplusplus
}
#endif

#endif //NETEVO_H
