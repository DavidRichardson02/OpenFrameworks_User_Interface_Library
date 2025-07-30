## OpenFrameworks UI Library

A **header‑only, event‑driven collection of reusable UI widgets for C++/openFrameworks**.  
Drop the headers into any oF sketch and you instantly gain modern GUI elements—no external addons, XML layouts or drag‑and‑drop editors required.

### What’s inside
| Module | Purpose |
| ------ | ------- |
| **InputControls** (Button, Toggle, TextField, Tab) | Core click / type widgets with callback hooks and value validation. |
| **NavigationalComponents** | Sliders & Tables that auto‑layout, resize and nest for complex panels. |
| **InformationalComponents** | Tooltips and drawing helpers that adapt to message length and screen quadrants. |
| **TableManager** | Packs multiple tables into rows/columns, handles focus mode, window‑resize and callback propagation. |
| **DrawingUtilities / StatisticalMethods** | Lightweight helpers for vector math, plotting and descriptive stats (optional). |
| **ofApp demo** | A minimal sketch illustrating instantiation, event forwarding and logging.

### Highlights
* **Pure C++** – each widget is a self‑contained class; include only what you need.  
* **Zero dependencies** – relies solely on openFrameworks’ `<ofMain.h>` types.  
* **Dynamic layout** – widgets reposition and scale to window size & content.  
* **Callback‑first API** – bind lambdas or std::function objects for immediate reactions.  
* **Typed validation** – TextField enforces numeric ranges and precision at runtime.

### Quick start
```cpp
#include "InputControls.hpp"   // or any other header you need

class ofApp : public ofBaseApp {
    Button   runBtn;
    Toggle   liveMode;
    double   speed = 1.0;
    TextField speedField;

    void setup() {
        runBtn   = Button("Run",        50, 50, 120, 40,
                          []{ ofLogNotice() << "Simulation running"; });
        liveMode = Toggle("Live",       50,120, 120, 40, false);
        speedField = TextField("Speed", 50,190, 140, 40, 0, 10, speed, 2);
    }

    void draw() {
        runBtn.draw(); liveMode.draw(); speedField.draw();
    }

    void mousePressed(int x,int y,int button){ runBtn.mousePressed(x,y,button);
                                               liveMode.mousePressed(x,y,button);
                                               speedField.mousePressed(x,y,button); }
    void keyReleased(int key){ speedField.keyReleased(key); }
};
