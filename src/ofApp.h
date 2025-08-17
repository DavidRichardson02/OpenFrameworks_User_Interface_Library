//  ofApp.h
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02

// This file demonstrates how to create instances of Button, Toggle, TextField, and Tab,
// call their various methods, and validate that they respond to events.


#pragma once
#include "ofMain.h"
#include "InputControls.hpp"
#include "NavigationalComponents.hpp"
#include "InformationalComponents.hpp"





// A simple ofApp to test the GUI controls.
class ofApp : public ofBaseApp
{
public:
	double testValue = 25.0; // Example value for the TextField
	Table *inputControls;
	Table *navigationalComponents;
	TableManager *tableManager;
	
	
	
	
	float theta = 0.5; // Example value for Barnes-Hut θ
	float dt = 1.0 / 60.0; // Example value for Δt (time step)
	double G = 6.67430e-11; // Gravitational constant in m^3 kg^-1 s^-2
	
	
	void setup() override;
	void draw() override;
	

	void keyReleased(int key) override;
	void mouseDragged(int x, int y, int button) override;
	void mousePressed(int x, int y, int button) override;
	void mouseReleased(int x, int y, int button) override;
};















