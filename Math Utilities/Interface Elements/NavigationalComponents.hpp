//  NavigationalComponents.hpp
//  OpenFrameworks_User_Interface_Library
//  DavidRichardson02
/**
 * Navigational Components header file defines several classes representing GUI components
 * for an OpenFrameworks-based interface.
 *
 * These components include:
 *   - Slider: A basic GUI slider with interactive mouse handling and configurable range/precision.
 *   - Table: A container organizing multiple elements (sliders, buttons, toggles, text fields, etc.).(WIP,		7/8, ~87.5%, 	fully functional but slight auto-positioning issues)
 *   - TableManager: Manages multiple tables, orchestrating their positions, interactions, and layout.(WIP,		4/5, ~80%, 		fully functional but bit more tricky auto-positionaing & aligning issues)
 *   - RectangularGridDragSelection: Allows the user to drag and define a square grid area with uniform cells.(WIP,		2/3, ~66%, 		mostly done with groundwork but needs to be significantly extended)
 *   - RectangularSelectionWindow: A window class that leverages RectangularGridDragSelection for area-based user selections.(WIP,		1/3, ~33%, 		very basic foundation been layed which must be completed and will still need to be significantly extended)
 *
 * These components are designed to facilitate user interaction and data manipulation within a graphical interface.
 */


#pragma once
#include "InputControls.hpp"
#include "InformationalComponents.hpp"
#include "DrawingUtilities.hpp"






/**
 * Slider class representing a GUI slider.
 *
 * The Slider class represents a basic GUI slider with a label, position, size, and a range (min, max).
 * It provides functionalities for user interactions, including mouse pressed, dragged and released events.
 * The slider's attributes, such as the label, position, size, and range can be directly accessed and modified.
 */
class Slider
{
public:
	/// ------------- Constructors -------------
	/// \{
	Slider(); // Basic constructor that initializes a slider with no label and default position, size, and range
	Slider(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, float &_value); // Constructor that initializes a slider with a label, specific position, size, and range
	Slider(std::string _label, float _x, float _y, float _w, float _h, float _min, float _max, float &_value, int _precision); // Constructor that initializes a slider with a label, specific position, size, range, and precision
																															   /// \}
	
	
	
	/// ------------- Setters and Upkeep -------------
	/// \{
	void setPosition(ofVec2f rectPos); // Sets the position of the slider
									   /// \}
	
	
	
	/// ------------- User Interaction -------------
	/// \{
	void draw(); // Draws the slider on the screen
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseDragged(int x, int y, int button); // Handles the mouse dragged event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
												  /// \}
	
	
	
	
	/// ------------- Slider Attributes -------------
	/// \{
	float *value; // The current value of the slider
	float min, max; // The minimum and maximum values of the slider
	std::string label; // The label displayed on the slider
	bool isDragging; // Indicates whether the slider is currently being dragged
	ofRectangle rect; // Represents the size and position of the slider
	int precision;  // Integer to track the degree of precision needed to record and display value of object passed into slider. For example, gravitational constant, 'g', needs approximately 15 digits of precision
					/// \}
};








/**
 * Table class representing a GUI table.
 *
 * The Table class represents a basic GUI table with a label, position, and size,
 * that encapsulates and manages multiple GUI elements, such as: buttons, toggles,
 * sliders, textfields, tabs, etc. It provides functionalities for user interactions,
 * including key released, mouse pressed, dragged, and released events.
 */
class Table
{
public:
	/// ------------- Constructors and Destructor -------------
	/// \{
	Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened); // Constructor for regular tables
	Table(std::string _label, float _x, float _y, float _w, float _h, bool _isOpened, int _tableType); // Constructor for tables with a specific type
	~Table(); // Destructor
			  /// \}
	
	
	/// ------------- Element Addition -------------
	/// \{
	void addSliderElement(Slider* &_sliderElement); // Adds a slider element to the table
	void addButtonElement(Button* &_buttonElement); // Adds a button element to the table
	void addToggleElement(Toggle* &_toggleElement); // Adds a toggle element to the table
	void addTextFieldElement(TextField* &_textFieldElement); // Adds a text field element to the table
	void addTooltipElement(Tooltip* &_toolTipElement); // Adds a tooltip element to the table
	void addTabElement(Tab* &_tabElement); // Adds a tab element to the table
													   /// \}
	
	
	
	/// ------------- Setters -------------
	/// \{
	ofVec2f tableElementsDimensions(); // Returns the dimensions of the table
	void layoutElements(); // Method to dynamically adjust the layout of elements within tableRect
	void setPosition(ofVec2f rectPos); // Sets the position of the table
									   /// \}
	
	
	
	/// ------------- Callback Function -------------
	/// \{
	void callbackUpdate(); // Continuously calls the callback function for all toggle elements
						   /// \}
	
	
	/// ------------- User Interaction -------------
	/// \{
	void draw(); // Draws the table on the screen
	void exit(); // Handles the exit event
	void clear(); // Clears all elements from the table
	
	void keyReleased(int key); // Handles the key released event
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseDragged(int x, int y, int button); // Handles the mouse dragged event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
												  /// \}
	
	
	
	
	/// ------------- Table Attributes -------------
	/// \{
	ofRectangle tableRect; // The opaque rectangle that encloses the elements of the table
	Tab tableTab; // The tab of the table
	bool isOpened; // Indicates whether the table is open or not
	std::string label; // The label displayed on the table
	ofRectangle labelRect; // The size of the bounding box enclosing the table element's name
	/**
	 * TABLE TYPES:
	 *
	 * tableType == 0 : Regular table
	 *
	 * tableType == 1 : Double Row Table
	 *      1.1 Center Screen, Left Row Sliders, Right Row Mutually Exclusive Buttons. With a scalar for adjusting width of table and scalar for adjusting height of table
	 *
	 *      1.2 Similar to Regular Table but with a scalar for adjusting size of table
	 *
	 * tableType == 2 : Special Case
	 *
	 */
	int tableType; // The type of the table (0: regular, 1: double row, 2: special case)
	
	
	/// Table Elements
	std::vector<Slider*> sliderElements; // The slider elements in the table
	std::vector<Button*> buttonElements; // The button elements in the table
	std::vector<Toggle*> toggleElements; // The toggle elements in the table
	std::vector<TextField*> textfieldElements; // The text field elements in the table
	std::vector<Tooltip*> toolTipElements; // The tooltip elements in the table
	std::vector<Tab*> tabElements; // The tab elements in the table
																   //std::vector<Tab*> tabElements; // The tab elements in the table
										   /// \}
};














/**
 * TableManager class representing a manager for multiple GUI tables.
 *
 * The TableManager class manages multiple GUI tables and provides functionalities for user interactions.
 * It also handles the layout of the tables and provides functionalities for adding and clearing tables.
 * The TableManager's attributes, such as the label, position, tables, and simulation mode can be directly accessed and modified.
 */
class TableManager
{
public:
	/// ------------- Constructors and Destructor -------------
	/// \{
	TableManager(); // Basic constructor that initializes a table manager with default parameters
	TableManager(int _mode, std::string _label); // Constructor that initializes a table manager with a specific mode and label
	TableManager(int _mode, std::string _label, float _x, float _y, float _w, float _h); // Constructor that initializes a table manager with a specific mode, label, position and size
	~TableManager(); // Destructor for the table manager
					 /// \}
	
	
	/// ------------- Setters -------------
	/// \{
	void setPosition(ofVec2f rectPos); // Sets the position of the table manager
	void repositionTables(); // Repositions all tables in the table manager
							 /// \}
	
	
	/// ------------- User Interaction -------------
	/// \{
	void update(float &theta, double &G, float &e, float &dt); // Updates the table manager
	void draw(); // Draws the table manager on the screen
	void exit(); // Handles the exit event
	void clear(); // Clears all tables from the table manager
	
	void keyReleased(int key); // Handles the key released event
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseDragged(int x, int y, int button); // Handles the mouse dragged event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
												  /// \}
	
	
	/// ------------- Table Management -------------
	/// \{
	void addTable(Table* &table); // Adds a table to the table manager
	void adjustTableManagerDimensions(float newHeight); // Adjusts the dimensions of the table manager
	void focusedMode(); // Sets the table manager to focus mode, i.e., closes all tables except the one in focus
						/// \}
	
	
	
	
	
	/// ------------- TableManager Attributes -------------
	/// \{
	std::vector<Table*> tables; // The tables managed by the table manager
	Tab tableTab; // The tab of the table manager
	ofRectangle rect; // The rectangle that encloses the elements of the table manager
	bool isOpened; // Whether the table manager is open or not
	bool focusMode; // Indicates whether the table manager is in focus mode
	std::string label; // The label of the table manager
	ofTrueTypeFont labelFont, labelBodyFont; //fonts of table elements
	ofRectangle labelRect; // The size of the bounding box enclosing the table manager's name
						   /// \}
};






//table type
/**
 * TABLE TYPES:
 *
 * 1. Regular table
 * 2. Double Row Table
 *      2.1 Center Screen, Left Row Sliders, Right Row Mutually Exclusive Buttons. With a scalar for adjusting width of table and scalar for adjusting height of table
 *
 *      2.2 Similar to Regular Table but with a scalar for adjusting size of table
 *
 * 3. Table Manager, tables within this table
 *
 
 */






/**
 * RectangularGridDragSelection class provides functionality to create a rectangular  grid
 * with the top left centered at the starting position of the mouse when left clicked,
 * the user can then begin dragging their cursor to change the size, shape, and orientation
 * of the rectangle, with the top left corner of the rectangle(starting position) fixed in
 * place, while the bottom right corner follows the user's cursor until they let go of the
 * clicked button, and where the width and height of the bounds grow at the same rate, so that there are always four right angles.
 *
 * Whenever the user releases the mouse, the selected area will be locked in, and the
 * user will be prompted with a slider to specify the granularity of the grid to be made
 * from the selected area as well as a button to submit the slider granularity value once
 * satisfactorily adjusted.
 *
 * Throughout the process of selecting the area for the grid and adjusting granularity, the
 * rectangular bounds of the grid selection will always be in the shape of a square,
 * and will never not have four right angles, this must always be true due to the
 * requirement that all grid cells are of a uniform size and can be evenly distributed
 * to fill the grid space.
 */
class RectangularGridDragSelection
{
public:
	/// ------------- Constructors -------------
	/// \{
	RectangularGridDragSelection(std::string label, float _x, float _y, float _w, float _h); // Constructor that initializes a RectangularGridDragSelection with a label, specific position, and size
	RectangularGridDragSelection(std::string label, float _x, float _y, float _w, float _h, float _min, float _max); // Constructor that initializes a RectangularGridDragSelection with a label, specific position, size, and min/max values for the slider
																													 /// \}
	
	
	
	/// ------------- Setters -------------
	/// \{
	void setPosition(ofVec2f rectPos); // Sets the position of the top left corner of RectangularGridDragSelection
	void set(ofVec2f rectSize); // Sets the size of the RectangularGridDragSelection
								/// \}
	
	
	
	
	void updateGridCells();  // Update gridCells based on current gridBounds and granularity
	void draw(); // Draws the RectangularGridDragSelection square on the screen
	
	
	
	/// ------------- User Interaction -------------
	/// \{
	void mouseDragged(int x, int y, int button); // Handles the mouse dragged event
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
												  /// \}
	
	
	
	
	/// ------------- RectangularGridDragSelection Attributes -------------
	/// \{
	std::string gridLabel; // The label to be displayed on the rectangle selection slider
	ofRectangle gridBounds; // Represents the bounds(size and position) of the selection rectangle
	std::vector<ofRectangle> gridCells; // Vector of grid cells representing the individual cells of the grid
	
	
	// Make granularity automatically determined based on size of selected area so that all grid cells are of a
	//uniform size and can be evenly distributed to fill the grid space, number of bodies inside selected area
	float granularity; // The granularity(detail) of the grid, i.e., the size of each cell in the grid
	/** grid cells all of uniform size
	 *      grid cell  x == gridBounds.x + i*granularity
	 *      grid cell  y == gridBounds.y + i*granularity
	 *
	 *      grid cell height == gridBounds.height/granularity
	 *      grid cell width == gridBounds.width/granularity
	 */
	
	
	Slider rectangleGranularitySlider; // The slider to specify the grid's granularity
	Button gridGranularitySubmit; // The button to submit the specified slider entry
	float min, max; // The minimum and maximum values of the slider/granularity
	bool isPressed; // Represents the state of the tab (pressed/unpressed)
	bool isDragging; // Indicates whether the slider is currently being dragged
	bool gridConfigureMode = false; // Flag to track when the user
									/// \}
};


/**
 * Consider implementing the vector grid to be used globally with an active and inactive mode, such that the vector grid
 * can be used for function callbacks at simulation initialization while minimally inhibiting computational performance
 *
 */















class RectangularSelectionWindow
{
public:
	/// ------------- Constructors -------------
	/// \{
	RectangularSelectionWindow(); // Basic constructor that initializes an interface window with a default templated label, position, size, and table manager(s).
	RectangularSelectionWindow(std::string _label, float _x, float _y, float _w, float _h); // Constructor that initializes an interface window with a label and specific position and size.
	RectangularSelectionWindow(std::string _label, float _x, float _y, float _w, float _h, TableManager *_tableManager); // Constructor that initializes an interface window with a label, specific position and size, and a table manager.
																														 /// \}
	
	
	
	/// ------------- Setters -------------
	/// \{
	void setAnchorPosition(ofVec2f rectPos); // Sets the position of the interface window
	void setWindow(ofVec2f rectPos, ofVec2f rectSize); // Sets the position and size of the interface window
													   /// \}
	
	
	/// ------------- Callbacks -------------
	/// \{
	void setOnClick(std::function<void()> callback); // Sets the callback function for click events
													 /// \}
	
	
	
	/// ------------- User Interaction -------------
	/// \{
	void draw(); // Draws the interface window on the screen
	void mousePressed(int x, int y, int button); // Handles the mouse pressed event
	void mouseReleased(int x, int y, int button); // Handles the mouse released event
												  /// \}
	
	
	
	
	/// ------------- Rectangular Selection Window Attributes -------------
	/// \{
	Tooltip toolTip; // Tooltip to be displayed when the mouse hovers over the button.
	ofRectangle interfaceWindow; // Represents the size and position of the screen
	bool isSelecting; // Indicates whether the user is currently engaged with the selection process dictating the window.
	bool unselected;
	bool selectionVerified;
	std::string screenLabel; // The label displayed on the screen
	std::function<void()> onClick; // Callback function for click events
	
	
	/// The entire canvas of the selection window will be accomodated by the RectangularGridDragSelection object 'selectionWindow'.
	RectangularGridDragSelection selectionWindow;
	/// \}
};

