# InterfaceTemplate Usage Guide

This document provides comprehensive examples for using the `InterfaceWindow` and `Template` classes from the OpenFrameworks User Interface Library.

---

## InterfaceWindow Class

The `InterfaceWindow` class is a comprehensive container for organizing complex UI layouts with TableManager integration, tooltips, and drag selection capabilities.

### Basic Usage

#### Creating a Simple Interface Window

```cpp
#include "InterfaceTemplate.hpp"

// In your ofApp.h
InterfaceWindow* mainWindow;

// In your ofApp::setup()
mainWindow = new InterfaceWindow("Main Interface", 50, 50, 600, 400);
```

#### Creating an Interface Window with a TableManager

```cpp
// Create a table manager
TableManager* uiManager = new TableManager(0, "UI Manager", 60, 60, 15, 15);

// Create tables and add UI elements
Table* controlsTable = new Table("Controls", 0, 0, 200, 20, true);
Button* btn = new Button("Click Me", 0, 0, 100, 30);
controlsTable->addButtonElement(btn);
uiManager->addTable(controlsTable);

// Create interface window with the table manager
InterfaceWindow* window = new InterfaceWindow(
    "Main Window",     // Label
    100, 100,          // Position (x, y)
    800, 600,          // Size (width, height)
    uiManager          // TableManager pointer
);
```

### Setting Position and Size

```cpp
// Set only the position (maintains current size)
window->setAnchorPosition(ofVec2f(200, 150));

// Set both position and size
window->setWindow(ofVec2f(100, 100), ofVec2f(1000, 800));
```

### Adding Custom Callbacks

```cpp
// Set a callback function that triggers on click
window->onClick = [&]() {
    ofLogNotice("InterfaceWindow") << "Window clicked!";
    // Add your custom logic here
};
```

### Rendering and Event Handling

```cpp
// In your ofApp::draw()
void ofApp::draw()
{
    ofBackground(40);
    mainWindow->draw();
}

// In your ofApp::mousePressed()
void ofApp::mousePressed(int x, int y, int button)
{
    mainWindow->mousePressed(x, y, button);
}

// In your ofApp::mouseReleased()
void ofApp::mouseReleased(int x, int y, int button)
{
    mainWindow->mouseReleased(x, y, button);
}
```

### Accessing Components

```cpp
// Access and configure the tooltip
mainWindow->toolTip.setMessage("This is the main application window");

// Access the user rectangle for drag selection
// The RectangularGridDragSelection component is available as:
mainWindow->userRectangle.draw();
```

---

## Template Class

The `Template` class provides a flexible, reusable widget foundation for creating custom UI elements with standard interaction patterns.

### Basic Usage

#### Creating a Simple Template Widget

```cpp
#include "InterfaceTemplate.hpp"

// In your ofApp.h
Template* customWidget;

// In your ofApp::setup()
customWidget = new Template("My Widget", 100, 100, 200, 80);
```

#### Creating a Template with a Callback

```cpp
Template* actionButton = new Template(
    "Action Button",          // Label
    150, 200,                 // Position (x, y)
    180, 60,                  // Size (width, height)
    [&]() {                   // Callback function
        ofLogNotice("Template") << "Action button clicked!";
        performCustomAction();
    }
);
```

### Positioning and Sizing

```cpp
// Set only the position (maintains current size)
customWidget->setPosition(ofVec2f(300, 250));

// Set both position and size
customWidget->set(ofVec2f(400, 300), ofVec2f(250, 100));
```

### Custom Tooltips

```cpp
// Configure the tooltip for the template
customWidget->toolTip.setMessage("Click this widget to perform an action");
customWidget->toolTip.setPosition(
    customWidget->interfaceWindow.x + 10,
    customWidget->interfaceWindow.y - 30
);
```

### Event Handling

```cpp
// In your ofApp::draw()
void ofApp::draw()
{
    ofBackground(40);
    customWidget->draw();
}

// In your ofApp::mousePressed()
void ofApp::mousePressed(int x, int y, int button)
{
    customWidget->mousePressed(x, y, button);
}

// In your ofApp::mouseReleased()
void ofApp::mouseReleased(int x, int y, int button)
{
    customWidget->mouseReleased(x, y, button);
}
```

### Checking Interaction State

```cpp
// Check if the user is currently interacting with the template
if (customWidget->isInterfacing)
{
    ofLogNotice("Template") << "User is interacting with the widget";
    // Perform actions while user interacts
}
```

---

## Advanced Examples

### Multiple Templates in a Grid Layout

```cpp
std::vector<Template*> templateGrid;

// Create a 3x3 grid of template widgets
for (int row = 0; row < 3; row++)
{
    for (int col = 0; col < 3; col++)
    {
        float x = 100 + col * 220;
        float y = 100 + row * 120;
        
        std::string label = "Widget " + ofToString(row * 3 + col + 1);
        
        Template* widget = new Template(
            label,
            x, y,
            200, 100,
            [row, col]() {
                ofLogNotice("Grid") << "Clicked widget at [" << row << "," << col << "]";
            }
        );
        
        templateGrid.push_back(widget);
    }
}

// Draw all templates
void ofApp::draw()
{
    for (auto widget : templateGrid)
    {
        widget->draw();
    }
}
```

### InterfaceWindow with Dynamic Content

```cpp
class DynamicInterface
{
public:
    InterfaceWindow* window;
    TableManager* manager;
    
    void setup()
    {
        // Create table manager
        manager = new TableManager(0, "Dynamic UI", 110, 110, 15, 15);
        
        // Create interface window
        window = new InterfaceWindow("Dynamic Window", 100, 100, 700, 500, manager);
        
        // Configure tooltip
        window->toolTip.setMessage("This window contains dynamic UI elements");
    }
    
    void addControls(std::vector<Button*>& buttons)
    {
        Table* dynamicTable = new Table("Dynamic Controls", 0, 0, 200, 20, true);
        
        for (auto btn : buttons)
        {
            dynamicTable->addButtonElement(btn);
        }
        
        manager->addTable(dynamicTable);
    }
    
    void draw()
    {
        window->draw();
    }
};
```

### Custom Template Subclass

```cpp
// Create a specialized template by composition
class StatusIndicator
{
public:
    Template* display;
    bool status;
    
    StatusIndicator(std::string label, float x, float y)
    {
        status = false;
        display = new Template(label, x, y, 150, 50, [&]() {
            toggleStatus();
        });
    }
    
    void toggleStatus()
    {
        status = !status;
        std::string msg = status ? "Status: ACTIVE" : "Status: INACTIVE";
        display->toolTip.setMessage(msg);
        ofLogNotice("StatusIndicator") << msg;
    }
    
    void draw()
    {
        display->draw();
        
        // Draw custom status indicator
        if (status)
        {
            ofSetColor(0, 255, 0); // Green for active
        }
        else
        {
            ofSetColor(255, 0, 0); // Red for inactive
        }
        ofDrawCircle(
            display->interfaceWindow.x + 20,
            display->interfaceWindow.y + 25,
            8
        );
    }
};
```

---

## Best Practices

### 1. Memory Management
- Always use proper memory management (smart pointers or manual cleanup)
- Clean up in `ofApp::exit()` or class destructors

```cpp
void ofApp::exit()
{
    delete mainWindow;
    delete customWidget;
}
```

### 2. Event Routing
- Route all mouse events through your top-level containers
- Let parent components handle event propagation to children

### 3. Positioning
- Use `setPosition()` when you only need to move elements
- Use `set()` or `setWindow()` when changing both position and size

### 4. Tooltips
- Configure tooltips immediately after creating widgets
- Use descriptive messages to guide users

### 5. Callbacks
- Keep callback functions simple and focused
- Use lambda captures carefully to avoid dangling references

---

## Integration with Existing UI

### Adding InterfaceWindow to TableManager

```cpp
// While InterfaceWindow contains a TableManager,
// you typically use it as a top-level container
InterfaceWindow* mainUI = new InterfaceWindow(
    "Main UI",
    0, 0,
    ofGetWidth(), ofGetHeight()
);

// Create and configure the internal table manager
TableManager* internalManager = new TableManager(0, "Controls", 20, 20, 15, 15);
mainUI->tableManager = internalManager;

// Add tables to the internal manager
Table* settingsTable = new Table("Settings", 0, 0, 200, 20, true);
internalManager->addTable(settingsTable);
```

### Using Templates as Custom Buttons

```cpp
// Templates can serve as enhanced button alternatives
Template* enhancedBtn = new Template(
    "Enhanced Action",
    100, 300,
    220, 80,
    [&]() {
        // Complex action logic
        performDataAnalysis();
        updateVisualization();
        saveResults();
    }
);

// Configure for button-like behavior
enhancedBtn->toolTip.setMessage("Click to perform comprehensive analysis");
```

---

## Troubleshooting

### Widget Not Responding to Mouse Events
- Ensure you're calling `mousePressed()` and `mouseReleased()` in ofApp
- Check that the widget's position is within the visible screen area
- Verify that coordinates are being passed correctly

### Tooltip Not Visible
- Call `toolTip.toggleVisibility()` or check tooltip positioning
- Ensure tooltip is being drawn (included in widget's `draw()` method)

### InterfaceWindow Not Rendering TableManager
- Verify that `tableManager` pointer is not null
- Ensure tables have been added to the manager
- Check that `tableManager->draw()` is being called

---

## Additional Resources

- See `InputControls.hpp` for examples of Button, Toggle, and TextField
- See `NavigationalComponents.hpp` for Slider, Table, and TableManager details
- See `InformationalComponents.hpp` for Tooltip implementation details

---

## Summary

The `InterfaceWindow` and `Template` classes provide robust, reusable foundations for building complex user interfaces in openFrameworks. They follow the library's conventions for event handling, rendering, and state management, making them easy to integrate with existing UI components.
