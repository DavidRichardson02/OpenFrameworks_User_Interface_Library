//  ofApp.cpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02


#include "ofApp.h"






void ofApp::setup()
{
	Button *myButton = new Button("Click Me", 50, 50, 120, 40, [this]() {
		ofLogNotice("TestInputControls") << "Button callback triggered.";
	});
	
	
	Toggle *myToggle = new Toggle("Switch", 50, 120, 120, 40, false);
	
	
	TextField *myTextField = new TextField("Value", 50, 190, 140, 40, 0, 100, testValue, 2);
	
	
	Tab *myTab = new Tab("TestTab", 50, 260, 120, 40, false, [this]() {
		ofLogNotice("TestInputControls") << "Tab pressed!";
	});
	ofLogNotice("TestInputControls") << "Setup complete.";

	
	paramTable = new Table("Simulation", 30, 30, 220, 20, true);
	paramTable->addButtonElement(myButton);
	paramTable->addToggleElement(myToggle);
	paramTable->addTextFieldElement(myTextField);
	
	
	
	
	
	
	Slider* thetaSlider = new Slider("MAC", 125, 50, 150, 10, 0, 2, theta);
	Slider *dtS = new Slider("t", 0,0,200,15, (1/240), (1/30), dt);
	TextField *gTF = new TextField("G", 0,0,200,17, 6.67e-11, 1e-8,  G,  9);

	paramTable->addSliderElement(thetaSlider);
	paramTable->addSliderElement(dtS);
	paramTable->addTextFieldElement(gTF);
	
	
	
	
	
	// Optional: pack multiple tables
	//TableManager *uiManager(0,"UI", 0 + ofGetWidth() * 0.025, ofGetHeight() * 0.030, 15, 15);
	//uiManager->addTable(paramTable);
}



void ofApp::draw()
{
	// Draw each UI element
	ofBackground(40);
	ofSetColor(255);
	
	paramTable->draw();
	
	// Provide some on-screen instructions
	ofDrawBitmapStringHighlight("Click or toggle the controls above;\nType in the TextField and press ENTER to apply.",
								50, 320);
}








// Forward mouse events to each control
void ofApp::mousePressed(int x, int y, int button)
{
	paramTable->mousePressed(x, y, button);
}


void ofApp::mouseReleased(int x, int y, int button)
{
	paramTable->mouseReleased(x, y, button);
}






// Forward key events to text field
void ofApp::keyReleased(int key)
{
	paramTable->keyReleased(key);
}
