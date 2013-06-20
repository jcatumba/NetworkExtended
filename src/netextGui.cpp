/*===================================================================
 * NetworkExtended
 * Copyright (C) 2012 Jorge Catumba Ruiz <jorgerev90@gmail.com>
 * Universidad Nacional de Colombia, Colombia
 * ------------------------------------------------------------------
 * This software is licensed under the terms of the GPL v0.3 for
 * more information about the license see the license.txt file.
 * ================================================================*/

#include "netextGui.h"

//--------------------------------------------------------------
void netextGui::setup (){
    // App specific information
    ofSetWindowTitle ("NetworkExtended");
    ofTrueTypeFont::setGlobalDpi (72);
    verdana14.loadFont ("GUI/verdana.ttf", 14, true, true);
    //ofBackgroundGradient (ofColor (255, 255, 255), ofColor (0, 0, 0), OF_GRADIENT_CIRCULAR);

    // Graph initialization TODO: Ask user for graphType required
    my_graph.set (nxGraph);

    // Variable initialization
    mouse_dragged = false;

    //ofBackground (32, 32, 32);
    ofEnableSmoothing ();
    //float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320;
    //gui = new ofxUICanvas ();

    //gui->setFont ("GUI/verdana.ttf");
    //gui->addLabel ("NetworkExtended", OFX_UI_FONT_LARGE);
    //gui->addSpacer ();
    /*gui->addLabel (graphType, OFX_UI_FONT_MEDIUM);
    gui->addSlider ("Background value", 0.0, 255.0, 100.0);
    gui->addToggle ("Fullscreen", false);
    gui->addLabel ("Configuration", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();
    gui->addLabel ("File", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();
    gui->addLabel ("Graph Algorithms", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();
    gui->addLabel ("Node properties", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();*/

    //vector<string> names;
    //names.push_back ("Graph");
    //names.push_back ("DiGraph");
    //names.push_back ("MultiGraph");
    //names.push_back ("MultiDiGraph");
    //ddl = new ofxUIDropDownList (length-xInit, "Graph Type", names, OFX_UI_FONT_MEDIUM);
    //ddl->setAllowMultiple (false);
    //gui->addWidgetDown (ddl);

    /*gui->addSpacer ();
    gui->addLabel ("Edge properties", OFX_UI_FONT_MEDIUM);*/

    //gui->autoSizeToFitWidgets ();
    //ofAddListener (gui->newGUIEvent, this, &netextGui::guiEvent);
    //gui->loadSettings ("GUI/guiSettings.xml");
}

//--------------------------------------------------------------
void netextGui::update (){
}

//--------------------------------------------------------------
void netextGui::draw (){
    // Draw the graph
    my_graph.draw ();

    // Draw the info box
    ofSetColor (211,211,211);
    ofFill ();
    ofRect (0,ofGetHeight ()-90,ofGetWidth (),90);

    // Put the contents of info box
    ofSetColor (0);
    /*verdana14.drawString (my_graph.graphType, 30, ofGetHeight ()-70);
    verdana14.drawString (my_graph.numNodes, 30, ofGetHeight ()-53);
    verdana14.drawString ("Node (s)", 35 + verdana14.stringWidth (my_graph.numNodes), ofGetHeight ()-53);
    verdana14.drawString (my_graph.numEdges, 30, ofGetHeight ()-36);
    verdana14.drawString ("Edge (s)", 35 + verdana14.stringWidth (my_graph.numEdges), ofGetHeight ()-36);
    verdana14.drawString ("Density: ", 30, ofGetHeight ()-19);
    verdana14.drawString (my_graph.graphDensity, 35 + verdana14.stringWidth ("Density: "), ofGetHeight ()-19);*/
}

//--------------------------------------------------------------
void netextGui::exit (){
    //gui->saveSettings ("GUI/guiSettings.xml");
    //delete gui;
}

//--------------------------------------------------------------
/*void netextGui::guiEvent (ofxUIEventArgs &e){
    string name = e.widget->getName ();

    if (name  == "Background value") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        ofBackground (slider->getScaledValue ());
    } else if (name == "Fullscreen") {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen (toggle->getValue ());
    } else if (name == "Graph Type") {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected ();
        for (int i=0; i< selected.size (); i++) {
            my_graph.update_graphType (selected[i]->getName ());
        }
    }
}*/

//--------------------------------------------------------------
void netextGui::keyPressed (int key){
    //cout << "Key pressed is: " << key << endl;
    // Get the pressed key
    switch (key) {
        case 's': {
            my_graph.save_graph("netext_graph.gml");
            break;
        }
        case 'f':
            ofToggleFullscreen ();
            break;
        case 'p':
            //gui->setDrawWidgetPadding (true);
            break;
        case 'P':
            //gui->setDrawWidgetPadding (false);
            break;
        case 127: {
            // Remove selected;
            vector<int> selectedI;
            for (int i=0; i<my_graph.Edges.size (); i++) {
                if (my_graph.Edges[i].selected) {
                    selectedI.push_back (i);
                }
            }
            for (int i=0;i<selectedI.size (); i++) {
                Edge edge_selected = my_graph.Edges[selectedI[i]];
                my_graph.remove_edge (edge_selected.source_id, edge_selected.target_id, selectedI[i]-i);
            }
            selectedI.clear ();
            for (int i=0; i<my_graph.Nodes.size (); i++) {
                if (my_graph.Nodes[i].selected) {
                    selectedI.push_back (i);
                }
            }
            for (int i=0; i<selectedI.size (); i++) {
                my_graph.remove_node (selectedI[i], selectedI[i]-i);
                for (int j=0; j<my_graph.Edges.size (); j++) {
                    if (my_graph.Edges[j].source_id > selectedI[i])
                        my_graph.Edges[j].source_id -= 1;
                    if (my_graph.Edges[j].target_id > selectedI[i])
                        my_graph.Edges[j].target_id -= 1;
                }
            }
            break;
        }
        default:
            break;
    }
}

//--------------------------------------------------------------
void netextGui::keyReleased (int key){

}

//--------------------------------------------------------------
void netextGui::mouseMoved (int x, int y){

}

//--------------------------------------------------------------
void netextGui::mouseDragged (int x, int y, int button){
    mouse_dragged = true;

    // Manipulate a selected node
    if (selectedNode > -1) {
        if (button == 0) {
            my_graph.Nodes[selectedNode].update (ofGetMouseX (), ofGetMouseY (), my_graph, selectedNode);
            for (int i=0; i<my_graph.Edges.size (); i++) {
                if (my_graph.Edges[i].source_id == selectedNode) {
                    my_graph.Edges[i].update_source (my_graph.Nodes[selectedNode]);
                } else if (my_graph.Edges[i].target_id == selectedNode) {
                    my_graph.Edges[i].update_target (my_graph.Nodes[selectedNode]);
                }
            }
        } else if (button == 2) {
            // Nothing
        }
    }

    // Manipulate a selected edge
    if (selectedEdge > -1) {
        //Edges[selectedEdge].update (ofGetMouseX (), ofGetMouseY ());
    }

    // Declare final coordinates of selection if not edge nor node was selected
    if (selectedNode == -1 && selectedEdge == -1) {
        selectVf.set (ofGetMouseX (), ofGetMouseY ());
    }
}

//--------------------------------------------------------------
void netextGui::mousePressed (int x, int y, int button){
    bool nodePressed = false;
    bool edgePressed = false;

    // Actions on mouse click event (0 = left, 2 = right)
    if (button == 0) {
        // Detect if a node was clicked
        for (int i=0; i<my_graph.Nodes.size (); i++) {
            if (my_graph.Nodes[i].checkOver (x, y)) {
                nodePressed = true;
                selectedNode = i;
                //my_graph.Nodes[i].toggle_selected ();
                break;
            }
        }
        // Detect if an edge was clicked
        for (int i=0; i<my_graph.Edges.size (); i++) {
            if (my_graph.Edges[i].checkOver (x, y)) {
                edgePressed = true;
                selectedEdge = i;
                //Edges[i].toggle_selected ();
                break;
            }
        }
        // Declare the initial coordinates of the node multi-selection mode
        if (!nodePressed && !edgePressed) {
            selectVi.set (ofGetMouseX (), ofGetMouseY ());
        }
    } else if (button == 2) {
        // Detect a right-clicked node
        for (int i=0; i<my_graph.Nodes.size (); i++) {
            if (my_graph.Nodes[i].checkOver (x, y)) {
                nodePressed = true;
                selectedNode = i;
                break;
            }
        }
        // Detect a right-clicked edge
        for (int i=0; i>my_graph.Edges.size (); i++) {
            if (my_graph.Edges[i].checkOver (x, y)) {
                edgePressed = true;
                selectedEdge = i;
                break;
            }
        }
    }
}

//--------------------------------------------------------------
void netextGui::mouseReleased (int x, int y, int button){
    // Detect if a node was selected
    if (selectedNode > -1) {
        if (button == 0) {
            if (mouse_dragged) {
                //empty
            } else {
                my_graph.Nodes[selectedNode].toggle_selected ();
                for (int i=0; i<my_graph.Edges.size (); i++) {
                    if (selectedNode == my_graph.Edges[i].source_id || selectedNode == my_graph.Edges[i].target_id) {
                        my_graph.Edges[i].toggle_selected ();
                    }
                }
                // TODO: Active properties edition
            }
        }
        if (button == 2) {
            // Create edge on mouse release over a node
            for (int i=0; i<my_graph.Nodes.size (); i++) {
                if (my_graph.Nodes[i].checkOver (ofGetMouseX (), ofGetMouseY ()) && i != selectedNode) {
                    // Add edge
                    my_graph.Edges.push_back (Edge ());
                    // Set edge
                    my_graph.Edges.back ().set (my_graph.Nodes[selectedNode], my_graph.Nodes[i], selectedNode, i, my_graph);

                    // Update number of edges on screen
                    my_graph.update_numEdges ();
                    // Update density of graph
                    my_graph.update_graphDensity ();
                }
            }
        }
    }

    // Detect if an edge was selected
    if (selectedEdge > -1) {
        if (button == 0) {
            if (mouse_dragged) {
                //empty
            } else {
                my_graph.Edges[selectedEdge].toggle_selected ();
                // TODO: Active properties edition
            }
        }
    }

    if (selectedNode == -1 && selectedEdge == -1) {
        if (button == 0) {
            if (mouse_dragged) {
                // Select multiple nodes
                if (selectVi.x > selectVf.x) {
                    float pass = selectVi.x;
                    selectVi.x = selectVf.x;
                    selectVf.x = pass;
                }
                if (selectVi.y > selectVf.y) {
                    float pass = selectVi.y;
                    selectVi.y = selectVf.y;
                    selectVf.y = pass;
                }
                for (int  i=0; i<my_graph.Nodes.size (); i++) {
                    if (selectVi.x <= my_graph.Nodes[i].center.x && my_graph.Nodes[i].center.x <= selectVf.x && selectVi.y <= my_graph.Nodes[i].center.y && my_graph.Nodes[i].center.y <= selectVf.y) {
                        my_graph.Nodes[i].toggle_selected ();
                        for (int j=0; j<my_graph.Edges.size (); j++) {
                            if (i == my_graph.Edges[j].source_id || i == my_graph.Edges[j].target_id) {
                                if (!my_graph.Edges[j].selected)
                                    my_graph.Edges[j].toggle_selected ();
                            }
                        }
                    }
                }
            } else {
                // Add node
                my_graph.Nodes.push_back (Node ());
                // Set the node properties
                my_graph.Nodes.back ().set (x, y, my_graph);

                // Update number of nodes on screen
                my_graph.update_numNodes ();
                // Update density of graph
                my_graph.update_graphDensity ();
            }
        }
    }

    // Forget the selected node or edge and drag of mouse
    selectedNode = -1;
    selectedEdge = -1;
    mouse_dragged = false;
}

//--------------------------------------------------------------
void netextGui::windowResized (int w, int h){

}

//--------------------------------------------------------------
void netextGui::gotMessage (ofMessage msg){

}

//--------------------------------------------------------------
void netextGui::dragEvent (ofDragInfo dragInfo){ 

}
