# 🚀 Moon Landing — OpenGL Computer Graphics Project

An animated 2D scene built with **C++ and OpenGL/GLUT**, created for a Computer Graphics course project. The program simulates a rocket launch from Earth, its journey through space, and a landing sequence — all drawn using primitive shapes (circles, triangles, quads, polygons) and simple physics-based animation.

---

## 🎬 What It Does

The project has **three animated scenes**, and you switch between them using your keyboard while the program is running.

| Scene | Trigger | What You See |
|-------|---------|--------------|
| **1. Launch Site** | *(default, starts automatically)* | A countdown timer, a rocket on a launch pad, a river with boats, moving clouds, birds, trees with falling fruit, houses, antennas, and a running car — a full animated town scene. |
| **2. Space Journey** | Press **`A`** | The rocket separates into two stages and flies past Earth, the Moon, Mercury, Venus, asteroids, satellites, UFOs, and a comet, all set against a field of twinkling stars. |
| **3. Landing & Ending** | Press **`S`** | A second rocket animation with deploying landing stairs, a robot ("Scout") that walks out and plants a flag, a monster character, and a closing "THE END" title card. |

---

## 🛠️ Built With

- **Language:** C++
- **Graphics library:** OpenGL (`GL/glut.h`, `freeglut`)
- **Windows APIs used:** `windows.h`, `mmsystem.h` (for playing a background sound file)
- **IDE / Build system:** Code::Blocks (`Sample1.cbp` project file)
- **Compiler:** GCC / MinGW (Windows)

---

## 📁 Project Structure

```
Graphics_Project-main/
├── Sample1 (1)/
│   └── MoonLanding/
│       ├── main.cpp           # All source code (single file)
│       ├── Sample1.cbp        # Code::Blocks project file
│       ├── Sample1.depend     # Build dependency cache
│       ├── Sample1.layout     # Editor layout (safe to ignore)
│       ├── bin/Debug/
│       │   ├── Sample1.exe    # Compiled executable
│       │   └── al.wav         # Background sound played on launch
│       └── obj/Debug/         # Compiled object files
├── Project_report/
│   └── Title.docx             # Project report / cover page
└── ScreenShort/
    ├── 1no.jpeg               # Screenshot — Launch site scene
    ├── 2no.png                # Screenshot — Space journey scene
    └── 3no.jpg                # Screenshot — Landing / ending scene
```

---

## ▶️ How to Run

### Option A — Just run it (Windows)
1. Go to `Sample1 (1)/MoonLanding/bin/Debug/`
2. Double-click **`Sample1.exe`**
3. Make sure `al.wav` stays in the same folder — the program plays it on startup.

### Option B — Open and build in Code::Blocks
1. Install [Code::Blocks](http://www.codeblocks.org/) with the **MinGW** compiler.
2. Install **FreeGLUT** and make sure your Code::Blocks compiler settings point to its `include` and `lib` folders (this project expects them under `C:/Program Files/CodeBlocks/MinGW/...`).
3. Open **`Sample1.cbp`** in Code::Blocks.
4. Press **Build and Run** (`F9`).

### Option C — Compile manually with g++
```bash
g++ main.cpp -o MoonLanding -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
```
> ⚠️ This project uses Windows-only headers (`windows.h`, `mmsystem.h`), so it will only compile and run on **Windows**.

---

## ⌨️ Controls

| Key | Action |
|-----|--------|
| `A` | Switch to the **Space Journey** scene |
| `S` | Switch to the **Landing / Ending** scene |
| *(none)* | The **Launch Site** scene plays automatically when the program starts |

---

## ✨ Key Features / Techniques Demonstrated

- Custom shape-drawing helper functions (`drawCircleA`, `drawEllipseA`, `drawTriangleA`, `drawQuadA`, `drawStarM`, etc.) built from raw OpenGL primitives (`GL_TRIANGLE_FAN`, `GL_QUADS`, `GL_POLYGON`, `GL_LINES`).
- Frame-by-frame animation using `glutIdleFunc` and `glutTimerFunc`.
- Multi-stage rocket with animated flame effects and stage separation.
- Orbiting/rotating celestial bodies (Earth, Moon, Venus, Mercury) using `glPushMatrix` / `glTranslatef` / `glRotatef` transformations.
- A simple scene-management system (`scene` variable) that switches between three independent `display()` functions based on keyboard input.
- A basic countdown timer rendered with `glutBitmapCharacter`.
- Background audio playback via the Windows Multimedia API (`sndPlaySound`).

---

## 📄 Project Report

See [`Project_report/Title.docx`](Graphics_Project-main/Project_report/Title.docx) for the accompanying written report/cover page.

---

## 📌 Notes

- This was built as an academic exercise to practice fundamental OpenGL concepts (transformations, primitives, animation loops) rather than as production-grade rendering code — so the source is a single large `main.cpp` with many hand-tuned coordinates.
- Tested and intended to run on **Windows** with **Code::Blocks + MinGW + FreeGLUT**.
