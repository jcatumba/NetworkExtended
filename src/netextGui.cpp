#include "netextGui.h"

//--------------------------------------------------------------
void netextGui::setup (){
    ofEnableSmoothing ();
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

}

//--------------------------------------------------------------
void netextGui::exit (){
    gui->saveSettings ("GUI/guiSettings.xml");
    delete gui;
}

//--------------------------------------------------------------
void netextGui::guiEvent (ofxUIEventArgs &e){
    if (e.widget->getName () == "Background value") {
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        ofBackground (slider->getScaledValue ());
    } else if (e.widget->getName () == "Fullscreen") {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen (toggle->getValue ());
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

}

//--------------------------------------------------------------
void netextGui::mousePressed (int x, int y, int button){

}

//--------------------------------------------------------------
void netextGui::mouseReleased (int x, int y, int button){

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
