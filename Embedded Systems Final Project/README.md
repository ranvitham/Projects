Final Project for CPRE 2880 (Spring 2025) - Embedded Systems at Iowa State University - A project truly built all the way from the ground up.

Group Members: Ranvitha Muramreddy (me), Megan Chng, Wesley McGovern, Dylan Bunting, Carson Cornwell.

Problem Statement: Create an Accessible Drink Delivery System that can navigate through unpredictable environments 
and deliver drinks to a person, announcing using a sound signal when it has arrived.

POV statement: An adult needs an accessible and convenient way to get drinks from their office breakroom in their environment due to 
a disability of some sort, like mobility or visual impairment. They would like to keep their independence in their 
environment even when navigating around is a difficult thing to do.   

High-level mission goals: When the robot is given an order, it needs to navigate through the environment and any obstacles to deliver to the person
who ordered it, making a sound signal that announces its arrival. It needs to avoid running over small objects like 
misplaced toys or office supplies on the floor, table legs and walls. It also needs to avoid any drops, puddles, stairwells 
and make it to the person in their room or cubicle and announce its presence with a sound. (The symbolic meanings of our given 
test field in the context of our problem.)

Key Functionalities:
- Basic Platform Components and Modes: Open Interface and iRobot sensors, Interrupts, Analog to digital conversion, Input capture, Pulse width modulation, and UART/WiFi.
- Pathfinding & Navigation: Maneuvering through the test field without hitting any objects or falling into “holes” using sensors and servo-mounted 
scanning systems.
- GUI Map: A visual representation of what the sensors are detecting so the user/driver can see what is there without being physically present.

Key Technical Features:
- IR and Ping sensors for detection.
- 180-degree servo for scanning.
- Integrated audio system for output of sound signal.
- IMU(Internal Measurement Unit) for accurate movement and positioning.
- Optimized software for the cleanest and most precise desired movement (based around CyBot 10).


