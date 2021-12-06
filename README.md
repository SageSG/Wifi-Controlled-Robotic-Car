# ICT2x01 Project: Wi-Fi Enabled Robotic Toy Car
Team Bumbling Cat Pandas
- Jas Pang, 2000823
- Jonathan Tan, 2001428
- Nur Shahidah Binte Imran, 2001470
- Ryan Goh Shao Chong, 1802980
- Yip Hou Liang, 2000721

# Table of Contents
1. [Description of Project](#description-of-Project)
2. [Gameplay](#gameplay)
3. [Robotic Car](#robotic_car)
4. [Technologies Used](#technologies-used)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Whitebox Test](#whitebox-test)
8. [Blackbox Test](#blackbox-test)

## Description of Project <a name="description-of-Project"></a>
The Bumbling Cat Pandas team had developed a gamified web-based learning system that integrates both the virtual and physical environment that aims to instill critical problem-solving and computational thinking skills.

The system engages the students by having a game that requires them to create a route using block-based programming that would pilot a robotic car through a maze. The game further challenges the students logic skills by generating bombs that would require the students to re-evaluate their routes to move the car around the bombs. 

## Gameplay <a name="gameplay"></a>
This gameplay requires the student to follow the virtual maze layout and build a physical maze with the tiles provided. Once the arena is set, the student can use the web-based terminal and input the sequence of command for the car to transverse the maze.

## Robotic Car <a name="robotic_car"></a>
The robotic car consists of MSP432 with ultrasonic sensor, infra-red sensor and is powered by battery.
- It uses a Wi-Fi to communicate to the web interface to get its set of instructions.
- There is memory storage in the MSP432 board, microcontroller, and processor of the car.
- The infra-red sensor is used to detect the lines drawn on surfaces.
- Ultrasonic sensor will detect nearby obstacles to ensure that the car will not collide with other objects.
- The battery will power all the components on the car.

https://user-images.githubusercontent.com/32363441/144721149-a5590148-93c6-41c7-a3ef-8eda82d52cca.mp4

## Technologies Used <a name="technologies-used"></a>
* Python
* Python Flask Framework
* C
* JavaScript
* Bootstrap

## Installation <a name="installation"></a>
pip install -r requirements.txt

## Usage <a name="usage"></a>
1) Download source code from latest release and extract contents.
2) Execute the program: python main.py
3) Open the browser and navigate to the link provided in the command line. (https://localhost:7000)

![screenshot](https://drive.google.com/uc?export=view&id=1JWoiP1Clp29KRJQxnHNQIVjMYjqNzBQ-)

## Whitebox Test <a name="whitebox-test"></a>
**Class:** MapControllerAPI

**Technique:** Statement Coverage

**Test File:** test_mapcontroller.py

**Location:** whitebox_testing

### <ins>Test Cases</ins>
The statement coverage statistics for each function were manually driven by first counting the total number of statements in the function and then counting the number of statements tested in the test case.

#### test_post
* Tests the post method in the MapControllerAPI class.

* Total number of statements = 4

![total_statements_post](https://drive.google.com/uc?export=view&id=19hn509fmrP6bO6VNpwPRn9rnhl7Ygkfz)

* Number of statements tested = 4

![tested_statements_post](https://drive.google.com/uc?export=view&id=1S958vnvJA7gHEXcM_Y7zen95j1JOviGI)

* Coverage statistics = 4/4 = 1

#### test_delete
* Tests the delete method in the MapControllerAPI class.

* Total number of statements = 5

![total_statements_delete](https://drive.google.com/uc?export=view&id=1rK_7eopl9eaU0LIcKt1vk92riK1EB8nw)

* Number of statements tested = 5

![tested_statements_delete](https://drive.google.com/uc?export=view&id=1tRrhzzwZ9s7XkY5qnQDt9EYKWCfl7OoA)

* Coverage statistics = 5/5 = 1

### <ins>Running the Test Suite</ins>
1) Download the zipped file.
2) Navigate to the directory of the project. (2x01)
4) Run python -m unittest whitebox_testing/test_mapcontroller.py

https://user-images.githubusercontent.com/32363441/144780066-fece0879-ef2a-423a-a31a-e52f0f33609d.mp4

## Blackbox Test <a name="blackbox-test"></a>
The various system test cases as shown in the video for the web portal's features are derived from its state diagram.
![image](https://user-images.githubusercontent.com/32363441/144779751-49ea15ee-4b38-4a48-93d2-b9f3ae3bb438.png)

https://user-images.githubusercontent.com/32363441/144779944-6ca38f9a-0c53-4003-9ea9-e254f6e9354e.mp4