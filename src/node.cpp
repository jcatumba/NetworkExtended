#include "node.h"

Node::Node () {
    // Set the initial color
    bgcolor.set (200, 200, 200);
    bdcolor.set (64, 64, 64);

    // Default radius
    //x = ofRandom (ofGetWindowWidth ());
    x = 0;
    //y = ofRandom (ofGetWindowHeight ());
    y = 0;
    radius = 30;
}

void Node::set (int _xDest, int _yDest) {
    x = _xDest;
    y = _yDest;
}

void Node::draw () {
    ofSetColor (bgcolor);
    ofFill ();
    ofCircle (x, y, radius);
    ofSetColor (bdcolor);
    ofNoFill ();
    ofCircle (x, y, radius);
}
