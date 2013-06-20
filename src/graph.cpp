/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "graph.h"

//---------------------------
// Node specification
//---------------------------
Node::Node () {
    def_bgcolor.set (200, 200, 200);
    sel_bgcolor.set (100, 100, 200);
    def_bdcolor.set (100, 100, 100);
    sel_bdcolor.set (32, 32, 64);

    selected = false;
    center.set(0, 0);
    radius = 25;
}

void Node::set (int _xDest, int _yDest, Graph& graph) {
    center.set (_xDest, _yDest);

    // Add NetworkX node
    PyObject *tuple = PyTuple_New(2);
    PyTuple_SetItem (tuple, 0, graph.the_graph);
    PyTuple_SetItem (tuple, 1, PyInt_FromLong (graph.Nodes.size()-1));
    PyObject_CallObject (nx_add_node, tuple);

    // Add center properties (for visualization)
    PyObject *graph_node = load_attr (graph.the_graph, "node");
    PyObject *node_ptr = PyObject_GetItem(graph_node, PyInt_FromLong(graph.Nodes.size()-1));
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

void Node::update (int x, int y, Graph& graph, int position) {
    center.set (x, y);

    PyObject *graph_node = load_attr (graph.the_graph, "node");
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

//---------------------------
// Edge specification
//---------------------------
Edge::Edge () {
    def_color.set (100, 100, 100);
    sel_color.set (32, 32, 64);
    middleDraw.set (0, 0);
    midRad = 9;

    selected = false;
}

void Edge::set (Node _source, Node _target, int idsource, int idtarget, Graph& graph) {
    source = _source;
    target = _target;
    source_id = idsource;
    target_id = idtarget;
    middleDraw.set (source.center.getMiddle(target.center));

    // Add NetworkX edge
    PyObject *tuple = PyTuple_New(3);
    PyTuple_SetItem(tuple, 0, graph.the_graph);
    PyTuple_SetItem(tuple, 1, PyInt_FromLong(idsource));
    PyTuple_SetItem(tuple, 2, PyInt_FromLong(idtarget));
    PyObject_CallObject(nx_add_edge, tuple);
}

void Edge::draw (string graphType) {
    if (selected)
        ofSetColor (sel_color);
    else
        ofSetColor (def_color);
    ofNoFill ();
    //ofBezier (source.center.x, source.center.y, middleBezier.x, middleBezier.y, middleBezier.x, middleBezier.y, target.center.x, target.center.y);
    ofLine (source.center, target.center);
    ofCircle (middleDraw.x, middleDraw.y, midRad);
    // Draw arrow inside circle for Directed Graphs
    if (graphType == "DiGraph" || graphType == "MultiDiGraph") {
        double t = midRad / middleDraw.distance(target.center);
        ofVec2f head = (1 - t)*middleDraw + t*target.center;
        ofVec2f tail1 = head.rotate(120, middleDraw);
        ofVec2f tail2 = head.rotate(-240, middleDraw);
        head.rotate(120, middleDraw);
        ofLine (head, tail1);
        ofLine (head, tail2);
    }
}

void Edge::update (int x, int y) {
    middleDraw.set (x, y);
}

void Edge::update_source_id (int idsource) {
    source_id = idsource;
}

void Edge::update_source (Node _source) {
    source = _source;
    middleDraw.set (source.center.getMiddle(target.center));
}

void Edge::update_target_id (int idtarget) {
    target_id = idtarget;
}

void Edge::update_target (Node _target) {
    target = _target;
    middleDraw.set (source.center.getMiddle(target.center));
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

Graph::Graph () {
    graphType = "Graph";
    graphDensity = "0";
    numNodes = "0";
    numEdges = "0";
}

void Graph::set (PyObject *type) {
    the_graph = PyObject_CallObject(type, NULL);
}

void Graph::draw () {
    for (int i=0; i<Edges.size (); i++) {
        Edges[i].draw (graphType);
    }
    for (int i=0; i<Nodes.size (); i++) {
        Nodes[i].draw ();
    }
}

void Graph::save_graph (const char* filename) {
    PyObject_CallObject (nx_write_gml, PyTuple_Pack (2, the_graph, PyString_FromString(filename)));
}

void Graph::update_graphType (string newType) {
    graphType = newType;
    //TODO: Add functionality to change graph type on NetworkX
}

void Graph::update_graphDensity () {
    stringstream gd;
    gd << PyFloat_AsDouble(PyObject_CallObject(nx_density, PyTuple_Pack(1, the_graph)));
    graphDensity = gd.str();
}

void Graph::update_numNodes () {
    stringstream ss;
    ss << Nodes.size ();
    numNodes = ss.str();
}

void Graph::remove_node (int node, int position) {
    PyObject_CallObject (nx_remove_node, PyTuple_Pack (2, the_graph, PyInt_FromLong(node)));
    Nodes.erase (Nodes.begin () + position);
    update_numNodes ();
}

void Graph::update_numEdges () {
    stringstream ss;
    ss << Edges.size ();
    numEdges = ss.str();
}

void Graph::remove_edge (int source, int target, int position) {
    PyObject_CallObject (nx_remove_edge, PyTuple_Pack (3, the_graph, PyInt_FromLong(source), PyInt_FromLong(target)));
    Edges.erase (Edges.begin () + position);
    update_numEdges ();
}
