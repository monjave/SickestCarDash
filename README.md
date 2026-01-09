<img src="./QtApp/CarDashboardContent/images/logo.png" alt="Project Logo" width="720"/>

<h1>SICKEST CAR DASH - Dom, Josh, Mo, Xavier</h1>

SICKEST CAR DASH (SCD) is a vehicle dashboard project aimed at the daily driver, race car driver, and the sim racer. 

For actual vehicles, we'll be taking advantage of the OBDII system that is standard in all cars since 1996. Using a [CAN bus shield for the ESP32](https://store.mrdiy.ca/p/esp32-can-bus-shield/), we have a direct connection to the CAN bus of the vehicle. For the dash itself, we use a 12.3" ultrawide (1920x720) screen by Wisecoco that is connected to a Raspberry Pi. This Pi wirelessly connects to the ESP32's web server for data; with which the dash can be updated and telemetry can be recorded to an SD card.

Note: General Motors used a proprietary protocol called SAE J1850 VPW for many of their vehicles manufactured before 2008. Since our target vehicle (a 2004 Chevy Blazer) falls into this category, we are using J1850 VPW instead of the more modern CAN bus protocol. This choice affects how we communicate with the ECU and which commands/protocol settings we use with the ELM327 adapter.

## Feature List

- Displays for:
  - Speed
  - RPM
  - Fluid Temperatures
  - Warning Lights
  - Fuel Level
  - Throttle Position
  - Current Gear
  - Battery Voltage

# Getting Started
There are two main dependencies you need to have downloaded:
1. Qt Framework
  - this is the framework our application is written with
  - download from [Qt Group](https://www.qt.io/try-qt)
2. Ninja
  - this is the tool used to build our project
  - on Mac, type `brew install ninja` into terminal
  - otherwise, see the documentation [here] to get started

to verify, type the following into your terminal:
```
ninja --version
qmake --version
```

# Installation Steps
1. Clone the repository
```
# Clone the repo
git clone git@github.com:BS-CS410/software-engineering-project-race_car_go_brrr.git

# Navigate to the project directory
cd software-engineering-project-race_car_go_brrr
```

2. Build the project
```
./.scripts/allCleanBuildAndTest
```

3. Run the application
```
# navigate to the application in the `build` file
build/QtApp/CarDashboardApp
```

# Project Structure
```
.
├── .scripts
├── datasheets_and_references
├── diagrams
└── QtApp/
    ├── App/
    │   └── main.cpp
    ├── CarDashboardContent/
    │   ├── App.qml
    │   └── Acreen01.ui.qml
    ├── include
    ├── replay
    ├── src
    └── test
```
## Directories Explained
`.scripts/` : Holds the scripts to run in order to build and test the project.

`QtApp/App/main.cpp` : is the main component that initializes the application

`QtApp/CarDashboardContent/App.qml` : manages the data displayed on the screen

`QtApp/CarDashboardContent/Screen01.ui.qml` : provides the screen and layout to view the data

`QtApp/include` : header files for the back-end logic

`QtApp/replay` : contains `.csv` files with data for the replay function

`QtApp/src` : implementation files for the back-end logic

`QtApp/test` : provides the QTest files for testing the program
