# GameCheck — PC Compatibility Checker

## Build and Run

1. Open a terminal in the project root.
2. Create a build directory and configure with CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```
3. Build the application:
   ```bash
   cmake --build .
   ```
4. Run the executable `GameCheck`.

## OOP Concepts in the App

- Abstraction: `Hardware` defines a generic hardware interface with `getPerformanceScore()` and `getName()`.
- Inheritance: `CPU`, `GPU`, `RAM`, and `Storage` inherit from `Hardware`.
- Polymorphism: Each hardware subclass overrides `getPerformanceScore()` to calculate its own score.
- Encapsulation: Hardware fields are private, with getters and setters exposing values safely.
- Composition: `Computer` owns `CPU`, `GPU`, `RAM`, and `Storage` by value.

## Class Mapping

- `Hardware` — abstract base class for all components.
- `CPU`, `GPU`, `RAM`, `Storage` — concrete hardware types.
- `Computer` — assembles hardware components into one rig.
- `GameRequirement` / `HardwareSpec` — store game minimum and recommended requirements.
- `CompatibilityChecker` — evaluates a PC against a game and returns detailed results.
- `GamesDB` — hardcoded database of CPU, GPU, and game requirements.

## UI and Styling

- All visual styling is defined in `styles.qss`.
- The UI uses a dark theme with cyan accents and clearly delineated cards.
- Game buttons are created dynamically and highlight when selected.
- The result panel updates in place and shows a verdict emoji, badge, component bars, and score cards.

## Signals and Slots

- `checkButton::clicked` → `MainWindow::onCheckClicked()`
- Game button `clicked` → `MainWindow::onGameSelected()`
- `cpuComboBox::currentIndexChanged`, `gpuComboBox::currentIndexChanged`, `ramSpinBox::valueChanged`, `storageSpinBox::valueChanged`, and radio button toggles all connect to `MainWindow::validateInputs()`.

## Project Files

- `main.cpp` — loads styles and starts the Qt application.
- `mainwindow.ui` — defines the layout and widget names.
- `mainwindow.cpp` / `mainwindow.h` — UI logic and interaction.
- `hardware.h` — hardware abstraction and component classes.
- `checker.h` — compatibility evaluation and result types.
- `games_db.h` — hardcoded CPU, GPU, and game requirement database.
- `styles.qss` — dark theme styling.
