#!/usr/bin/env bash

read -p "Please enter home path. Example: /home/nvidia/catkin_ws : "  ws

if [ -z $ws ];
then
    echo "Please run the script again and enter workspace"
else
    #ws="/home/nvidia/ros_ws/homeservice_ws"

    source /opt/ros/kinetic/setup.bash
    source $ws/devel/setup.bash

    xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch" &
    sleep 5

    xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
    sleep 5

    xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
    sleep 10

    xterm -e "roslaunch mbot_simple_goal mbot_simple_goal.launch" &
    sleep 5

fi
