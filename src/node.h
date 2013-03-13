#ifndef ball_h
#define ball_h

#include "ofMain.h"

class Node {
public:
    // Constructor
    Node ();

    // Methods
    void moveTo (int, int);
    void draw ();

    // Properties
    int x;
    int y;
    int radius;
    ofColor color;
};

#endif
