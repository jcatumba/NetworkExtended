#ifndef NODE_H
#define NODE_H

#include "ofMain.h"
#include "ofxUI.h"

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

#endif // NODE_H
