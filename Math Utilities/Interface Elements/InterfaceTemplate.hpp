//  InterfaceTemplate.hpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02


#pragma once
#include "CoordinateSystem.hpp"
#include "InputControls.hpp"
#include "NavigationalComponents.hpp"
#include "InformationalComponents.hpp"
#include "DrawingUtilities.hpp"






class InterfaceWindow
{
public:
	/// Constructors
	InterfaceWindow(); // Basic constructor that initializes an interface window with a default templated label, position, size, and table manager(s).
	InterfaceWindow(std::string _label, float _x, float _y, float _w, float _h); // Constructor that initializes an interface window with a label and specific position and size.
	InterfaceWindow(std::string _label, float _x, float _y, float _w, float _h, TableManager *_tableManager); // Constructor that initializes an interface window with a label, specific position and size, and a table manager.
	
	
	/// Setters
	void setAnchorPosition(ofVec2f rectPos); // Sets the position of the interface window
	void setWindow(ofVec2f rectPos, ofVec2f rectSize); // Sets the position and size of the interface window
	TableManager *arrangeTables(); // Arranges the tables in the interface window
	

	
	/// User Interaction
	void draw(); // Draws the interface window on the screen
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
	
	
	Tooltip toolTip; // Tooltip to be displayed when the mouse hovers over the button.
	
	
	RectangularGridDragSelection userRectangle;
	
	
	
	
	/// Interface Window Attributes
	TableManager *tableManager; // Pointer to the table manager associated with this interface window
	ofRectangle interfaceWindow; // Represents the size and position of the screen
	bool isInterfacing; // Indicates whether the user is engaged with the interface window.
	std::string screenLabel; // The label displayed on the screen
	std::function<void()> onClick; // Callback function for click events
	
	
};












/**
 * Template class representing a template for a menu screen.
 *
 *
 */
class Template
{
public:
	/// Constructors
	Template(); // Basic constructor that initializes a button with no label and default position and size
	Template(std::string _label, float _x, float _y, float _w, float _h); // Constructor that initializes a templated interface window with a label and specific position and size
	Template(std::string _label, float _x, float _y, float _w, float _h, std::function<void()> callback);
	
	
	/// Setters
	void setPosition(ofVec2f rectPos); // Sets the position of the interface window
	void set(ofVec2f rectPos, ofVec2f rectSize); // Sets the position and size of the interface window
	
	
	
	
	/// User Interaction
	void draw(); // Draws the interface window on the screen
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
	
	
	Tooltip toolTip; // Tooltip to be displayed when the mouse hovers over the button.
	
	
	/// Button Attributes
	ofRectangle interfaceWindow; // Represents the size and position of the screen
	bool isInterfacing; // Indicates whether the user is engaged with the interface window.
	std::string screenLabel; // The label displayed on the screen
	std::function<void()> onClick; // Callback function for click events
	
	
};















