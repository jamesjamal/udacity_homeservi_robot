# udacity_homeservi_robot
finsal project in udacity robotic sdoftware engineerign course

# ROS based Autonamous service robot

Use the below commnad to check the dependencies needed to run the homeservice_robot

$  `source devel/setup.bash`

$ `<rospack depends [name of package]>`


## To Lauch homeservice_robot 

1. clone the repo 

2. navigate inside /homeservice_robot

3. use command `source devel/setup.bash`

Use .sh files created inside src/scripts 

4. `./home_service.sh` to launch the robot anvigation stack and marker facilities to locate pickup and drop location 

5. This script launches all the nodes necessary for navigating inside thedefined map.


## To Try mapping using gmmaping 

use .sh file inside src/scripts/test_slam.sh

use command `./test_slam.sh`


which launches necessary nodes such as robot in gazebo with sensors , gmapping and teleop 


### To launch robot in gazebo

`roslaunch roslaunch my_robot world.launch`
