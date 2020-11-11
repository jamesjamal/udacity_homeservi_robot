#!/bin/sh
xterm  -e  " roslaunch my_robot world.launch " &
sleep 5


xterm  -e  " roslaunch where_am_i amcl.launch " &

sleep 5
xterm  -e  "roslaunch rviz_launcher homeservice.launch" &

sleep 5
xterm  -e  "rosrun add_markers subs"&

sleep 5
xterm  -e  "rosrun pick_objects pick_objects"&






