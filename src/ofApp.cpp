//  ofApp.cpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02


#include "ofApp.h"




void ofApp::setup()
{
	Button *myButton = new Button("Click Button", 50, 50, 40, 40, [this]() {
		ofLogNotice("TestInputControls") << "Button callback triggered.";});
	Toggle *myToggle = new Toggle("Switch Toggle", 50, 120, 40, 40, false);
	TextField *myTextField = new TextField("Value", 50, 300, 180, 50, 1, 100, testValue, 4);
	ofLogNotice("TestInputControls") << "Setup complete.";
	inputControls = new Table("Input Controls Manager", 45, 45, 20, 20, false);
	inputControls->addButtonElement(myButton);
	inputControls->addToggleElement(myToggle);
	inputControls->addTextFieldElement(myTextField);
	
	
	Slider* thetaSlider = new Slider("MAC", 125, 50, 150, 10, 0, 2, theta);
	Slider *dtS = new Slider("t", 0,0,200,15, (1/120), 1, dt);
	TextField *gTF = new TextField("G", 0,0,200,17,6.67430e-11, 6.67430e4, G, 15);
	navigationalComponents = new Table("Navigation Components Manager", 45, 450, 20, 20, false);
	navigationalComponents->addSliderElement(thetaSlider);
	navigationalComponents->addSliderElement(dtS);
	navigationalComponents->addTextFieldElement(gTF);
	
	
	
	tableManager = new TableManager(0, "UI Elements Table Manager", 0 + ofGetWidth() * 0.025, ofGetHeight() * 0.030, 15, 15);
	tableManager->addTable(inputControls);
	tableManager->addTable(navigationalComponents);
}





void ofApp::draw()
{
	ofBackground(40); ofSetColor(255);
	tableManager->draw();
	ofDrawBitmapStringHighlight("Click or toggle the controls above;\nType in the TextField and press ENTER to apply.", 25, ofGetHeight() - 50);
}


void ofApp::keyReleased(int key)
{ tableManager->keyReleased(key); }

void ofApp::mouseDragged(int x, int y, int button)
{ tableManager->mouseDragged(x, y, button); }
void ofApp::mousePressed(int x, int y, int button)
{ tableManager->mousePressed(x, y, button); }
void ofApp::mouseReleased(int x, int y, int button)
{ tableManager->mouseReleased(x, y, button); }



