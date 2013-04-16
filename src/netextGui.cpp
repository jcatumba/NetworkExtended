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
    ofSetWindowTitle("NetworkExtended");
    ofBackgroundGradient (ofColor (255, 255, 255), ofColor (0, 0, 0), OF_GRADIENT_CIRCULAR);

    //Variable initialización
    mouse_dragged = false;

    //ofBackground (32, 32, 32);
    ofEnableSmoothing ();
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320;
    //gui = new ofxUICanvas ();

    /*gui->setFont ("GUI/mono.ttf");
    gui->addLabel ("NetworkExtended", OFX_UI_FONT_LARGE);
    gui->addSpacer ();
    gui->addSlider ("Background value", 0.0, 255.0, 100.0);
    gui->addToggle ("Fullscreen", false);
    gui->addLabel ("Configuration", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();
    gui->addLabel ("File", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();
    gui->addLabel ("Graph Algorithms", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();
    gui->addLabel ("Node properties", OFX_UI_FONT_MEDIUM);
    gui->addSpacer ();

    vector<string> names;
    names.push_back("One");
    names.push_back("Two");
    names.push_back("Three");
    ddl = new ofxUIDropDownList (length-xInit, "Dynamic Drop Down", names, OFX_UI_FONT_MEDIUM);
    ddl->setAllowMultiple (true);
    gui->addWidgetDown (ddl);

    gui->addSpacer ();
    gui->addLabel ("Edge properties", OFX_UI_FONT_MEDIUM);

    gui->autoSizeToFitWidgets ();
    ofAddListener (gui->newGUIEvent, this, &netextGui::guiEvent);
    gui->loadSettings ("GUI/guiSettings.xml");*/
}

//--------------------------------------------------------------
void netextGui::update (){
}

//--------------------------------------------------------------
void netextGui::draw (){
    for (int i=0; i<Edges.size (); i++) {
        Edges[i].draw ();
    }
    for (int i=0; i<Nodes.size (); i++) {
        Nodes[i].draw ();
    }
}

//--------------------------------------------------------------
void netextGui::removeSelected (void) {
    //
}

//--------------------------------------------------------------
void netextGui::exit (){
    gui->saveSettings ("GUI/guiSettings.xml");
    delete gui;
}

//--------------------------------------------------------------
void netextGui::guiEvent (ofxUIEventArgs &e){
    string name = e.widget->getName ();

    if (name  == "Background value") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        ofBackground (slider->getScaledValue ());
    } else if (name == "Fullscreen") {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen (toggle->getValue ());
    } else if (name == "Dynamic Drop Down") {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected();
        for (int i=0; i< selected.size(); i++) {
            cout << "SELECTED: " << selected[i]->getName() << endl;
        }
    }
}

//--------------------------------------------------------------
void netextGui::keyPressed (int key){
    //cout << "Key pressed is: " << key << endl;
    // Get the pressed key
    switch (key) {
        case 'f':
            ofToggleFullscreen ();
            break;
        case 'p':
            gui->setDrawWidgetPadding (true);
            break;
        case 'P':
            gui->setDrawWidgetPadding (false);
            break;
        case 127:
            //remove_selected ();
            break;
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
            Nodes[selectedNode].update(ofGetMouseX(), ofGetMouseY());
            for (int i=0; i<Edges.size(); i++) {
                if (Edges[i].source_id == selectedNode) {
                    Edges[i].update_source (Nodes[selectedNode]);
                } else if (Edges[i].target_id == selectedNode) {
                    Edges[i].update_target (Nodes[selectedNode]);
                }
            }
        } else if (button == 2) {
            // Nothing
        }
    }

    // Manipulate a selected edge
    if (selectedEdge > -1) {
        Edges[selectedEdge].update(ofGetMouseX(), ofGetMouseY());
    }

    // Declare final coordinates of selection if not edge nor node was selected
    if (selectedNode == -1 && selectedEdge == -1) {
        selectVf.set(ofGetMouseX(), ofGetMouseY());
    }
}

//--------------------------------------------------------------
void netextGui::mousePressed (int x, int y, int button){
    bool nodePressed = false;
    bool edgePressed = false;

    // Actions on mouse click event (0 = left, 2 = right)
    if (button == 0) {
        // Detect if a node was clicked
        for (int i=0; i<Nodes.size(); i++) {
            if (Nodes[i].checkOver (x, y)) {
                nodePressed = true;
                selectedNode = i;
                //Nodes[i].toggle_selected ();
                break;
            }
        }
        // Detect if an edge was clicked
        for (int i=0; i<Edges.size(); i++) {
            if (Edges[i].checkOver (x, y)) {
                edgePressed = true;
                selectedEdge = i;
                //Edges[i].toggle_selected ();
                break;
            }
        }
        // Declare the initial coordinates of the node multi-selection mode
        if (!nodePressed && !edgePressed) {
            selectVi.set(ofGetMouseX(), ofGetMouseY());
            //Nodes.push_back (Node ());
            //Nodes.back().set (x, y);
        }
    } else if (button == 2) {
        // Detect a right-clicked node
        for (int i=0; i<Nodes.size(); i++) {
            if (Nodes[i].checkOver (x, y)) {
                nodePressed = true;
                selectedNode = i;
                break;
            }
        }
        // Detect a right-clicked edge
        for (int i=0; i>Edges.size(); i++) {
            if (Edges[i].checkOver (x, y)) {
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
                Nodes[selectedNode].toggle_selected ();
                // TODO: Active properties edition
            }
        }
        if (button == 2) {
            // Create edge on mouse release over a node
            for (int i=0; i<Nodes.size(); i++) {
                if (Nodes[i].checkOver(ofGetMouseX(), ofGetMouseY()) && i != selectedNode) {
                    Edges.push_back (Edge ());
                    Edges.back().set(Nodes[selectedNode], Nodes[i], selectedNode, i);
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
                Edges[selectedEdge].toggle_selected ();
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
                for (int  i=0; i<Nodes.size(); i++) {
                    if (selectVi.x <= Nodes[i].center.x && Nodes[i].center.x <= selectVf.x && selectVi.y <= Nodes[i].center.y && Nodes[i].center.y <= selectVf.y) {
                        Nodes[i].toggle_selected ();
                    }
                }
            } else {
                // Create node
                Nodes.push_back (Node ());
                Nodes.back().set (x, y);
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
