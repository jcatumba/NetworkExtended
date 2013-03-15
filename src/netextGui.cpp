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
    //theNode.moveTo (mouseX, mouseY);
}

//--------------------------------------------------------------
void netextGui::draw (){
    //theNode.draw ();
    for (int i=0; i<Nodes.size (); i++) {
        Nodes[i].draw ();
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
        Nodes[selectedNode].update(ofGetMouseX(), ofGetMouseY());
    }
}

//--------------------------------------------------------------
void netextGui::mousePressed (int x, int y, int button){
    bool pressed = false;
    for (int i=0; i<Nodes.size(); i++) {
        if (Nodes[i].checkOver(x, y)) {
            pressed = true;
            selectedNode = i;
            break;
        }
    }
    if (button == 0 && !pressed) {
        Nodes.push_back (Node ());
        Nodes.back().set (x, y);
    }
}

//--------------------------------------------------------------
void netextGui::mouseReleased (int x, int y, int button){
    selectedNode = -1;
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
