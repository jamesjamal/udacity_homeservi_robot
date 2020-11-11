#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


bool publish = true;
bool drop = false;
int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;
  
  
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
   

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header



    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      
      sleep(1);
    }



    if (publish == true && drop == false )
  {

    ROS_INFO("publishing  marker for 5 sec");


    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker_pub.publish(marker);

    ros::Duration(5).sleep();

    publish = false;


  }
    
  


  
   // marker_pub.publish(marker);
       
  if(publish == false ){
    marker.action = visualization_msgs::Marker::DELETE;

    marker_pub.publish(marker);

    ROS_INFO("deleted marker waiting 5 sec");

    ros::Duration(5).sleep();

    drop = true;
}
 

if(drop == true){
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = 1;
    marker.pose.position.y = 1;
    marker.pose.position.z = 0;
    marker_pub.publish(marker);
    ROS_INFO("ADDED marker at goal");

    publish = true;

  }

 
   



    r.sleep();
  }
}