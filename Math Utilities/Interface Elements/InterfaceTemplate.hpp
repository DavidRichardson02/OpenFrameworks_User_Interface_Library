//  InterfaceTemplate.hpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02
/**
 * Interface Template header file defines template classes for GUI interface windows
 * and reusable widget templates for an OpenFrameworks-based interface library.
 *
 * These template components include:
 *   - InterfaceWindow: A comprehensive window container that manages table managers,
 *     tooltips, and rectangular grid drag selections for complex UI layouts.
 *   - Template: A flexible, reusable widget template with configurable appearance,
 *     callbacks, and interaction states suitable for creating custom UI elements.
 *
 * These classes serve as foundational building blocks for creating sophisticated
 * user interfaces, providing standardized interaction patterns and visual feedback.
 */


#pragma once
#include "CoordinateSystem.hpp"
#include "InputControls.hpp"
#include "NavigationalComponents.hpp"
#include "InformationalComponents.hpp"
#include "DrawingUtilities.hpp"






/**
 * InterfaceWindow class representing a comprehensive GUI interface window.
 *
 * The InterfaceWindow class provides a high-level container for organizing and managing
 * multiple UI components within a windowed interface. It integrates with TableManager
 * for hierarchical element organization, supports tooltips for contextual information,
 * and includes drag selection capabilities via RectangularGridDragSelection.
 *
 * Key features:
 * - Manages position, size, and visual rendering of the window
 * - Integrates with TableManager for complex UI hierarchies
 * - Supports tooltip display for user guidance
 * - Handles user interaction through mouse events
 * - Provides callback mechanism for custom interactions
 * - Includes rectangular grid drag selection for area-based user input
 */
class InterfaceWindow
{
public:
	/// ------------- Constructors -------------
	/// \{
	InterfaceWindow(); // Default constructor that initializes an interface window with templated defaults
	InterfaceWindow(std::string _label, float _x, float _y, float _w, float _h); // Constructor with label and geometry
	InterfaceWindow(std::string _label, float _x, float _y, float _w, float _h, TableManager *_tableManager); // Constructor with label, geometry, and table manager
	/// \}
	
	
	/// ------------- Setters -------------
	/// \{
	void setAnchorPosition(ofVec2f rectPos); // Sets the position of the interface window while maintaining size
	void setWindow(ofVec2f rectPos, ofVec2f rectSize); // Sets both the position and size of the interface window
	TableManager *arrangeTables(); // Arranges and organizes tables within the interface window
	/// \}
	

	
	/// ------------- User Interaction -------------
	/// \{
	void draw(); // Renders the interface window, its components, and all child elements on screen
	void mousePressed(int x, int y, int button); // Handles mouse press events and routes to child components
	void mouseReleased(int x, int y, int button); // Handles mouse release events and routes to child components
	/// \}
	
	
	
	/// ------------- Interface Window Attributes -------------
	/// \{
	TableManager *tableManager; // Pointer to the table manager associated with this interface window
	ofRectangle interfaceWindow; // Represents the size and position of the interface window
	bool isInterfacing; // Indicates whether the user is currently engaged with the interface window
	std::string screenLabel; // The label displayed on the interface window
	std::function<void()> onClick; // Callback function for click events on the window
	Tooltip toolTip; // Tooltip to be displayed when the user interacts with the window
	RectangularGridDragSelection userRectangle; // Grid-based drag selection component for user-defined areas
	/// \}
	
	
};












/**
 * Template class representing a flexible, reusable GUI widget template.
 *
 * The Template class provides a foundational widget structure that can be customized
 * for various UI purposes. It offers a simple, clean interface with standard interaction
 * patterns, visual feedback, and callback support. This class is designed to serve as
 * a starting point for creating custom widgets or as a standalone interactive element.
 *
 * Key features:
 * - Configurable label, position, and dimensions
 * - Visual state feedback (normal vs. interfacing)
 * - Integrated tooltip support for contextual information
 * - Standard mouse event handling with callback support
 * - Rounded rectangle rendering with customizable appearance
 * - Consistent with library widget patterns and conventions
 */
class Template
{
public:
	/// ------------- Constructors -------------
	/// \{
	Template(); // Default constructor that initializes a template with default values
	Template(std::string _label, float _x, float _y, float _w, float _h); // Constructor with label and geometry
	Template(std::string _label, float _x, float _y, float _w, float _h, std::function<void()> callback); // Constructor with label, geometry, and callback
	/// \}
	
	
	/// ------------- Setters -------------
	/// \{
	void setPosition(ofVec2f rectPos); // Sets the position of the template while maintaining size
	void set(ofVec2f rectPos, ofVec2f rectSize); // Sets both the position and size of the template
	/// \}
	
	
	
	
	/// ------------- User Interaction -------------
	/// \{
	void draw(); // Renders the template with state-based visual feedback
	void mousePressed(int x, int y, int button); // Handles mouse press events and triggers callbacks
	void mouseReleased(int x, int y, int button); // Handles mouse release events and updates state
	/// \}
	
	
	
	/// ------------- Template Attributes -------------
	/// \{
	ofRectangle interfaceWindow; // Represents the size and position of the template widget
	bool isInterfacing; // Indicates whether the user is currently interacting with the template
	std::string screenLabel; // The label displayed on the template
	std::function<void()> onClick; // Callback function for click events on the template
	Tooltip toolTip; // Tooltip to provide contextual information about the template
	/// \}
	
	
};















