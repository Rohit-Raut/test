# Bismuth-207 Purity Monitor

![License](https://img.shields.io/badge/license-MIT-blue.svg)

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)

## Introduction

**Bismuth-207 Purity Monitor** is a comprehensive simulation toolkit developed to model and analyze the behavior of Bismuth-207 radioactive sources within a cylindrical drift chamber-based purity monitor. Utilizing the powerful [Geant4](https://geant4.web.cern.ch/) framework, this project aims to provide accurate simulations of radioactive decay processes, electron emission, and their interactions within liquid argon (LAr) environments. The simulation is instrumental in assessing and ensuring the purity of LAr by measuring free electron lifetimes, which are critical for applications in particle physics experiments and dark matter detection.

## Features

- **Bismuth-207 Source Modeling:** Accurately represents the geometry, encapsulation, and placement of \(^{207}\text{Bi}\) sources within the detector setup.
- **Radioactive Decay Simulation:** Utilizes Geant4's built-in radioactive decay capabilities to simulate decay processes, including emission of internal-conversion (IC) electrons and gamma rays.
- **Dynamic Activity Configuration:** Allows setting and adjusting the activity levels of the radioactive sources to study various operational scenarios.
- **Visualization Support:** Integrated with Geant4's visualization tools to render and inspect the detector geometry and decay events.
- **Modular Physics List:** Customizable physics list incorporating necessary processes for accurate simulation of particle interactions and decays.
- **Scalable Simulation Parameters:** Supports simulations with varying drift lengths and detector configurations to optimize sensitivity and measurement ranges.

## Installation

### Prerequisites

- **Operating System:** Linux, macOS, or Windows (with appropriate environment setup)
- **Compiler:** GCC (version 7.5 or higher) or Clang
- **CMake:** Version 3.10 or higher
- **Geant4:** Version 11.3.0 or higher (with `G4RadioactiveDecay` component)

### Steps

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/rohit-email/Bismuth-207-Purity-Monitor.git
    cd Bismuth-207-Purity-Monitor
    ```

2. **Set Up Geant4 Environment:**

    Ensure that Geant4 is installed and its environment variables are correctly set. You can source the Geant4 environment script:

    ```bash
    source /path/to/geant4-install/bin/geant4.sh
    ```

3. **Create a Build Directory:**

    ```bash
    mkdir build
    cd build
    ```

4. **Configure the Project with CMake:**

    ```bash
    cmake ..
    ```

    *If Geant4 is installed in a non-standard location, specify the Geant4 installation path:*

    ```bash
    cmake -DGeant4_DIR=/path/to/geant4-install/lib/Geant4-11.3.0 ../
    ```

5. **Build the Project:**

    ```bash
    make
    ```

6. **Verify the Installation:**

    After a successful build, an executable named `BismuthPurityMonitor` (or as specified) will be available in the `build` directory.

## Usage

### Running the Simulation

1. **Navigate to the Executable Directory:**

    ```bash
    cd build/bin
    ```

2. **Prepare a Visualization Macro (`vis.mac`):**

    Ensure that a `vis.mac` file is present with appropriate visualization commands. An example `vis.mac` is provided in the repository.

3. **Execute the Simulation:**

    ```bash
    ./BismuthPurityMonitor
    ```

    This will launch the Geant4 simulation with visualization support. The simulation parameters, such as activity and simulation time, can be adjusted in the `main.cc` file or via command-line arguments/macro files as implemented.

### Configuring Simulation Parameters

- **Activity Setting:**

    Modify the `activity_kBq` and `simulationTime_s` variables in `main.cc` to set the desired source activity and simulation duration.

- **Detector Configuration:**

    Adjust detector geometry parameters in `DetectorConstruction.cc` to model different detector setups or source placements.

## Project Structure






- **CMakeLists.txt:** CMake configuration file for building the project.
- **README.md:** Project documentation.
- **LICENSE:** License information.
- **include/**: Header files defining classes and interfaces.
- **src/**: Source files implementing the simulation logic.
- **vis.mac:** Geant4 macro file for visualization settings.

## Contributing

Contributions are welcome! Whether it's reporting bugs, suggesting enhancements, or submitting pull requests, your input is invaluable to improving the project.

### How to Contribute

1. **Fork the Repository:**

    Click the "Fork" button on the GitHub repository page to create a personal copy.

2. **Clone Your Fork:**

    ```bash
    git clone https://github.com/your-username/Bismuth-207-Purity-Monitor.git
    cd Bismuth-207-Purity-Monitor
    ```

3. **Create a Feature Branch:**

    ```bash
    git checkout -b feature/YourFeatureName
    ```

4. **Make Your Changes:**

    Implement your feature or fix.

5. **Commit Your Changes:**

    ```bash
    git add .
    git commit -m "Add feature: YourFeatureName"
    ```

6. **Push to Your Fork:**

    ```bash
    git push origin feature/YourFeatureName
    ```

7. **Create a Pull Request:**

    Navigate to the original repository and submit a pull request from your feature branch.

---
## Acknowledgements

- **Geant4 Collaboration:** For providing a robust framework for particle simulations.
- **Open-Source Community:** For numerous libraries and tools that made this project possible.
- **CERN and University of Texas at Arlington:** For supporting this research and development.

---
