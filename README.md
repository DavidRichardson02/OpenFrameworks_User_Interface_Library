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
   Button startBtn("Start",20,20,90,25, [](){ ofLogNotice() << "Simulation started"; });
   Slider gravity("G", 20,60,180,15, 1e-5f, 1e-3f, G, 6);
   ```
3. **Forward events** from openFrameworks:

   ```cpp
   void ofApp::mousePressed(int x,int y,int b){ startBtn.mousePressed(x,y,b); gravity.mousePressed(x,y,b); }
   void ofApp::draw(){ startBtn.draw(); gravity.draw(); }
   ```

---
