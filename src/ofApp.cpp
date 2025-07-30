//  ofApp.cpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02


#include "ofApp.h"






void ofApp::setup()
{
	// Setup Button
	myButton = Button("Click Me", 50, 50, 120, 40, [this]() {
		ofLogNotice("TestInputControls") << "Button callback triggered.";
	});
	// For demonstration, highlight the button is initially 'not pressed'.
	myButton.isPressed = false;
	
	// Setup Toggle
	myToggle = Toggle("Switch", 50, 120, 120, 40, false, [this]() {
		ofLogNotice("TestInputControls") << "Toggle state changed to: " << (myToggle.isOn ? "ON" : "OFF");
	});
	
	// Setup TextField
	// Suppose the range is [0, 100] and we store the new value in testValue with 2 decimal precision.
	myTextField = TextField("Value", 50, 190, 140, 40, 0, 100, testValue, 2);
	
	// Setup Tab
	myTab = Tab("TestTab", 50, 260, 120, 40, false, [this]() {
		ofLogNotice("TestInputControls") << "Tab pressed!";
	});
	
	// Logging startup
	ofLogNotice("TestInputControls") << "Setup complete.";
}




void ofApp::draw()
{
	// Draw each UI element
	ofBackground(40);
	ofSetColor(255);
	
	myButton.draw();
	myToggle.draw();
	myTextField.draw();
	myTab.draw();
	
	// Provide some on-screen instructions
	ofDrawBitmapStringHighlight("Click or toggle the controls above;\nType in the TextField and press ENTER to apply.",
								50, 320);
}








// Forward mouse events to each control
void ofApp::mousePressed(int x, int y, int button)
{
	myButton.mousePressed(x, y, button);
	myToggle.mousePressed(x, y, button);
	myTextField.mousePressed(x, y, button);
	myTab.mousePressed(x, y, button);
}


void ofApp::mouseReleased(int x, int y, int button)
{
	myButton.mouseReleased(x, y, button);
	// Toggle only uses mousePressed, so no mouseReleased usage.
	myTextField.mouseReleased(x, y, button);
	// Tab only uses mousePressed, so no mouseReleased usage.
}






// Forward key events to text field
void ofApp::keyReleased(int key)
{
	myTextField.keyReleased(key);
}
