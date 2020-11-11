#include <ros/ros.h>
#include <tf/tf.h>
#include <geometry_msgs/Twist.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>
#include <nav_msgs/Odometry.h>


class odom_monitor{

	public:
	odom_monitor() 
	{
        marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
        odom_sub = n.subscribe("/odom", 1, &odom_monitor::odomCallback, this);

        // initialize marker and show marker at pickup zone
        // Set the frame ID and timestamp.  See the TF tutorials for information on these.
        marker.header.frame_id = "map";
        marker.header.stamp = ros::Time::now();

        // Set the namespace and id for this marker.  This serves to create a unique ID
        // Any marker sent with the same namespace and id will overwrite the old one
        marker.ns = "add_markers";
        marker.id = 0;

        // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
        marker.type = visualization_msgs::Marker::SPHERE;

        // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
        marker.action = visualization_msgs::Marker::ADD;

        // Set the scale of the marker -- 1x1x1 here means 1m on a side
        marker.scale.x = 0.25;
        marker.scale.y = 0.25;
        marker.scale.z = 0.25;

        // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;


        // Set marker's initial coordinates
        setMarkerPosition(service_zone[0][0], service_zone[0][1]);

        marker.lifetime = ros::Duration();
		

    }

	
    void odomCallback(const nav_msgs::Odometry::ConstPtr& msg)
	  {

	   //ROS_INFO("Seq: [%d]", msg->header.seq);
	   //ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
	   //ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
	   //ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
        float pos_y=  msg->pose.pose.position.y;
	    float pos_x=  msg->pose.pose.position.x;

		pickup = fabs(service_zone[0][0]-(pos_x)) + fabs(service_zone[0][1]-fabs(pos_y));
       	drop = fabs(service_zone[1][0]-(pos_x)) + fabs(service_zone[1][1]-fabs(pos_y));

	   // ROS_INFO("picked up [%f]", pickup);


	    if (pickup <= 0.2)
	    {
           ROS_INFO("reached for pickup");
		   ROS_INFO("waiting for simulate pickup");

		   marker.action = visualization_msgs::Marker::DELETE;
            // hide marker and set it to new coordinates
           // setMarkerPosition(service_zone[1][0], service_zone[1][1]);
           //marker.color.a = 1.0;

		   picked = true;
			

        }

		else if((drop <= 0.2) && (picked == true))
		{
            ROS_INFO("droping of the pickup");
			marker.action = visualization_msgs::Marker::ADD;
			setMarkerPosition(service_zone[1][0], service_zone[1][1]);
			marker.type = visualization_msgs::Marker::CUBE;
			publishMarker();

		}

		else
		{
			publishMarker();
		}

    }

    void setMarkerPosition(double pos_x, double pos_y) 
	{
        // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        marker.pose.position.x = pos_x;
        marker.pose.position.y = pos_y;
    }

    void publishMarker() 
	{
        // Publish the marker
        while (marker_pub.getNumSubscribers() < 1) {
            ROS_WARN_ONCE("Please create a subscriber to the marker");
            sleep(1);
        }

        marker_pub.publish(marker);
    }

   private:
     ros::NodeHandle n;
     ros::Publisher marker_pub;
     ros::Subscriber odom_sub;
	visualization_msgs::Marker marker;
	double service_zone[2][2] ={{7,1},{0,0}};

	bool picked =false;
	bool droped =false;
	float pickup ;
	float drop;

};


	


int main(int argc, char **argv)
{

	double x_pos;
	ros::init(argc, argv, "subs");
    odom_monitor odom_marker;

	
    //subscriber lister the msgs of given topic
    ros::spin();//run it until you press ctrl+c
	
	return 0;


}
