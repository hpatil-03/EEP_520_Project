# Complex Maze Solving Autonomous Robot
To put a robot at the start and have it explore until it finds the end of the maze using range sensors, wall following behaviors

## Key Challenges and Solutions

##### To make precise 90 degree turns of the agent
* While rotating the agent, due to time delays, the final angle after turning the agent was not precisely equal to multiples of 1.5708 radians (90 degrees). 
To resolve this issue the total_angle global variable is checked to get the precise angle. Using teleport() function the agent is correctly orriented eliminating the offsets. the x and y coordinates of final position is retrieve using position() method.

##### Front Sensor Threshold Value issue
* Front sensor  threshold value with which the agent detects hurdles or wall should be set so that there enough space for the agent to rotate or else it might get stuck depending on shape of the agent.

##### Top and Bottom sensors algorithm limitations 
* The rotation algorithm depends on the top and bottom algorithm. The rotation angle is decided on the greater sensor values depicting max free space. Not necessary that the max free space might be the correct track. So the algorithm is changed so that the agent should not go back travel through the same track again. 
