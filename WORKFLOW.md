# Workflow 
## The Github repo consists of four main catgories of branches 
### Master branch 
The master branch contains the finalised code that is used for Releases.

### Dev branch 
The dev branch contains the most up to date code of the development code. 

### Feature branches 
The feature branch contains the development code for each specific feature.

### Whitebox Test branch
The whitebox test branch contains the code that is used to test the development code. 

## General Workflow Guidlines 
- Always commit to the dev branch before the master branch.
- Use the apporpirate branch for the code that you are working on - E.g. Terminal code should fall under the "feauture/terminal" branch.
- Pull requests to the dev branch do not require approval unless code conflicts occur.
- No direct commits to the dev branch is allowed unless under special circumstances - E.g. Updating the README.md file. 
- Personal config files, auto-gen files, compiled binaries and large asset files shall not be pushed and tracked. 

--------------------------LOGS---------------------------

#1 Create Repository name 2x01-Project to replace the previous 2201-P3-5-Team-Project to better view the use of Github commands
#2 Create Master to replace Main / Dev / Features Branches
#3 Insert barebone code from feature initial setup to Dev
#4 Push dashboard page from feature/dashboard with template layout
#5 Push backbone of database into feature/dashboard
#6 Pull Request from Dev for dashboard/feature
#7 Push terminal page from feature/terminal with template
#8 Add blocky integration from feature/blocky 
#9 Pull Request from Dev from terminal page & blockly integration
#10 Merge and pull terminal page, blocky integration, and dashboard
#11 Added Controllers into feature/terminal
#12 Push homepage from feature/homepage with template layout
#13 Added wifi connections to feature/wifi
#14 Create layout of the map on feature/customisemap
#15 Duplicate layout of the map on feature/terminal
#16 Add logic of map creation in feature/customisemap
#17 Pull Request for map layout, logic from feature/customisemap, feature/wifi to Dev
#18 Pull Request for wifi connection from feature/car
#19 Update the car commands for feature/car
#20 Merge Pull Request from feature/customisemap and feature/car
#21 Add logic and enhance the map creation UI in feature/customisemap
#22 Integrate the database to map creation UI in feature/customisemap
#23 Update the data for dashboard into database in feature/dashboard
#24 Push changes from feature/customisemap, feature/car, feature/dashboard
#25 Pull request the changes from feature/customisemap, feature/car, feature/dashboard into Dev
#26 Add tutorial page from feature/tutorial
#27 Fix bugs from dashboard using feature/bugfixes-and-cleanup
#28 Update blockly commands in feature/blocky
#29 Add game logic to terminal page in feature/terminal
#30 Push the tutorial page, game logic into Dev
#31 Update extra game logic to the terminal page in feature/terminal
#32 Push the bug fixes to Dev from feature/bugfixes-and-cleanup
#33 Push the blockly commands, game logic to Dev from feature/blockly, feature/logic
#34 Pull request for bugfixes, blockly command and game logic to Dev
#35 Merge the changes to Dev
#36 Push Dev to Master
#37 Pull request from Dev to master
#38 Deploy the 1st version of the application from master as a release
#39 Fix bugs and errors on the terminal on feature bugfixes-and-cleanup
#40 Push bug fixes to Dev
#41 Update the layout and information on feature/homepage to Dev
#42 Update the tutorial information on feature/tutorial to Dev
#43 Added tutorial maps to feature/customisemap to Dev
#43 Updated car logic to feature/car to Dev
#44 Push updates from feature/homepage, feature/tutorial, feature/customisemap, feature/car
#45 Pull Request for feature/bugfixes-and-cleanup, feature/homepage, feature/tutorial, feature/customisemap, feature/car to Dev
#46 Merge updates and changes for Dev
#47 Push Dev to Master
#48 Merge changes from Dev to Master
#49 Add terminal linking between game and car in feature/car
#50 Added Readme, whitebox testing on feature/customisemap
#51 Clean up of code for all branches and push to Dev
#52 Update and review all branches
#53 Push branches that have pending changes to Dev
#54 Pull Request from Dev
#55 Merge the changes
#56 Code freeze
#57 Code submission