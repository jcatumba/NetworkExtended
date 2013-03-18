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
    bool checkOver (int, int); // Check if the mouse is over the node

    // Properties
    ofVec2f center;
    int radius;
    ofColor bgcolor;
    ofColor bdcolor;
};

class Edge {
public:
    // Constructor
    Edge ();

    // Methods
    void set (Node, Node, int, int); // Initialize the node
    void draw (); // Draw the edge
    void update (int, int); // Update the edge
    void update_source (Node);
    void update_target (Node);
    bool checkOver (int, int); // Check oif the mouse is over the edge

    // Properties
    Node source;
    Node target;
    int source_id;
    int target_id;
    int midRad;
    ofVec2f middleBezier;
    ofVec2f middleDraw;
    ofColor color;
};

ofVec2f drawPoint (ofVec2f, ofVec2f, ofVec2f); // Get the point on the middle of the bezier curve
ofVec2f bezierPoint (ofVec2f, ofVec2f, ofVec2f); // get the bezier point according to the middle point of the curve

#endif // GRAPH_H
