#pragma once

#include "node.h"

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
        int selectedNode = -1;

    ofxUICanvas *gui;
    ofxUIDropDownList *ddl;
    void exit ();
    void guiEvent (ofxUIEventArgs &e);
};
