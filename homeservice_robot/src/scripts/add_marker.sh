#!/bin/sh
xterm  -e  " roslaunch my_robot world.launch " &
sleep 5


xterm  -e  " roslaunch where_am_i amcl.launch " &

sleep 5
xterm  -e  "roslaunch rviz_launcher view_test_navigation.launch" &

sleep 5
xterm  -e  "rosrun add_markers add_markers"






