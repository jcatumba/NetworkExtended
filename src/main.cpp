/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "networkx.h"
#include "ofMain.h"
#include "netextGui.h"
#include "ofAppGlutWindow.h"

extern PyObject* nxGraph;
extern PyObject* nxDiGraph;
extern PyObject* nxMultiGraph;
extern PyObject* nxMultiDiGraph;

//--------------------------------------------------------------
int main () {
	ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
    ofSetupOpenGL (&window, 1024, 768, OF_WINDOW);

    // Initializing app
    Py_Initialize ();
    init_networkx ();
	ofRunApp (new netextGui ()); // start the app

    // Finalizing
    Py_Finalize ();
}
