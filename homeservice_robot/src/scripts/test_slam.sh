#!/bin/sh
xterm  -e  " roslaunch my_robot world.launch " &
sleep 5


xterm  -e  " rosrun gmapping slam_gmapping" &

sleep 5
xterm  -e  "roslaunch rviz_launcher view_test_navigation.launch" &

sleep 5
xterm  -e  "rosrun teleop_twist_keyboard teleop_twist_keyboard.py"




