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

## Description of Project <a name="description-of-project"></a>
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

## Whitebox Test <a name="whitebox_test"></a>
**Class:** MapControllerAPI
**Technique:** Statement Coverage
**Test File:** test_mapcontroller.py
**Location:** webportal/whitebox_testing

### <ins>Test Cases</ins>
The statement coverage statistics for each function were manually driven by first counting the total number of statements in the function and then counting the number of statements tested in the test case.

#### Test Case: test_post_delete
* Tests the post and delete functions of the MapControllerAPI class.

##### post function
Total number of statements = 4

![total_statements_post](https://drive.google.com/uc?export=view&id=19hn509fmrP6bO6VNpwPRn9rnhl7Ygkfz)

Number of statements tested = 4

![tested_statements_post](https://drive.google.com/uc?export=view&id=1_8VkQ1-VjSQOhKAoR2bEItyepfd8ADAt)

Coverage statistics = 4/4 = 1

#### delete function
Total number of statements = 5

![total_statements_delete](https://drive.google.com/uc?export=view&id=1rK_7eopl9eaU0LIcKt1vk92riK1EB8nw)

Number of statements tested = 5

![tested_statements_delete](https://drive.google.com/uc?export=view&id=1Qkc0ll5onjL_OEQOrLfIP5Kf_qSX7miO)

Coverage statistics = 5/5 = 1

### <ins>Running the Test Suite</ins>
1) Download the zipped file.
2) Navigate to the directory of the project. (2x01)
4) Run python -m unittest whitebox_testing/test_mapcontroller.py

![run_test](https://media.giphy.com/media/ssjSWnQiRcXHSRrj90/giphy.gif)


## Blackbox Test <a name="blackbox_test"></a>

### <ins>Test Cases</ins>

#### Test Case: User Access Web Portal via localhost at the respective URL.
Precondition: 
Domain URL must be valid and available.

Steps: 
1. User enters the URL on the navigation bar of their web browser.

Result: 
User successfully accesses the web portal. Test case passed.

![tc1](https://user-images.githubusercontent.com/73056944/144760449-4f0967ea-d424-4ba4-aeef-db4a95e26e9d.png)

#### Test Case: User navigates to tutorial page by selecting tutorial button.
Precondition: 
The tutorial page has to be accessible by the user.

Steps:
1. User clicks on the tutorial button.

Result: 
User successfully accesses the tutorial page. Test case passed.

![tc2](https://user-images.githubusercontent.com/73056944/144760486-c8dabfdc-36a1-40c3-bff9-60a9b5db6298.png)

#### Test Case: User reads tutorials on the tutorial page.
Precondition: 
User has successfully accessed the tutorial page.

Steps:
1. User will go through the tutorials.

Result: 
User is able to view the tutorials. Test case passed.

![tc3](https://user-images.githubusercontent.com/73056944/144760571-913002c7-44ad-498d-b298-d9a5cd6cca18.png)


#### Test Case: User navigates to customise map page by selecting customise button.
Precondition: 
The map page URL has to be accessible by the user.

Steps:
1. User clicks on the customise button on the navigation bar.

Result: 
The feature of being able to customise the previously created maps was not implemented in the maps page. Test case failed.

![tc4](https://user-images.githubusercontent.com/73056944/144760627-179124d3-cbb7-404e-91e9-8df240c8dd2a.png)

#### Test Case: User can display previously created maps.
Precondition: 
User must be able to access web portal and the map creation page.

Steps:
1. User clicks on the maps button on the navigation bar.

Result: 
The feature of displaying the previously created maps was not implemented in the maps page. Test case failed.

![tc5](https://user-images.githubusercontent.com/73056944/144760672-fae3690f-f763-44c9-93ee-ad8bf106c083.png)

#### Test Case: User can view map assets - grids, routes, boundary - when an empty map is loaded.
Precondition: 
User must be able to create maps and is on the Maps page.

Steps:
1. User clicks on the maps button on the navigation bar.

2. User is displayed with an empty map. 

Result: 
A boundary and unshaded square grids are displayed on the screen to represent an empty map. Test case passed.

![tc6](https://user-images.githubusercontent.com/73056944/144760712-8b532bb0-df6a-4d09-845c-04d4b786290a.png)

#### Test Case: User can view an empty map on the map creation page.
Precondition: 
User must be able to access web portal and the map creation page.

Steps:
1. User clicks on the maps button on the navigation bar.

Result: 
An empty map is displayed on the screen, available for the user to modify it. Test case passed.

![tc7](https://user-images.githubusercontent.com/73056944/144760729-8201a036-51f0-4e0c-af1b-b55cc6c4b4ac.png)

#### Test Case: User can delete a previously saved map.
Precondition:
User must be able to select maps and is on the Maps page.

Steps:
1. User selects a saved map.

2. User clicks on "Delete Map".

Result: 
The feature of deleting maps was not implemented on the maps page. Test case failed.

![tc8](https://user-images.githubusercontent.com/73056944/144760763-1649f579-d9d2-4403-b230-528671e96c98.png)

#### Test Case: User can edit items on the empty map by utilising the map assets.
Precondition: 
User must be able to view and utilise the Maps assets on the maps page.

Steps:
1. User clicks on the maps button on the navigation bar.

2. User drag and drops the map assets onto the grid of the map.

Result: 
Grids that were clicked will be shaded, representing a new route on the map. Test case passed.

![tc9](https://user-images.githubusercontent.com/73056944/144760811-2b0870b1-f4bf-4e78-877f-04a1cdac5fd4.png)

#### Test Case: User can save an edited map that was initially empty.
Precondition: 
User have already customised an empty map to include new routes.

Steps:
1. User clicks on the maps button on the navigation bar.

2. User click on the grids.

3. Click on the "Save" button.

Result: 
Based on the game's internal logic, the user is not allowed to save an empty map. Test case failed.

![tc10](https://user-images.githubusercontent.com/73056944/144760838-85f887e9-e5fc-4d24-926e-2307f44059c1.png)

#### Test Case: User can create and save a new game map.
Precondition: 
User must be able to access web portal and the map creation page.

Steps:
1. User clicks on the maps button on the navigation bar.

2. User selects an empty map.

3. User customize the map by clicking on the map grids.

4. User clicks on the "Save" button.

Result: 
Student will be able to modify the map and the map will be saved to the database. Test case passed.

![tc11](https://user-images.githubusercontent.com/73056944/144760894-2bfc228f-9ecc-4547-9c6d-560473085faa.png)

#### Test Case: User is able to delete saved maps.
Precondition: 
1) User must be able to access web portal and the map creation page.
                                                                                                 
2) User must have previously created customised maps.

Steps:
1. User clicks on the maps button on the navigation bar.
                                
2. User selects a saved map.
                                
3. User clicks on "Delete Map".

Result: 
The feature of being able to delete maps was not implemented in the maps page. Test case failed.

![tc12](https://user-images.githubusercontent.com/73056944/144760934-48c29076-9707-41a4-baae-18277b526c6d.png)

#### Test Case: User navigates to dashboard by selecting dashboard button.
Precondition: 
The dashboard page url has to be accessible by the user.        

Steps:
1. User clicks on the Dashboard button on the navigation bar.
                                                                                             
2. The user gets redirected to the dashboard page.

Result: 
Dashboard page will be displayed. Test case passed.

![tc13](https://user-images.githubusercontent.com/73056944/144760985-ef8ce20e-92c1-48b2-92f5-7c55fe0eac77.png)

#### Test Case: User will see car status updated through the dashboard.
Precondition: 
1. User must be able to access web portal and the dashboard page. 
                                                                                                               
2. The car is sending readings back to the web portal.

Steps:
1. User will monitor the dashboard.
                
2. Changes will be reflected on the dashboard.

Result: 
The readings are constantly updated. Test case passed.

![tc14](https://user-images.githubusercontent.com/73056944/144761028-a78b8622-bf1b-4635-a7f1-af34825071fc.png)

#### Test Case: User views Car Connection Info on the Dashboard.
Precondition: 
1. User must be able to access web portal and the dashboard page.
                                  
2. Web Portal must have received the connection information.

Steps:
1. User will look at the car status on the dashboard.

Result: 
There is a lack of a proper mechanism to determine if the car is connected to the web portal. Test case failed.

![tc15](https://user-images.githubusercontent.com/73056944/144761072-78c2d50a-2dd0-4efa-9d52-45630c392e79.png)

#### Test Case: User views Car Speed Info on the Dashboard.
Precondition: 
1. User must be able to access web portal and the dashboard page.
                           
2. Web Portal must have received and extracted the car speed information.

Steps:
1. User will look at the car speed information on the dashboard.

Result: 
Car Speed Information can be seen on the dashboard. Test case passed.

![tc16](https://user-images.githubusercontent.com/73056944/144761114-77cec2f1-7d70-4f82-a75c-29752e812f2d.png)

#### Test Case: User views Car Current Temperature on the Dashboard
Precondition: 
1. User must be able to access web portal and the dashboard page.
                            
2. Web Portal must have received and extracted the car current temperature.

Steps:
1. User will look at the current car temperature on the dashboard.

Result: 
The current car temperature can be seen on the Dashboard. Test case passed.

![tc17](https://user-images.githubusercontent.com/73056944/144761153-e222b930-d7bb-4b42-8fca-c8af2732e003.png)

#### Test Case: User views Car Temperature Graph on the Dashboard.
Precondition: 
1. User must be able to access web portal and the dashboard page.
                                
2. Web Portal must have received and extracted the car temperature information and is plotted on the graph.

Steps:
1. User will look at the changes of the car temperature on the graph on the dashboard.

Result: 
The Car Temperature Graph can be seen on the Dashboard. Test case passed.

![tc18](https://user-images.githubusercontent.com/73056944/144761193-c7a0ec76-6c3e-429f-8554-7359ef7ce5d6.png)

#### Test Case: User views rate of line detection graph on the Dashboard.
Precondition: 
1. User must be able to access web portal and the dashboard page.
                               
2. Web Portal must have received and extracted the line detection information and is plotted on the graph.

Steps:
1. User will look at the rate of line detection on the graph on the dashboard.

Result: 
The rate of line detection graph can be seen on the Dashboard. Test case passed.

![tc19](https://user-images.githubusercontent.com/73056944/144761237-0769c64a-fade-449d-9390-31ca656aa3d2.png)

#### Test Case: User views line detection count graph on the Dashboard.
Precondition: 
1. User must be able to access web portal and the dashboard page.
                                
2. Web Portal must have received and extracted the line detection count information and the information is plotted in the graph.

Steps:
1. User will look at the detection count on the graph on the dashboard.

Result: 
The line detection count graph can be seen on the dashboard. Test case passed.

![tc20](https://user-images.githubusercontent.com/73056944/144761277-48792e61-ff39-4895-885a-8a8d3df66129.png)

#### Test Case: User navigates to terminal page by selecting terminal button.
Precondition: 
The terminal page URL has to be accessible by the user.

Steps:
1. User clicks on the terminal button on the navigation bar.

Result: 
The terminal page will be displayed. Test case passed.

![tc21](https://user-images.githubusercontent.com/73056944/144761342-2d63fa04-514b-447b-9acb-1afdab516c2d.png)

#### Test Case: User views the created map.
Precondition: 
1. The terminal page has to be accessible by the user.
                                       
2. User must have already created a map.
 
Steps:
1. User clicks on the Terminal button on the naviaton bar.
                                
2. The map that the user has created loads onto the temrinal page. 

Result: 
The map created by the user gets displayed onto the terminal. Test case passed.

![tc22](https://user-images.githubusercontent.com/73056944/144761382-615fce1f-a793-4ac3-9032-1f7ec88681d0.png)

#### Test Case: User inputs commands into the terminal and executes them. 
Precondition: 
1. The terminal page has to be accessible by the user.
                                          
2. User must have already created a map.
 
Steps:
1. User clicks on the terminal button on the navigation bar.
                                     
2. The user drags and drops the blocky commands that they want to input.
                                                                        
3. User clicks on the "Send" button on the terminal page.

Result: 
The commands inputted by the user will be sent to the robotic car to be executed. Test case passed.

![tc23](https://user-images.githubusercontent.com/73056944/144761445-62edbff9-3400-4aaf-8867-9c290e379037.png)

#### Test Case: User removes a command from the terminal. 
Precondition: 
1. The terminal page has to be accessible by the user.
                                                                    
2. User must already have input a command previously.

Steps:
1. User clicks on the terminal button on the navigation bar.
                                
2. User drags and drops the blocky commands that they want to input.
                                                                        
3. User drags the blocky command that they want to remove into a bin.

Result: 
The command that the user dragged to the bin will be removed. Test case passed.

![tc24](https://user-images.githubusercontent.com/73056944/144761484-aec6dd0c-d18c-4d49-b834-760a05be836a.png)


#### Test Case: User resets all of the command entered into the terminal. 
Precondition: 
1. The terminal page has to be accessible by the user.                                                                    

2. User must already have input a command previously.

Steps:
1. User clicks on the terminal button on the navigation bar.
                                
2. User drags and drops the blocky commands that they want to input.
                                                                        
3. User clicks on the "Reset" button on the terminal page.
                                                                                                 
Result: 
All of the commands inputted by the user will be removed. Test case passed.

![tc25](https://user-images.githubusercontent.com/73056944/144761534-a3a608b1-0cdc-428f-8471-6b8acec5549b.png)

#### Test Case: User plays the game.  
Precondition: 
1. The maps page has to be accessible by the user.
                                                           
2. The terminal page has to be accessible by the user.
                                     
3. User must already have input a command previously.
                                   
4. The robotic car must be able to communicate to the web portal.
 
Steps:
1. User clicks on the map button on the navigation bar.
                                    
2. User creates a map by dragging and dropping the map elements onto the map grid.
                                                       
3. User gets redirected to the terminal page.
                                                    
4. User drags and drops the blocky commands that they want to input.
                                   
5. User clicks on the "send" button on the terminal page.                           
                                                                                                 
Result: 
The robotic car will execute the commands that the user wants it to execute.  Test case passed.

![tc26](https://user-images.githubusercontent.com/73056944/144761598-e43f1b86-ca35-4702-84fc-15aa5e24a2aa.png)

#### Black Box Testing video

[![web video player](https://user-images.githubusercontent.com/73056944/144762031-4c117203-4a3c-4b03-8b0e-5e3bbea721f3.png)](https://youtu.be/lzgUs9H4lgM)

   














