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

NX_object* load_nx(NX_object *nxobject, const char* attr_name);
NX_object* load_networkx();
void load_objects(NX_object *nxobj);

#endif //NETWORKX_H
