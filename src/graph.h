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

#include "ofMain.h"

class Node {
public:
    // Constructor
    Node ();

    // Methods
    void set (int, int); // Setup the node
    void draw (); // Draw the node
    void update (int, int); // Update the node
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
    void set (Node, Node); // Initialize the node
    void draw (); // Draw the edge
    void update (int, int); // Update the edge
    void update_source (Node);
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
    ofVec2f middleBezier;
    ofVec2f middleDraw;
    ofColor def_color;
    ofColor sel_color;
};

ofVec2f drawPoint (ofVec2f, ofVec2f, ofVec2f); // Get the point on the middle of the bezier curve
ofVec2f bezierPoint (ofVec2f, ofVec2f, ofVec2f); // get the bezier point according to the middle point of the curve

#endif // GRAPH_H
