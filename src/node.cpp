#include "node.h"

Node::Node () {
    // Set the initial color
    bgcolor.set (200, 200, 200);
    bdcolor.set (64, 64, 64);

    // Default radius
    //x = ofRandom (ofGetWindowWidth ());
    center.set(0, 0);
    radius = 25;
}

void Node::set (int _xDest, int _yDest) {
    center.set (_xDest, _yDest);
}

void Node::draw () {
    ofSetColor (bgcolor);
    ofFill ();
    ofCircle (center.x, center.y, radius);
    ofSetColor (bdcolor);
    ofNoFill ();
    ofCircle (center.x, center.y, radius);
}

void Node::update (int x, int y) {
    center.set (x, y);
}

bool Node::checkOver (int x, int y) {
    if (center.distance(ofVec2f (x, y)) < radius * 0.9) {
        return true;
    } else {
        return false;
    }
}
