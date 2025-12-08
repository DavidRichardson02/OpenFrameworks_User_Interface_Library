//  InterfaceTemplate.cpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02


#include "InterfaceTemplate.hpp"






/**
 * InterfaceWindow
 *
 * Default constructor for the InterfaceWindow class.
 * Initializes an InterfaceWindow object with default values and a basic templated configuration.
 */
InterfaceWindow::InterfaceWindow()
{
	/// Initialize default values
	screenLabel = "Interface Window"; // Set a default label for the interface window
	interfaceWindow = ofRectangle(100, 100, 400, 300); // Initialize with default position and size
	isInterfacing = false; // Set the interfacing state to false by default
	tableManager = nullptr; // Initialize table manager pointer to null
	toolTip = Tooltip("Interface window tooltip", interfaceWindow.x + 10, interfaceWindow.y + 10); // Create a default tooltip
}


/**
 * InterfaceWindow
 *
 * Parameterized constructor that initializes an InterfaceWindow object with specified
 * label, position, and dimensions.
 *
 * @param _label: The label for the interface window
 * @param _x: The x-coordinate of the window position
 * @param _y: The y-coordinate of the window position
 * @param _w: The width of the window
 * @param _h: The height of the window
 */
InterfaceWindow::InterfaceWindow(std::string _label, float _x, float _y, float _w, float _h)
{
	/// Assign parameter values to the object
	screenLabel = _label; // Set the label of the interface window
	interfaceWindow.set(_x, _y, _w, _h); // Set the position and dimensions of the interface window
	isInterfacing = false; // Set the interfacing state to false
	tableManager = nullptr; // Initialize table manager pointer to null
	toolTip = Tooltip(_label + " info", _x + 10, _y + 10); // Create tooltip with label-based message
}


/**
 * InterfaceWindow
 *
 * Parameterized constructor that initializes an InterfaceWindow object with specified
 * label, position, dimensions, and an associated table manager.
 *
 * @param _label: The label for the interface window
 * @param _x: The x-coordinate of the window position
 * @param _y: The y-coordinate of the window position
 * @param _w: The width of the window
 * @param _h: The height of the window
 * @param _tableManager: Pointer to the table manager to be associated with this window
 */
InterfaceWindow::InterfaceWindow(std::string _label, float _x, float _y, float _w, float _h, TableManager *_tableManager)
{
	/// Assign parameter values to the object
	screenLabel = _label; // Set the label of the interface window
	interfaceWindow.set(_x, _y, _w, _h); // Set the position and dimensions of the interface window
	isInterfacing = false; // Set the interfacing state to false
	tableManager = _tableManager; // Assign the provided table manager
	toolTip = Tooltip(_label + " info", _x + 10, _y + 10); // Create tooltip with label-based message
}


/**
 * setAnchorPosition
 *
 * Sets the position of the interface window while maintaining its current dimensions.
 *
 * @param rectPos: A vector representing the new position of the interface window
 */
void InterfaceWindow::setAnchorPosition(ofVec2f rectPos)
{
	/// Update the position of the interface window
	interfaceWindow.set(rectPos.x, rectPos.y, interfaceWindow.width, interfaceWindow.height);
	toolTip.setPosition(rectPos.x + 10, rectPos.y + 10); // Update tooltip position relative to window
}


/**
 * setWindow
 *
 * Sets both the position and size of the interface window.
 *
 * @param rectPos: A vector representing the new position of the interface window
 * @param rectSize: A vector representing the new size of the interface window
 */
void InterfaceWindow::setWindow(ofVec2f rectPos, ofVec2f rectSize)
{
	/// Update both position and size of the interface window
	interfaceWindow.set(rectPos.x, rectPos.y, rectSize.x, rectSize.y);
	toolTip.setPosition(rectPos.x + 10, rectPos.y + 10); // Update tooltip position relative to window
}


/**
 * arrangeTables
 *
 * Arranges the tables within the interface window and returns the table manager.
 * This method handles the layout logic for organizing multiple tables within the window.
 *
 * @return Pointer to the table manager associated with this interface window
 */
TableManager* InterfaceWindow::arrangeTables()
{
	/// Arrange tables within the interface window
	if (tableManager != nullptr)
	{
		// Table arrangement logic could be implemented here
		// For now, simply return the table manager
	}
	return tableManager;
}


/**
 * draw
 *
 * Renders the interface window on the screen.
 * This function draws the window border, background, label, and any associated UI elements
 * including the table manager, tooltip, and user rectangle selection.
 */
void InterfaceWindow::draw()
{
	/// Step 1: Draw the interface window background
	ofFill();
	if (isInterfacing)
	{
		ofSetColor(100, 100, 120, 200); // Slightly highlighted background when interfacing
	}
	else
	{
		ofSetColor(80, 80, 80, 180); // Normal background color
	}
	ofDrawRectRounded(interfaceWindow, 5); // Draw rounded rectangle for the window
	
	
	/// Step 2: Draw the interface window border
	ofNoFill();
	ofSetColor(150, 150, 150); // Light gray border
	ofSetLineWidth(2);
	ofDrawRectangle(interfaceWindow);
	ofSetLineWidth(1); // Reset line width
	
	
	/// Step 3: Draw the window label
	ofSetColor(255); // White color for text
	ofDrawBitmapString(screenLabel, interfaceWindow.x + 10, interfaceWindow.y + 20);
	
	
	/// Step 4: Draw associated table manager if present
	if (tableManager != nullptr)
	{
		tableManager->draw();
	}
	
	
	/// Step 5: Draw the tooltip
	toolTip.draw();
	
	
	/// Step 6: Draw user rectangle selection if active
	userRectangle.draw();
}


/**
 * mousePressed
 *
 * Handles the mouse pressed event for the interface window.
 * Routes the event to child components and determines if the user is interacting with the window.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was pressed
 */
void InterfaceWindow::mousePressed(int x, int y, int button)
{
	/// Check if the mouse press is within the interface window
	if (interfaceWindow.inside(x, y))
	{
		isInterfacing = true; // Set interfacing state to true
		
		/// Forward mouse event to table manager if present
		if (tableManager != nullptr)
		{
			tableManager->mousePressed(x, y, button);
		}
		
		/// Forward mouse event to tooltip
		toolTip.mousePressed(x, y, button);
		
		/// Forward mouse event to user rectangle
		userRectangle.mousePressed(x, y, button);
		
		/// Execute onClick callback if set
		if (onClick)
		{
			onClick();
		}
	}
	else
	{
		isInterfacing = false; // Set interfacing state to false if outside window
	}
}


/**
 * mouseReleased
 *
 * Handles the mouse released event for the interface window.
 * Routes the event to child components and updates interaction state.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was released
 */
void InterfaceWindow::mouseReleased(int x, int y, int button)
{
	/// Forward mouse released event to table manager if present
	if (tableManager != nullptr)
	{
		tableManager->mouseReleased(x, y, button);
	}
	
	/// Forward mouse released event to tooltip
	toolTip.mouseReleased(x, y, button);
	
	/// Forward mouse released event to user rectangle
	userRectangle.mouseReleased(x, y, button);
	
	/// Update interfacing state
	isInterfacing = false;
}










/**
 * Template
 *
 * Default constructor for the Template class.
 * Initializes a Template object with default values.
 */
Template::Template()
{
	/// Initialize default values
	screenLabel = "Template"; // Set a default label
	interfaceWindow = ofRectangle(50, 50, 200, 100); // Initialize with default position and size
	isInterfacing = false; // Set the interfacing state to false
	toolTip = Tooltip("Template tooltip", interfaceWindow.x + 10, interfaceWindow.y + 10); // Create a default tooltip
}


/**
 * Template
 *
 * Parameterized constructor that initializes a Template object with specified
 * label, position, and dimensions.
 *
 * @param _label: The label for the template
 * @param _x: The x-coordinate of the template position
 * @param _y: The y-coordinate of the template position
 * @param _w: The width of the template
 * @param _h: The height of the template
 */
Template::Template(std::string _label, float _x, float _y, float _w, float _h)
{
	/// Assign parameter values to the object
	screenLabel = _label; // Set the label of the template
	interfaceWindow.set(_x, _y, _w, _h); // Set the position and dimensions
	isInterfacing = false; // Set the interfacing state to false
	toolTip = Tooltip(_label + " info", _x + 10, _y + 10); // Create tooltip with label-based message
}


/**
 * Template
 *
 * Parameterized constructor that initializes a Template object with specified
 * label, position, dimensions, and a callback function.
 *
 * @param _label: The label for the template
 * @param _x: The x-coordinate of the template position
 * @param _y: The y-coordinate of the template position
 * @param _w: The width of the template
 * @param _h: The height of the template
 * @param callback: Callback function to be executed when the template is clicked
 */
Template::Template(std::string _label, float _x, float _y, float _w, float _h, std::function<void()> callback) : onClick(callback)
{
	/// Assign parameter values to the object
	screenLabel = _label; // Set the label of the template
	interfaceWindow.set(_x, _y, _w, _h); // Set the position and dimensions
	isInterfacing = false; // Set the interfacing state to false
	toolTip = Tooltip(_label + " info", _x + 10, _y + 10); // Create tooltip with label-based message
}


/**
 * setPosition
 *
 * Sets the position of the template while maintaining its current dimensions.
 *
 * @param rectPos: A vector representing the new position of the template
 */
void Template::setPosition(ofVec2f rectPos)
{
	/// Update the position of the template
	interfaceWindow.set(rectPos.x, rectPos.y, interfaceWindow.width, interfaceWindow.height);
	toolTip.setPosition(rectPos.x + 10, rectPos.y + 10); // Update tooltip position relative to template
}


/**
 * set
 *
 * Sets both the position and size of the template.
 *
 * @param rectPos: A vector representing the new position of the template
 * @param rectSize: A vector representing the new size of the template
 */
void Template::set(ofVec2f rectPos, ofVec2f rectSize)
{
	/// Update both position and size of the template
	interfaceWindow.set(rectPos.x, rectPos.y, rectSize.x, rectSize.y);
	toolTip.setPosition(rectPos.x + 10, rectPos.y + 10); // Update tooltip position relative to template
}


/**
 * draw
 *
 * Renders the template on the screen.
 * This function draws the template's background, border, label, and tooltip.
 * The visual appearance changes based on the interaction state.
 */
void Template::draw()
{
	/// Step 1: Draw the template background
	ofFill();
	if (isInterfacing)
	{
		ofSetColor(120, 140, 255, 200); // Blue tint when interfacing
	}
	else
	{
		ofSetColor(140, 140, 140, 180); // Gray background when not interfacing
	}
	ofDrawRectRounded(interfaceWindow, interfaceWindow.width * 0.15); // Draw rounded rectangle
	
	
	/// Step 2: Draw the template border
	ofNoFill();
	ofSetColor(191, 191, 191); // Light gray border
	ofSetLineWidth(2);
	ofDrawRectangle(interfaceWindow);
	ofSetLineWidth(1); // Reset line width
	
	
	/// Step 3: Draw the template label
	ofSetColor(255); // White color for text
	float labelX = interfaceWindow.x + (interfaceWindow.width - screenLabel.length() * 8) * 0.5; // Center the label horizontally
	float labelY = interfaceWindow.y + interfaceWindow.height * 0.5 + 4; // Center the label vertically
	ofDrawBitmapString(screenLabel, labelX, labelY);
	
	
	/// Step 4: Draw the tooltip
	toolTip.draw();
}


/**
 * mousePressed
 *
 * Handles the mouse pressed event for the template.
 * Determines if the user is interacting with the template and triggers callbacks.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was pressed
 */
void Template::mousePressed(int x, int y, int button)
{
	/// Check if the mouse press is within the template
	if (interfaceWindow.inside(x, y))
	{
		isInterfacing = true; // Set interfacing state to true
		
		/// Execute onClick callback if set
		if (onClick)
		{
			onClick();
		}
	}
	else
	{
		isInterfacing = false; // Set interfacing state to false if outside template
	}
	
	/// Forward mouse event to tooltip
	toolTip.mousePressed(x, y, button);
}


/**
 * mouseReleased
 *
 * Handles the mouse released event for the template.
 * Updates the interaction state and forwards the event to child components.
 *
 * @param x: The x-coordinate of the mouse cursor
 * @param y: The y-coordinate of the mouse cursor
 * @param button: The mouse button that was released
 */
void Template::mouseReleased(int x, int y, int button)
{
	/// Update interfacing state
	isInterfacing = false;
	
	/// Forward mouse released event to tooltip
	toolTip.mouseReleased(x, y, button);
}


/**
 RectangularGridDragSelection vectorGrid("Test grid", (ofGetWidth() * 0.5 - 1250), (ofGetHeight() * 0.5 - 1250), 5, 2500);
 simulationConfigure.config(simulatorTitle, simulationMode, rootQuadtree, bodies, bodiesAccelerations, vectorGrid, theta, G, e, dt);
 */















