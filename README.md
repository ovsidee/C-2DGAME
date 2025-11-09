# 2D Game

A 2D game built in C++ based loosely on the mechanics of *The Binding of Isaac*.  
This project uses the [SFML](https://www.sfml-dev.org/) library for graphics & window handling, and [fmt](https://github.com/fmtlib/fmt) for efficient string formatting.  
(Currently under active development.)

---

## 🧩 Features

- Basic player movement and controls  
- Enemies / obstacles / items in game levels  
- Level structure (rooms) and transitions  
- UI elements (menus, buttons)  
- Use of SFML for rendering and input  
- Use of fmt for readable and efficient logging/formatting  
- CMake based build system for cross-platform support  

---

## 📂 Repository structure

C-2DGAME/
├── BackgroundImages/ – background assets
├── Buttons/ – UI button assets
├── Character/ – player character sprites
├── Enemies/ – enemy character sprites
├── Font/ – font assets
├── LevelNumber/ – level numbering assets
├── Textures/ – other textures
├── CMakeLists.txt – CMake build configuration
├── main.cpp – entry point
├── Game.h / Game.cpp – main game loop & state handling
├── Player.h / Player.cpp – player logic
├── Enemy.h / Enemy.cpp – generic enemy logic
├── … – other entity types: Boss, Magician, NightBorn, Items, Obstacles, etc
└── README.md – this file

---

## How to run?

### Prerequisites  
You will need:  
- A C++17-compliant compiler (e.g., clang, gcc, MSVC)  
- CMake (version ≥ 3.10)  
- SFML library (graphics, window, system)  
- fmt library  

### Building  
1. Clone the repository:  
   ```bash
   git clone https://github.com/ovsidee/C-2DGAME.git
   cd C-2DGAME ```
2. Create a build directory and configure:
```mkdir build && cd build ```
```cmake```
3. Build the game:
```cmake --build .  ```
After building, run the executable generated (for example C2DGAME.exe or ./C2DGAME on Linux/Mac).
Make sure asset folders (BackgroundImages, Buttons, Textures, etc.) are accessible relative to the executable’s working directory.

🎮 Controls & Gameplay

[Arrow keys / WASD] — Move the player

[Mouse1] — Attack

[M] — Skip the level when allowed

Navigate through rooms, collect items, avoid or defeat enemies.

