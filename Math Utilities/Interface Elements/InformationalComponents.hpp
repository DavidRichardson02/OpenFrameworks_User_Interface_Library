//  InformationalComponents.hpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02
/**
 * Informational Components header file declares the Tooltip class for interactive, on-screen tooltips.
 *
 * It features:
 *  - A small icon indicating tooltip availability
 *  - A message box that toggles visibility for contextual information
 *  - Methods for drawing, positioning, and handling mouse events
 *
 * In essence, it provides a concise way to offer users additional details or instructions
 * where needed in an OpenFrameworks-based UI.
 */


#pragma once
#include "InputControls.hpp"






/**
 * Tooltip class representing a GUI tooltip.
 *
 * This class provides an interactive tooltip that displays a message at a given position.
 * Its message box can be toggled on or off, and is drawn conditionally based on user interaction.
 * It helps deliver contextual information to the user.
 */
class Tooltip
{
public:
	/// ------------- Constructors -------------
	/// \{
	Tooltip(); // Initializes a default tooltip with no message and default position
	Tooltip(std::string message, float x, float y); // Initializes a tooltip using the given message and position
													/// \}
	
	/// ------------- Setters -------------
	/// \{
	void setPosition(float x, float y); // Updates the tooltip's position on the screen
	void setMessage(const std::string &newMessage); // Changes the displayed message text
	void toggleVisibility(); // Flips the visibility state of the tooltip's message box
							 /// \}
	
	
	
	
	/// ------------- User Interaction -------------
	/// \{
	void draw(); // Renders the tooltip icon and, if visible, the tooltip's message box onto the screen
	void mousePressed(int x, int y, int button); // Responds to mouse press events on or near the tooltip icon
	void mouseReleased(int x, int y, int button); // Responds when mouse button is released, finalizing interaction
												  /// \}
	
	
	
	
	
	
	/// ------------- Tooltip Attributes -------------
	/// \{
private:
	ofVec2f position;  // Tooltip icon position
	std::string message;  // Message displayed in the tooltip
	bool isMessageVisible;  // Visibility state of the message box
	ofRectangle messageBox;  // Bounding box for the message
	bool isLargeMessage;  // Flag to check if message is long
						  /// \}
	
	
	
	
	/// ------------- Tooltip Conditional Logic -------------
	/// \{
	void drawTooltipIcon(); // Draws the icon representing the tooltip
	void drawMessageBox();  // Draws the rectangular message box if visible
	bool isMouseInside(int x, int y, ofRectangle rect); // Checks if mouse coordinates lie within a given rectangle
														/// \}
};
