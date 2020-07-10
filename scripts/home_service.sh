#!/bin/sh

xterm -e "source devel/setup.bash" &
sleep 2
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:="/home/robond/workspace/catkin_ws/src/Home_Service_Robot/map/Avadhoot.world" " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:="/home/robond/workspace/catkin_ws/src/Home_Service_Robot/map/map.yaml" initial_pose_x:="31.7741470337" initial_pose_y:="15.2176485443" initial_pose_a:="0.00690776336482"" & 
sleep 5
xterm  -e  "roslaunch turtlebot_rviz_launchers view_navigation.launch rviz_file:="-d/home/robond/workspace/catkin_ws/src/Home_Service_Robot/rvizConfig/new_rviz_config.rviz"" &

echo "Press any Enter to start sending the commands to robot"
read random_variable

xterm -e "rosrun add_markers add_markers" &
sleep 2	
xterm -e   "rosrun pick_objects pick_objects"

	
