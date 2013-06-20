/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#ifndef GRAPH_H
#define GRAPH_H

#include "networkx.h"
#include "netevo.h"
#include "ofMain.h"

class Graph;

class Node {
public:
    // Constructor
    Node ();

    // Methods
    void set (int, int, Graph&); // Setup the node
    void draw (); // Draw the node
    void update (int, int, Graph&, int); // Update the node
    void toggle_selected (void);
    bool checkOver (int, int); // Check if the mouse is over the node
    bool testEqual (Node &);

    // Properties
    bool selected;
    ofVec2f center;
    int radius;
    ofColor def_bgcolor;
    ofColor sel_bgcolor;
    ofColor def_bdcolor;
    ofColor sel_bdcolor;
};

class Edge {
public:
    // Constructor
    Edge ();

    // Methods
    void set (Node, Node, int, int, Graph&); // Setup the edge
    void draw (string); // Draw the edge
    void update (int, int); // Update the edge
    void update_source_id (int);
    void update_source (Node);
    void update_target_id (int);
    void update_target (Node);
    void toggle_selected (void);
    bool checkOver (int, int); // Check if the mouse is over the edge

    // Properties
    bool selected;
    Node source;
    Node target;
    int source_id;
    int target_id;
    int midRad;
    ofVec2f middleDraw;
    ofColor def_color;
    ofColor sel_color;
};

class Graph {
PyObject *the_graph;
friend class Node;
friend class Edge;
public:
    // Constructor
    Graph ();

    // Methods
    void set (PyObject*); // Initialize the graph
    void draw (); // draw Nodes and edges of graph
    void save_graph (const char*); // save the graph to a gml format
    void update_graphType (string);
    void update_graphDensity ();
    void update_numNodes ();
    void remove_node (int, int);
    void update_numEdges ();
    void remove_edge (int, int, int);
    
    // Properties
    string graphType;
    string graphDensity;
    string numNodes;
    string numEdges;
    vector<Node> Nodes;
    vector<Edge> Edges;
};

#endif // GRAPH_H
