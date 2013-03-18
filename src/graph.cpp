#include "graph.h"

Node::Node () {
    bgcolor.set (200, 200, 200);
    bdcolor.set (64, 64, 64);

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

Edge::Edge () {
    color.set (64, 64, 64);
    middleBezier.set (0, 0);
    middleDraw.set (0, 0);
    midRad = 9;
}

void Edge::set (Node _source, Node _target, int idsource, int idtarget) {
    source = _source;
    target = _target;
    source_id = idsource;
    target_id = idtarget;
    middleDraw.set ((source.center.x + target.center.x)/2, (source.center.y + target.center.y)/2);
    middleBezier = bezierPoint (source.center, middleDraw, target.center);
}

void Edge::draw () {
    ofSetColor (color);
    ofNoFill ();
    ofBezier (source.center.x, source.center.y, middleBezier.x, middleBezier.y, middleBezier.x, middleBezier.y, target.center.x, target.center.y);
    ofCircle (middleDraw.x, middleDraw.y, midRad);
}

void Edge::update (int x, int y) {
    middleDraw.set (x, y);
    middleBezier = bezierPoint (source.center, middleDraw, target.center);
}

void Edge::update_source (Node _source) {
    source = _source;
    middleDraw = drawPoint (source.center, middleBezier, target.center);
}

void Edge::update_target (Node _target) {
    target = _target;
    middleDraw = drawPoint (source.center, middleBezier, target.center);
}

bool Edge::checkOver (int x, int y) {
    if (middleDraw.distance(ofVec2f (x, y)) < midRad * 0.9) {
        return true;
    } else {
        return false;
    }
}

ofVec2f drawPoint (ofVec2f p0, ofVec2f p1, ofVec2f p2) {
    ofVec2f pd = operator*(0.125, p0) + operator*(6*0.125, p1) + operator*(0.125, p2);
    return pd;
}

ofVec2f bezierPoint (ofVec2f p0, ofVec2f pd, ofVec2f p2) {
    ofVec2f p1 =  operator*(8.0/6.0, pd - operator*(0.125, p0) - operator*(0.125, p2)); 
    return p1;
}
