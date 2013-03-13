#ifndef ball_h
#define ball_h

#include "ofMain.h"

class Node {
public:
    // Constructor
    Node ();

    // Methods
    void set (int, int);
    void draw ();

    // Properties
    int x;
    int y;
    int radius;
    ofColor bgcolor;
    ofColor bdcolor;
};

#endif
