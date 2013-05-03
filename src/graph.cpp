/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "graph.h"

Node::Node () {
    def_bgcolor.set (200, 200, 200);
    sel_bgcolor.set (100, 100, 200);
    def_bdcolor.set (100, 100, 100);
    sel_bdcolor.set (32, 32, 64);

    selected = false;
    center.set(0, 0);
    radius = 25;
}

void Node::set (int _xDest, int _yDest, PyObject *graph, int the_size) {
    center.set (_xDest, _yDest);

    // Add NetworkX node
    PyObject *tuple = PyTuple_New(2);
    PyTuple_SetItem (tuple, 0, graph);
    PyTuple_SetItem (tuple, 1, PyInt_FromLong (the_size));
    PyObject_CallObject (nx_add_node, tuple);

    // Add center properties (for visualization)
    PyObject *graph_node = load_attr (graph, "node");
    PyObject *node_ptr = PyObject_GetItem(graph_node, PyInt_FromLong(the_size));
    PyObject_SetItem(node_ptr, PyString_FromString("x"), PyInt_FromLong(_xDest));
    PyObject_SetItem(node_ptr, PyString_FromString("y"), PyInt_FromLong(_yDest));
}

void Node::draw () {
    if (selected)
        ofSetColor (sel_bgcolor);
    else
        ofSetColor (def_bgcolor);
    ofFill ();
    ofCircle (center.x, center.y, radius);
    if (selected)
        ofSetColor (sel_bdcolor);
    else
        ofSetColor (def_bdcolor);
    ofNoFill ();
    ofCircle (center.x, center.y, radius);
}

void Node::update (int x, int y, PyObject *graph, int position) {
    center.set (x, y);

    PyObject *graph_node = load_attr (graph, "node");
    PyObject *node_ptr = PyObject_GetItem(graph_node, PyInt_FromLong(position));
    PyObject_SetItem(node_ptr, PyString_FromString("x"), PyInt_FromLong(x));
    PyObject_SetItem(node_ptr, PyString_FromString("y"), PyInt_FromLong(y));
}

void Node::toggle_selected (void) {
    if (selected)
        selected = false;
    else
        selected = true;
}

bool Node::checkOver (int x, int y) {
    if (center.distance(ofVec2f (x, y)) < radius * 0.9) {
        return true;
    } else {
        return false;
    }
}

bool Node::testEqual (Node &comp) {
    return this == &comp;
}

Edge::Edge () {
    def_color.set (100, 100, 100);
    sel_color.set (32, 32, 64);
    middleBezier.set (0, 0);
    middleDraw.set (0, 0);
    midRad = 9;

    selected = false;
}

void Edge::set (Node _source, Node _target, int idsource, int idtarget, PyObject *graph) {
    source = _source;
    target = _target;
    source_id = idsource;
    target_id = idtarget;
    middleDraw.set ((source.center.x + target.center.x)/2, (source.center.y + target.center.y)/2);
    middleBezier = bezierPoint (source.center, middleDraw, target.center);

    // Add NetworkX edge
    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, graph);
    PyTuple_SetItem(tuple, 1, PyInt_FromLong(idsource));
    PyTuple_SetItem(tuple, 2, PyInt_FromLong(idtarget));
    PyObject_CallObject(nx_add_edge, tuple);
}

void Edge::draw () {
    if (selected)
        ofSetColor (sel_color);
    else
        ofSetColor (def_color);
    ofNoFill ();
    ofBezier (source.center.x, source.center.y, middleBezier.x, middleBezier.y, middleBezier.x, middleBezier.y, target.center.x, target.center.y);
    ofCircle (middleDraw.x, middleDraw.y, midRad);
}

void Edge::update (int x, int y) {
    middleDraw.set (x, y);
    middleBezier = bezierPoint (source.center, middleDraw, target.center);
}

void Edge::update_source_id (int idsource) {
    source_id = idsource;
}

void Edge::update_source (Node _source) {
    source = _source;
    middleDraw = drawPoint (source.center, middleBezier, target.center);
}

void Edge::update_target_id (int idtarget) {
    target_id = idtarget;
}

void Edge::update_target (Node _target) {
    target = _target;
    middleDraw = drawPoint (source.center, middleBezier, target.center);
}

void Edge::toggle_selected (void) {
    if (selected)
        selected = false;
    else
        selected = true;
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
