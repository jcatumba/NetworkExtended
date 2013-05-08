/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef GRAPH_H
#define GRAPH_H

#include "networkx.h"
#include "netevo.h"
#include "ofMain.h"

class Node {
public:
    // Constructor
    Node ();

    // Methods
    void set (int, int, PyObject*, int); // Setup the node
    void draw (); // Draw the node
    void update (int, int, PyObject*, int); // Update the node
    void toggle_selected (void);
    bool checkOver (int, int); // Check if the mouse is over the node
    bool testEqual (Node &);

    // Properties
    bool selected;
    ofVec2f center;
    int radius;
    ofColor def_bgcolor;
    ofColor sel_bgcolor;
    ofColor def_bdcolor;
    ofColor sel_bdcolor;
};

class Edge {
public:
    // Constructor
    Edge ();

    // Methods
    void set (Node, Node, int, int, PyObject*); // Initialize the node
    void draw (); // Draw the edge
    void update (int, int); // Update the edge
    void update_source_id (int);
    void update_source (Node);
    void update_target_id (int);
    void update_target (Node);
    void toggle_selected (void);
    bool checkOver (int, int); // Check oif the mouse is over the edge

    // Properties
    bool selected;
    Node source;
    Node target;
    int source_id;
    int target_id;
    int midRad;
    ofVec2f middleDraw;
    ofColor def_color;
    ofColor sel_color;
};

#endif // GRAPH_H