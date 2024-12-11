                                                              ![ISEL](https://github.com/osduarte/TESE-MEIC-2324/blob/main/logo_ISEL_principal_PNG.png)

# TESE-MEIC-2324

Welcome to the TESE-MEIC-2324 repository! This repository contains all the resources, documentation, and code related to a thesis project for the Master's in Computer Science and Engineering (MEIC) program for the 2023-2024 academic year. Below, you'll find an overview of the repository structure, its contents, and how to navigate it effectively.


Performing fitness exercises is not executed correctly can lead to injury. The scope of this project is to incorporate an embedded system on a pair of weights (deadlifts) to monitor the correctness of the exercise execution. The embedded system to be used is already available is able to acquire motion (accelerometers) and communicate the sensor readings via bluetooth to a host. The host can be either a mobile phone or a computer and is responsible for two taks: 1) control a point on screen with the weight’s movement; 2) validate the movement via a Neural Network The work to be performed consists of: - Extracting data from the sensor via bluetooth; - Dataset generation; - Selection and training of the most suitable neural network; - Program an application to present different exercises (challenges) to the user; - Keep tracking of the user’s performance (score); At the end of this project it is expected to have a demonstration of the system, a written report (thesis) and a scientific paper detailing on the developed work and its results

---
## Repository Structure

### 1. `/Examples`
Includes example implementations or applications demonstrating the use of the middleware or other components. Examples for accelerometer and the XIAO Sense.

### 3. `/Experiences`
Holds experimental data, results, or analyses conducted during the project. Experiences made with multiple components to test the final architecture.

### 4. `/Project`
This folder contains the main project source files and subfolders structured as follows:

#### 1. IMU Capture folders
Contains the Arduino code to capture the acceleromenter and gyroscope data.

#### 2.MODEL_Configurations and Results
Contains results obtained on Edge Impulse and Python code.

#### MODEL_Training
Contains the code to train the model locally in a pc that should be run using Visual Code, using wsl (see specific readme in the foldeR)

#### 4.IMU_Classifier
After obtaining a model from the previous step include it in this code (Use Arduino IDE) to upload it to the MCU.

#### 5.Mobile App
Mobile app code, to run check: [[https://success.outsystems.com/logout/logout](https://www.outsystems.com/Platform/Signup)](https://www.outsystems.com/Platform/Signup)

#### Raw data folders
Includes the data collected

#### References folder
Include some pdf with references used in this work (publicly available)

#### Box folder
Box model to be used, if you want to 3D print the box for the components of this project

---

## Getting Started

### Prerequisites
- **Python**: Ensure Python installed.

## Contributing
Contributions to this repository are welcome.

### Guidelines
1. Follow the repository structure.
2. Follow the specific readme in each folder

---

## Acknowledgments
Special thanks to ISEL that supported the development of this project.

---

For more details, refer to specific folders or contact the repository owner.



