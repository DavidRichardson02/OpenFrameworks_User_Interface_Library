# OpenFrameworks User Interface Library

A lightweight, header‑only collection of reusable UI widgets designed for rapid prototyping and scientific visualisation inside an **openFrameworks** application.


At its core the library supplies **buttons, toggles, text fields, tabs, sliders, table, tablemanagers, tooltips, and drag‑selection utilities**, each responsible for its own drawing, input handling and optional callbacks — so they can be dropped straight into an `ofApp` without extra wiring.nDrop the headers into any oF sketch and you instantly gain modern GUI elements—no external addons, XML layouts or drag‑and‑drop editors required.
Each control lives in its own class, so you can include just what you need or extend the base types.


---

## Features at a glance

| Module                      | Key classes                                                                                     | Purpose                                                   |
| --------------------------- | ----------------------------------------------------------------------------------------------- | --------------------------------------------------------- |
| **InputControls**           | `Button`, `Toggle`, `TextField`, `Tab`                                                          | Basic widgets for direct input w/callbacks & validation.  |
| **NavigationalComponents**  | `Slider`, `Table`, `TableManager`, `RectangularGridDragSelection`, `RectangularSelectionWindow` | Higher‑level containers, auto-layout, drag‑selection pane |
| **InformationalComponents** | `Tooltip`, `InterfaceWindow`                                                                    | Tooltips that adapt to message length & screen quadrants. |


> **Work‑in‑Progress status** – several navigation classes are still being hardened (percent complete numbers in the header) but are fully usable today for internal tools or prototypes.

---

<br>



## Highlights
* **Rich widget set** – buttons, toggles, text fields, sliders, tabbed tables, tool-tips and more  
* **Modular design** – every widget is a self-contained class wired together by your app; include only what you need.
* **Dynamic layout** – widgets reposition and scale to window size & content.  
* **Zero dependencies** – relies solely on openFrameworks’ `<ofMain.h>` types.  
* **Event-driven callbacks** – pass lambdas or `std::function` objects for button presses, toggle changes, slider drags, etc.  
* **Fully programmatic** – no XML layout or IDE files; object lifetimes are governed by RAII and the parent-child pattern familiar to openFrameworks  
* **Lightweight** – depends only on openFrameworks core; compiles with oF 0.12 on macOS & Windows.
* **Typed validation** – TextField enforces numeric ranges and precision at runtime.




<br>
<br>





## Architectural overview

* **Self‑contained widgets** – every control stores an `ofRectangle` for layout, renders itself in `draw()`, and exposes `mousePressed / mouseReleased` for interactivity.
* **Callback‑ready** – supply any `std::function<void()>` to react on click or state change.

<br>

### 1. InputControls
* **Button**: Momentary push‑button with rounded rect render and optional onClick lambda.
* **Toggle**: State‑holding button that fires its callback every frame while on.
* **TextField**: Validated numeric entry with reset button and precision control.
* **Tab**: 4‑way quadrant tab used to open/close panels.



### 2. NavigationalComponents
* **Slider**: Linear parameter control for continuous numeric input with configurable precision; maps value ↔ position with ofMap().
* **Table**: automatic vertical stacking of mixed widgets; recalculates its own bounding box and child positions each frame for responsive layouts.
* **TableManager**: orchestrates multiple tables into rows/columns, allowing *focus‑mode*, dynamic resizing, bulk event forwarding, and callback propagation.
* **RectangularGridDragSelection**: Lets users click‑and‑drag to define a square selection-region, then refine grid granularity with an embedded slider & submit button.
* **RectangularSelectionWindow**: Screen‑sized overlay that embeds the grid selector, table manager for parameter pickers, and attaches callbacks.

  
### 3. InformationalComponents
* **Tooltip**: tiny “?” icon that toggles an on‑screen message panel; ideal for explaining exotic physics parameters to end‑users.




<br>

### Event Flow

* **Mouse/key events** enter ofApp and are forwarded to the top‑level TableManager.
* **TableManager routes** to the open Table whose tableRect contains the cursor.
* **Each Table** bubbles events down its element vectors (sliderElements, buttonElements, etc.).
* **Widgets mutate** internal state (e.g., isPressed) and invoke bound callbacks.
* **callbackUpdate()** runs once per frame so toggles can fire continuously.


---


<br>
<br>

## Example: building a parameter panel

```cpp
// gravity, theta and dt are the simulation variables we want to expose
Table paramTable("Simulation", 30, 30, 220, 20, true);

Slider thetaS("Barnes–Hut θ", 0,0,200,15, 0.3f, 1.0f, theta, 3);
Slider dtS   ("Δt",           0,0,200,15, 1/240.f, 1/30.f, dt, 6);
TextField gTF("G",            0,0,200,17, 6.67e-11, 1e-8,  G,  9);

paramTable.addSliderElement(&thetaS);
paramTable.addSliderElement(&dtS);
paramTable.addTextFieldElement(&gTF);

// Optional: pack multiple tables
TableManager uiManager(0,"UI");
uiManager.addTable(&paramTable);
```

The table auto‑sizes to the widest label/value pair and vertically arranges all elements; no manual pixel maths required.

---


<br>
<br>


## Building & compatibility

| Requirement        | Version                                           |
| ------------------ | ------------------------------------------------- |
| **openFrameworks** | 0.10.0 or newer (tested on 0.12.0)                |
| **C++ standard**   | C++17 (for `std::optional`, `std::function` etc.) |
| **Platforms**      | macOS 10.15+, Windows 10, Linux (desktop)         |

Simply compile as part of your existing oF project – no additional libraries or build steps.

---


<br>
<br>


## Roadmap

* [ ] Finish auto‑layout edge‑cases for `Table` (minor mis‑alignment)
* [ ] Expose theme/skin system
* [ ] Add unit tests & CI



<br>
<br>







## Quick start

```bash
# inside your existing openFrameworks project
cp OpenFrameworks_User_Interface_Library/src/*.hpp src/
cp OpenFrameworks_User_Interface_Library/src/*.cpp src/
```

1. **Add headers** to your `ofApp.h`:

   ```cpp
   #include "InputControls.hpp"
   #include "NavigationalComponents.hpp"
   ```
2. **Instantiate** controls in `setup()`:

   ```cpp
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
   ```
3. **Forward events** from openFrameworks:

   ```cpp
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
   ```



<br />
<br />




https://github.com/user-attachments/assets/5ae777ff-ad65-4e6a-a4c2-846294fa7728




<br />
<br />




   

---


<br />
<br />

<br />
<br />



## Demonstrating UI Implementations

Adding interactive functionality to a real-time 2D Barnes-Hut N-body simulator using the widgets and resources provided, and achieved via a modularized implementation of the UI elements in a hierarchical structure of element management such that a single instantation of a 'TableManager' object will be responsible for all UI in the simulation and will require no additional assistance after it has been initialized with the UI elements.


<br />
<br />



https://github.com/user-attachments/assets/e80f2876-66ae-4536-9ff8-328aba6bec21



<br />
<br />








https://github.com/user-attachments/assets/e2ff2d4c-7d2b-46ac-8520-f14f23ee2291




<br />
<br />


<br />

Basically, TableManager manages the individual tables, the individual tables are made up of UI elements that execute similar functionalities, and the individual UI elements each handle a single task(defined when initializing using a lambda function) that is executed when the UI element is interacted with(i.e., when a button is clicked, a toggle is toggled, a slider is adjusted, etc.). Additionally, the tables also serve to group together UI elements based on broad categories of their purpose, for example, there is a table for handling visualization of parameters of the quadtree, a table for handling visualization of body data(like angular orientation), a table for handling visualization of some physics related stuff(like the gravitational vector field and the relative potential energy field), a special case table for custom galaxy creation(menus to begin, models of galaxies to distrubute bodies initial positions by to be chosen from, sliders for the number of bodies and their properties, etc.), as well as a few more tables, the main ones of which are involved in stuff like tweaking simulation parameters and interacting with bodies.

<br />

My main difficulty in making and implementing the above described UI is in defining the function callbacks for each UI element while maintaning the hierarchical structure grouping elements without necessitating too much dedicated data(that is otherwise irrelevant to the rest of the program). The other two less tricky problems are minimally inhibiting the performance of the simulation when the UI is not being used and completing all dynamic visualization with a single isolated coordinate system transform, where dynamic visualization just means the parts of the simulation that will be visualized relative to the user's dynamic configuration of the scene, basically the easiest way to understand what this means is by thinking of the window that the simulation is occuring in as being nothing but a viewing port through which you can look into the simulation, while the simulation itself can be thought of as happening on the coordinate system your looking into(kind of like how you can look at apple maps on your phone and zoom in/out and slide around, but here instead of the viewing port being your phone it's just the app window), where the affect of moving around your perspective is achieved by scaling and transforming the coordinate system(and by extension all the things in it) to reflect whatever configuration the user interaction specify.




