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

# As reviewer suggested, the loaind map is moved into amcl_demo.launch file to avoid hard coded paths.
    xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
    sleep 5

# As reviewer suggested, moved this step into add markers.launch file to avoid hard coded paths.
#    xterm -e "rosrun rviz rviz -d /home/nvidia/ros_ws/homeservice_ws/src/World/RvizConfig/homeservicebot-addMarker.rviz" &
#    sleep 10

    xterm -e "roslaunch add_markers add_markers.launch" &
    sleep 5


fi
