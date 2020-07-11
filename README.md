<img src="udacity_banner.jpg" height ="20">

### Robotics Software Engineer - Nanodegree

# Project 05 (of 05) : Home Service Robot
## Directory Structure
```
.Home_Service_Robot  
    ├──                                # Official ROS packages
    |
    ├── slam_gmapping                  # gmapping_demo.launch file                   
    │   ├── gmapping
    │   ├── ...
    ├── turtlebot                      # keyboard_teleop.launch file
    │   ├── turtlebot_teleop
    │   ├── ...
    ├── turtlebot_interactions         # view_navigation.launch file      
    │   ├── turtlebot_rviz_launchers
    │   ├── ...
    ├── turtlebot_simulator            # turtlebot_world.launch file 
    │   ├── turtlebot_gazebo
    │   ├── ...
    ├──                                # Custom packages and directories
    |
    ├── add_markers                    # add_marker C++ node
    │   ├── CMakeLists.txt
    │   ├── include
    │   │   └── add_markers
    │   ├── launch
    │   │   └── add_markers.launch
    │   ├── package.xml
    │   └── src
    │       └── add_markers.cpp
    ├── maps                           # map files
    │   ├── my_world.pgm
    │   └── my_world.yaml
             (Avadhoot.world)?
    ├── pick_objects                   # pick_objects C++ node
    │   ├── CMakeLists.txt
    │   ├── include
    │   │   └── pick_objects
    │   ├── launch
    │   │   └── pick_objects.launch
    │   ├── package.xml
    │   └── src
    │       └── pick_objects.cpp
    ├── rviz_conf                      # rviz configuration files
    │   └── new_rviz_config.rviz
    ├── scripts                        # shell scripts files
    │   ├── add_markers.sh
    │   ├── home_service.sh
    │   ├── pick_objects.sh
    │   ├── test_navigation.sh
    │   └── test_slam.sh
    ├── LICENSE
    ├── README.md
```  

## Project Goals
Creating a custom Gazebo world.

Deploying ```turtlebot``` in the world.

Using ```gmapping``` - ROS Package to map the world.

Writing a ```pick_objects``` node to send pickup and dropoff location to the ROS navigation stack.

Using ROS AMCL package, the robot is continously localised with respect to the environment. 
The ROS navigation stack creates a path for the robot based on Dijkstra's algorithm, a variant of the Uniform Cost Search algorithm, while avoiding obstacles on its path.

Writing a ```add_markers``` node which adds marker (virtual object) in ```RViz``` to simulate picking and dropping off of object by the robot.

Writing shell script to launch the project.

## Output
1. Show marker at the pickup zone. 
2. Hide the marker once the robot reaches the pickup zone
3. Wait 5 seconds to simulate a pickup
4. Show the marker at the drop off zone once your robot reaches it

The robot is unaware of the human figures as can be seen in the map provided to the robot.
ROS Navigation stack actively avoids obstacle in its path.

![](output/output_gif.gif)
Speed: x6 of the original output

## Environment
Tested on Ubuntu 16.04.6 LTS, ROS Kinetic, Boost 1.58

## Setup and run
Note: The commands in this README work, considering that the main workspace is located at ```/home/robond/workspace/catkin_ws/src```      
      Notice the ```robond``` username. Make appropriate changes for your system.

#### 1. Update the Workspace image
```
$ sudo apt-get update && sudo apt-get upgrade -y 
```

#### 2. Clone the files in /home/workspace
Cloning this repository:
```
$ cd /home/robond/workspace/catkin_ws/src
$ git clone https://github.com/Avadhoot94/Home_Service_Robot.git
```
#### 3. Dependencies
```
$ sudo apt-get install ros-kinetic-map-server
$ sudo apt-get install ros-kinetic-amcl
$ sudo apt-get install ros-kinetic-move-base
$ sudo apt-get install ros-kinetic-slam-gmapping
$ sudo apt-get install xterm
```

Clone these ROS packages in the workspace
```
$ cd /home/robond/workspace/catkin_ws/src/Home_Service_Robot
$ git clone https://github.com/ros-perception/slam_gmapping
$ git clone https://github.com/turtlebot/turtlebot
$ git clone https://github.com/turtlebot/turtlebot_interactions
$ git clone https://github.com/turtlebot/turtlebot_simulator
```

#### 3. Build the packages
```
$ cd /home/robond/workspace/catkin_ws
$ catkin_make
$ source devel/setup.bash
````

#### 4. Replace ```view_navigation.launch``` with custom launch file 
The ```view_navigation.launch``` file of ```turtlebot_rviz_launchers``` package brings up ```RViz```.

However, to launch ```RViz``` with custom configuration file, minor tweaking was done to allow passing of RViz config file location as parameter.

The original file path is still a default in the launch file.

```
$ cd /home/robond/workspace/catkin_ws/src/Home_Service_Robot
$ mv view_navigation.launch /home/robond/workspace/catkin_ws/src/Home_Service_Robot/turtlebot_interactions/turtlebot_rviz_launchers/launch
```

#### 5. Launch the script
Turn the script into executable script
```
$ cd /home/robond/workspace/catkin_ws/src/Home_Service_Robot/scripts
$ chmod +x home_service.sh
```

Execute the script
```
$ ./home_service.sh
```

The following are the scripts to test the workings of individual features:
```
$ chmod +x add_markers.sh
$ chmod +x pick_objects.sh
$ chmod +x test_navigation.sh
$ chmod +x test_slam.sh
$ ./test_slam.sh
$ ./test_navigation.sh
$ ./add_markers.sh
$ ./pick_objects.sh
```
