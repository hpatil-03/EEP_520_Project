# Complex Maze Solving Autonomous Robot
## Overview
To put a robot at the start location and have it explore until it finds the end of the maze using range sensors, wall following behaviors

## Key Challenges and Solutions

### To make precise 90 degree turns of the agent
* While rotating the agent, due to time delays, the final angle after turning the agent was not precisely equal to multiples of 1.5708 radians (90 degrees). 
To resolve this issue the total_angle global variable is checked to get the precise angle. Using teleport() function the agent is correctly orriented eliminating the offsets. the x and y coordinates of final position is retrieve using position() method.

### Front Sensor Threshold Value issue
* Front sensor  threshold value with which the agent detects hurdles or wall should be set so that there enough space for the agent to rotate or else it might get stuck depending on shape of the agent.

### Top and Bottom sensors algorithm limitations 
* The rotation algorithm depends on the top and bottom algorithm. The rotation angle is decided on the greater sensor values depicting max free space. Not necessary that the max free space might be the correct track. So the algorithm is changed so that the agent should not go back travel through the same track again. 

## Installation and Execution
---
	git clone https://github.com/hpatil-03/EEP_520_Project.git
	cd EEP_520_Project
	docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash
	make
	esm start
	enviro
[open localhost on any web browser](http://localhost/)
---

## How to use/modify the project
* The config.json can be editted or changed to some different file config having different agent attributes and maze orientation.
* The defs/my_robot.json file can be editted to change the shape, description of the agent. Number of sensors can be also be editted here. 
* If the changes are made to the json file then directly enter command 'enviro' to run the program.
* If the changes are made to the .h file then command 'make' and then 'enviro' needs to be entered.

## Acknowlegment
* Klavin-> Enviro Library 
* WebSocket library