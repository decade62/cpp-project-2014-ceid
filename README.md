# cpp-project-2014-ceid
Project on Object Oriented Programming II Course teached in Computer Engineering and Informatics Department at University of Patras on 2013-2014.

######################################################################################################################################

Object Oriented Programming II C++

2013-2014 Project

In this project you have to simulate the managing of a fleet of robot vehicles in order to explore a planet and mine resources.
The fleet will be composed of several vehicle types, all of them moving within the map matrix.

PLANET ENVIRONMENT
The purpose of this simulation game is to gather a specific minimum of three resources: Palladium, Iridium and Platinum.
Every cell in the map contains three properties: Palladium Concentration, Iridium Concentration, Platinum Concentration,
Access Risk (value from 0 to 0.9, proportional to the probability of the vehicle to get damaged) and Danger Flag (a bollean
variable that signs that the cell is not to be accessed by vehicles).

VEHICLES
The vehicles consist of three basic types: Exploration, Analysis and Rescue.
A vehicle contains the standard variables of Speed, Status (broken or not) and Access Ability (value from 0.1 to 1 which show
the probability that the vehicle remains intact and without damage after moving). Analysis robots have four extra variables:
Maximum Capacity, Palladium Load, Iridium Load, Platinum Load.

The two main functions of a vehicle are Move and Operate.

The vehicles move randomly on each iteration but may avoid moving onto a cell with Danger Flag. The possibility of caused
damage in a vehicle while moving is: Access Risk * (1 - Access Ability).

The Operate function has different utilization for each vehicle (polymorphism suggested):

Exploration Robot: Probe the current cell and place a Danger Flag if the Access Risk is over a certain value (eg > 0.6)
so that other vehicles will avoid it.

Analysis Robot:    Do the actual resource mining from the ground. Each mining operation has a risk to cause damage to the
vehicle, so mining takes place only to cells with increased concentration to minimize mining operations. You can choose
how the decision to mine or not is made (for example after considering the needs of the base for each resource). When
the vehicle reaches maximum capacity it returns to the base to store it.

Rescue Robot:      Search neighbour cells for damaged vehicles and repair them.

The program creates a random generated two dimensional world with all kinds of vehicles and places them around the map.
It also initializes the cells properties as far as concentration and access risk are concerned. During the simulation
fleet status is displayed. The simulation of the world progresses in accord to the following rules:

SIMULATION RULES
1. In each iteration concise messages that describe what happens (eg. Vehicle A moves, vehicle B mines etc) are printed.
2. For each vehicle the total moves and number of damages from beginning are stored. Additionally, for exploration
vehicles, the number of flags set, and for rescue vehicles, the number of repairs completed, are stored. Alternatively,
for analysis vehicles the total quantity of collected resources is recorded.
3. The base is located in specific place in the map and starts with zero quantity of each resource. The analysis vehicles
collect the materials and when they reach maximum capacity they are automatically transfered to base and unload resources.
4. The program must print requested information and status for a vehicle or map cell.
5. The program must keep general information for vehicles such as total number of damages, total number of danger flags,
total mined load from all vehicles and others, and print them upon user request (static variables and methods suggested).
Similarly other information must be printed for available map cells such as average access risk of map, total quantity of
each resource in map and others.
6. Suppose that all vehicle move at all times within the map.
7. If the world status is that all vehicles are damaged, the simulation terminates with a failure message. If the quantity
of materials in the base reaches the required minimum, the simulation terminates with a success message.
8. If a vehicle gets damaged and fails to be repaired within a specific time limit (eg 15 iterations) it is removed from
simulation.
9. During the simulation the user can import new vehicles, edit a map cell, edit damage status for a vehicle.

USER INTERFACE
The simulation will be utilized with console interface. The user will be able to pause it to view the world status and
information for a vehicle or map cell, or insert other data, or terminate the simulation.
