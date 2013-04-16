/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#pragma once

#include "ofxUI.h"
#include "graph.h"

class netextGui : public ofBaseApp {
	public:
		void setup ();
		void update ();
		void draw ();
		
		void keyPressed (int key);
		void keyReleased (int key);
		void mouseMoved (int x, int y);
		void mouseDragged (int x, int y, int button);
		void mousePressed (int x, int y, int button);
		void mouseReleased (int x, int y, int button);
		void windowResized (int w, int h);
		void dragEvent (ofDragInfo dragInfo);
		void gotMessage (ofMessage msg);

        vector<Node> Nodes; // Vector to save all nodes.
        vector<Edge> Edges; // Vector to sava all edges.
        int selectedNode = -1;
        int selectedEdge = -1;
        vector<int> selectedNodes;
        vector<int> selectedEdges;
        ofVec2f selectVi;
        ofVec2f selectVf;

    ofxUICanvas *gui;
    ofxUIDropDownList *ddl;
    void exit ();
    void guiEvent (ofxUIEventArgs &e);
};
