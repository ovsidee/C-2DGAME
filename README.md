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


---
## Pictures of a gameplay:

*Main menu, start of the game*
<img width="1281" height="744" alt="image" src="https://github.com/user-attachments/assets/a9c5c934-8200-40bd-9420-6430a7fb7160" />

*Hitting the button instructions of the game menu*
<img width="1281" height="743" alt="image" src="https://github.com/user-attachments/assets/6b41c9b1-f9f4-4a53-854b-e7d682f64a37" />

*Hitting the button *New Game**
<img width="1276" height="742" alt="image" src="https://github.com/user-attachments/assets/cc62be5a-5540-4f5d-8818-0c922fe3c365" />

*Taking some item interatction plus hitting animation*
<img width="1274" height="744" alt="image" src="https://github.com/user-attachments/assets/e793bbe5-7d45-4846-972a-4ba8f2d6b417" />

*Hitting space to roll the player*
<img width="1281" height="745" alt="image" src="https://github.com/user-attachments/assets/cda71f62-a2fa-46ec-96f3-f39dac3d24cb" />

*Facing the 2-nd level of the game*
<img width="1284" height="744" alt="image" src="https://github.com/user-attachments/assets/bc03a5b3-b924-4074-9cdb-57d9f75cbf79" />

*Getting ready to face *Boss* level*
<img width="1277" height="748" alt="image" src="https://github.com/user-attachments/assets/3878744c-a186-4fd2-b524-8b14fe1505be" />

*Boss*
<img width="1282" height="744" alt="image" src="https://github.com/user-attachments/assets/1a08e179-2284-4a73-aab9-bae164f7676a" />

*After killing the Boss*
<img width="1276" height="742" alt="image" src="https://github.com/user-attachments/assets/7331b83c-b44a-49aa-9434-12cd630f352c" />

*Random spawning of the obstacles and items*
*1*
<img width="1271" height="739" alt="image" src="https://github.com/user-attachments/assets/d634b49b-1202-4f73-960d-cea48dc279c0" />
*2*
<img width="1269" height="738" alt="image" src="https://github.com/user-attachments/assets/d54f6b31-1804-4f94-a4f3-a9e999ba1688" />
*and there is so much other variations.. try it yourself :)*
---

## 📂 Repository structure

```text
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
```

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

