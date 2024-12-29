# Code of the experiments for UAV AR.Drone 2.0 flight trajectory tracking, using state observers and on board data.

Resources and extra documentation for the manuscript titled **"UAV Flight Comparison Using Backstepping On-board Data and Observers"** with **ID 9357** published in IEEE Latin America Transactions.

**Abstract:** This work presents the comparison of performance in flight trajectory tracking for a commercial UAV AR.Drone 2.0, using state observers and on board data. This work seeks to establish that state observers are an alternative to close the control loop in this type of applications. The control strategy proposed for the flight is designed using the Backstepping technique. For the implementation of the control law, knowledge of the position and orientation of the UAV is assumed, therefore, its longitudinal and rotational velocities are estimated either by using observers or data from the combination of inertial and visual measurement of the on-board sensors. In both cases, the designed control strategy makes the UAV converge to the preestablished flight trajectory. However, an analysis of the mean square error between the UAV trajectory with respect to the desired trajectory, gives as a result that, in three of the four compared states, the error obtained with the observer is lower. The theoretical results presented are validated experimentally.

**Authors:**

**Jesus Santiaguillo-Salinas** was born in Mexico on March 1986. He received his M.Sc. and Ph.D. degrees in Electrical Engineering from Center for Research and Advanced Studies of the National Polytechnic Institute (CINVESTAV), Mexico, in 2012 and 2017, respectively. His research interests include mobile robotics and motion coordination problems with non-collision for multi-agent system. Currently, Dr. Santiaguillo-Salinas holds a Full Professor-Researcher Position at the Mechatronics Department of the Papaloapan University, Mexico.

**Eduardo Aranda-Bricaire** was born in Mexico City. He obtained the M.Sc Degree from Center for Research and Advanced Studies of the National Polytechnic Institute (CINVESTAV), Mexico, in 1991, and the Ph.D. Degree from Ecole Centrale de Nantes and Université de Nantes, France in 1994. Dr. Aranda-Bricaire´s research interests include Nonlinear Control Theory, Mobile Robotics, Multi- Agent Robot Systems and Discrete-Event Systems. Dr. Aranda-Bricaire has served as President of the Mexican Association of Automatic Control, the corresponding National Member Organization of the International Federation of Automatic Control (IFAC). Currently, Dr. Aranda-Bricaire holds a Full Professor Position at the Mechatronics Section of the CINVESTAV, Mexico.

**Hiram N. Garcia-Lozano** was born in Mexico State. He received his M.Sc. and Ph.D. degrees in Automatic Control from Center for Research and Advanced Studies of the National Polytechnic Institute (CINVESTAV), Mexico, in 2002 and 2007, respectively. Dr. Garcia-Lozano’s research interests include robotics, mobile robotics and control systems. Currently, Dr. Garcia-Lozano holds a Full Professor-Researcher Position at the Mechatronics Department of the Papaloapan University, Mexico.

## Requirements

To replicate the results of the paper, an experimental platform with the following components is required:
- **A vision system.** This system is responsible for tracking rigid bodies (position and orientation) and is made up of a set of OptiTrack Flex 13 cameras connected to a computer with Windows (7 or higher) where the Motive software runs.
- **A control system.** Consisting of a computer with Ubuntu 12.04 and ROS Fuerte Turtle. In addition, it must have the ROS drivers installed for the use of OptiTrack and the AR.Drone.
- **An AR.Drone 2.0.** This is a commercial quadcopter manufactured by the French company Parrot.
- **A communication system.** Consisting of a wireless router that generates a LAN network, to which all the previous components are connected. The computers of the vision and control systems are connected via Ethernet connection to the router and the AR.Drone via Wi-Fi. If the speed of the wireless router allows it, all components can be connected via Wi-Fi.

## Description

The folders contained in this repository are described below.
- **ardrone_autonomy.** ROS package that contains the driver to be able to use the AR.Drone. The installation process and its use are detailed in the README.md file inside the folder.
- **sandbox\ardrone_programs.** ROS package that contains the files necessary to reproduce the experiments of the paper. This package must be placed inside the ROS workspace and its content is as follows
  - **bin.** Contains files generated from the compilation of the source codes in src.
  - **build.** Contains the executable files generated from the source codes in src.
  - **launch\enviroment.launch**. File that launches the AR.Drone driver.
  - **src.** Contains the source codes for the programs to control the AR.Drone.
    - **dbackD1.cpp.** File containing the code to perform the trajectory tracking experiments using backstepping with observers and on board data, for the AR.Drone.
    - **landD1.cpp.** File containing the code to land the AR.Drone.
    - **net.cpp.** File containing the code to convert the transmitted data from Motive position and orientation with quaternions to position and orientation with Euler angles.
    - **takeoffD1.cpp.** File containing the code to take off the AR.Drone.

## Instructions for performing the experiments

**Preliminary instructions.**

1. **Track the AR.Drone from Motive.** Place infrared markers on the AR.Drone and register a new rigid body in Motive (Windows computer) generated from said markers. Verify the assigned name and id and allow the transmission of tracking data over the network.
2. **Configure the Optitrack driver in ROS.** Modify the driver configuration file (computer with Ubuntu) with the Motive transmission data and the name and id of the AR.Drone. [Driver installation and configuration guide](https://wiki.ros.org/mocap_optitrack).
3. **Configure the AR.Drone to connect to the LAN network.** Edit the configuration parameters to connect to an infrastructure type network (via Wi-Fi) and assign a valid IP address according to the LAN network configuration.

**Instructions for running the files.**

1. Launch the ROS core from the Ubuntu computer:
  `$ roscore`
2. Launch the OptiTrack driver:
  `$ roslaunch mocap_optitrack\launch mocap.launch`
3. Launch the AR.Drone driver:
  `$ roslaunch sandbox\ardrone_programs\launch enviroment.launch`
4. Run the program to convert streaming data:
  `$ rosrun sandbox\ardrone_programs net`
5. Run the program to perform trajectory tracking using backstepping:
  `$ rosrun sandbox\ardrone_programs dbackD1`
  > Each instruction in the steps above is run from the console (one for each instruction).

For more information about ROS (creating and using packages, using roslaunch, rosrun, among other basic information) you can consult the [ROS Wiki](https://wiki.ros.org/ROS/Tutorials#Beginner_Level)
