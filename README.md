# Client Management System (CMS)

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat&logo=c%2B%2B)
![Qt](https://img.shields.io/badge/Qt-5.15-41CD52?style=flat&logo=qt)
![QMake](https://img.shields.io/badge/Build-QMake-brightgreen?style=flat)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=flat)
![Database](https://img.shields.io/badge/Storage-SQLite-003B57?style=flat&logo=sqlite)
![License](https://img.shields.io/badge/License-MIT-blue?style=flat)

A modular desktop application built with C++, Qt 5, and QML for managing client profiles, contact points, addresses, and appointments. The application follows an enterprise n-tier architecture separating presentation (QML/C++ bindings), core domain logic/models (`cm-lib`), and automated unit tests (`cm-tests`).

---

## Architecture Overview

The project is structured as a multi-tier Qt subdirs build:

- **`cm-ui`**: Front-end layer utilizing QML, custom controls, Font Awesome icons, and styling components. Exposes C++ view-controllers into the QML engine context.
- **`cm-lib`**: Core static/shared library containing:
  - **Controllers**: Application lifecycle (`MasterController`), navigation routing (`NavigationController`), command dispatching (`CommandController`), and database transactions (`DatabaseController`).
  - **Data Framework**: Extensible Entity-Component framework (`Entity`, `EntityCollection`) paired with property decorators (`StringDecorator`, `IntDecorator`, `DateTimeDecorator`, `EnumeratorDecorator`) supporting JSON serialization and validation.
  - **Models**: Business entities for `Client`, `Contact`, `Address`, `Appointment`, and `ClientSearch`.
  - **Networking & RSS**: Built-in HTTP client wrapper (`WebRequest`, `NetworkAccessManager`) and XML RSS feed parser for external news aggregation.
- **`cm-tests`**: Comprehensive unit testing suite based on the Qt Test framework covering model validation, data decorators, entity serialization, and controllers.
- **`installer`**: Windows deployment assets and Qt Installer Framework package configuration.

---

## Features

- **Client Directory**: Add, update, view, and search clients with real-time field validation.
- **Multi-Entity Relationships**: Supports multiple contact records, primary addresses, and appointment schedules per client.
- **Local Persistence**: Backed by embedded SQLite storage (`cm.sqlite`) with schema initialization and JSON entity mapping.
- **RSS News Feed**: Integrated background RSS feed parser (`cm-lib/source/rss`) with custom delegate cards and browser links.
- **Modern QML Interface**: Custom themed layout featuring collapsible side navigation, command action bars, responsive forms, and date-time pickers.

---

## Requirements

- **Qt Framework**: Qt 5.15.x (Qt Core, Qt GUI, Qt Quick, Qt Qml, Qt Network, Qt Sql, Qt Xml)
- **Compiler**: C++17 compliant compiler (MSVC 2019+, GCC 9+, or Clang 10+)
- **Build System**: QMake

---

## Build & Installation

### 1. Clone the repository
```bash
git clone https://github.com/eng-muhammad-hamza/cms.git
cd cms
```

### 2. Build via Qt Creator
1. Open `cm.pro` in Qt Creator.
2. Select your Qt 5.15 desktop kit.
3. Run **Build All** or press `Ctrl + B`.
4. Run `cm-ui` target (`Ctrl + R`).

### 3. Build via Command Line
```bash
# On Linux/macOS
qmake cm.pro -spec linux-g++
make -j$(nproc)

# On Windows (cmd / MinGW / MSVC prompt)
qmake cm.pro
nmake   # or mingw32-make / make
```

Compiled binaries and intermediate object files are placed under the `binaries/` directory based on the active target platform configuration.

---

## Running Unit Tests

Unit tests are compiled as part of the `cm-tests` subproject:

```bash
cd cm-tests
qmake cm-tests.pro
make
./binaries/.../cm-tests
```

---

## Configuration & Notes

- **Database**: SQLite database file (`cm.sqlite`) is created automatically in the working directory on first launch.
- **RSS Parser Source**: The RSS feed endpoint can be adjusted in `MasterController` / networking controllers (defaults to BBC News feed).

---

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
