#include "netextGui.h"

//--------------------------------------------------------------
void netextGui::setup (){
    //ofBackgroundGradient (ofColor (255, 255, 255), ofColor (0, 0, 0), OF_GRADIENT_CIRCULAR);
    ofEnableSmoothing ();
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320;
    gui = new ofxUICanvas ();

    gui->setFont ("GUI/mono.ttf");
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
    gui->loadSettings ("GUI/guiSettings.xml");
}

//--------------------------------------------------------------
void netextGui::update (){
}

//--------------------------------------------------------------
void netextGui::draw (){
    for (int i=0; i<Nodes.size (); i++) {
        Nodes[i].draw ();
    }
    for (int i=0; i<Edges.size (); i++) {
        Edges[i].draw ();
    }
}

//--------------------------------------------------------------
void netextGui::exit (){
    gui->saveSettings ("GUI/guiSettings.xml");
    delete gui;
}

//--------------------------------------------------------------
void netextGui::guiEvent (ofxUIEventArgs &e){
    string name = e.widget->getName ();

    //cout << "Widget Name: " << name << endl;

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
    switch (key) {
        case 'p':
            gui->setDrawWidgetPadding (true);
            break;
        case 'P':
            gui->setDrawWidgetPadding (false);
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
    if (selectedEdge > -1) {
        Edges[selectedEdge].update(ofGetMouseX(), ofGetMouseY());
    }
}

//--------------------------------------------------------------
void netextGui::mousePressed (int x, int y, int button){
    bool nodePressed = false;
    bool edgePressed = false;
    if (button == 0) {
        for (int i=0; i<Nodes.size(); i++) {
            if (Nodes[i].checkOver (x, y)) {
                nodePressed = true;
                selectedNode = i;
                break;
            }
        }
        for (int i=0; i<Edges.size(); i++) {
            if (Edges[i].checkOver (x, y)) {
                edgePressed = true;
                selectedEdge = i;
                break;
            }
        }
        if (!nodePressed && !edgePressed) {
            Nodes.push_back (Node ());
            Nodes.back().set (x, y);
        }
    } else if (button == 2) {
        for (int i=0; i<Nodes.size(); i++) {
            if (Nodes[i].checkOver(x, y)) {
                nodePressed = true;
                selectedNode = i;
                break;
            }
        }
    }
}

//--------------------------------------------------------------
void netextGui::mouseReleased (int x, int y, int button){
    if (selectedNode > -1) {
        if (button == 2) {
            for (int i=0; i<Nodes.size(); i++) {
                if (Nodes[i].checkOver(ofGetMouseX(), ofGetMouseY()) && i != selectedNode) {
                    Edges.push_back (Edge ());
                    Edges.back().set(Nodes[selectedNode], Nodes[i], selectedNode, i);
                }
            }
        }
    }
    selectedNode = -1;
    selectedEdge = -1;
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
