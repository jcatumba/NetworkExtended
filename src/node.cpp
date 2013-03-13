#include "node.h"

Node::Node () {
    // Set the initial color
    color.set (ofRandom(255), ofRandom(255), ofRandom(255));

    // Default radius
    x = ofRandom (ofGetWindowWidth ());
    y = ofRandom (ofGetWindowHeight ());
    radius = 30;
}

void Node::moveTo (int _xDest, int _yDest) {
    x += (_xDest - x)*0.1;
    y += (_yDest - y)*0.1;
}

void Node::draw () {
    ofSetColor (color);
    ofFill ();
    ofCircle (x, y, radius);
}
