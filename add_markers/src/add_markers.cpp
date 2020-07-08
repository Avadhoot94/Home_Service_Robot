
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <math.h>


double pose_x, pose_y, diff_p_x, diff_p_y, diff_d_x, diff_d_y;
double pickup_x = 31.5613;
double pickup_y = 8.06135;
double dropoff_x = 14.9297647476;
double dropoff_y = 4.60580825806;
double tolerance = 0.5000000;
int z =0;
int z1 =0;
int z2 =0;

void currentposeCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &pose_amcl)
{
  // Update robot position
  pose_x = pose_amcl->pose.pose.position.x;
  pose_y = pose_amcl->pose.pose.position.y;
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);


 // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  ros::Subscriber current_pose = n.subscribe("/amcl_pose", 1000, currentposeCallback);

  while (ros::ok())
  {

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;


    // Set the marker type.  
    marker.type = visualization_msgs::Marker::CUBE;




 	while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
    }

	diff_p_x = fabs(pose_x - pickup_x);
	diff_p_y = fabs(pose_y - pickup_y);
	diff_d_x = fabs(pose_x - dropoff_x);
	diff_d_y = fabs(pose_y - dropoff_y);

	if(z==0 && z1==0)
	{
		marker.pose.position.x = pickup_x;
	    marker.pose.position.y = pickup_y;
	    marker.pose.position.z = 0;
	    marker.pose.orientation.x = 0.0;
	    marker.pose.orientation.y = 0.0;
	    marker.pose.orientation.z = 0.0;
	    marker.pose.orientation.w = 1.0;

	    marker.scale.x = 1.0;
	    marker.scale.y = 1.0;
	    marker.scale.z = 1.0;

	    marker.color.r = 0.0f;
	    marker.color.g = 1.0f;
	    marker.color.b = 0.0f;
	    marker.color.a = 1.0;

    	marker.lifetime = ros::Duration();
		marker.action = visualization_msgs::Marker::ADD;
   		marker_pub.publish(marker);
   		ROS_INFO("Marker added at pick-up point pose");
		z1=1;

	}


	if(diff_p_x<tolerance && diff_p_y<tolerance && z2==0)
	{
		marker.action = visualization_msgs::Marker::DELETE;
	   	marker_pub.publish(marker);
	   	ROS_INFO("Marker deleted at pick-up point");
	   	ros::Duration(5.0).sleep();
	   	z=1;
		z2=1;
	}



	if (diff_d_x<tolerance && diff_d_y<tolerance)
	{
	 	marker.pose.position.x = dropoff_x;
	    marker.pose.position.y = dropoff_y;
	    marker.pose.position.z = 0;
	    marker.pose.orientation.x = 0.0;
	    marker.pose.orientation.y = 0.0;
	    marker.pose.orientation.z = 0.0;
	    marker.pose.orientation.w = 1.0;
	    marker.scale.x = 1.0;
	    marker.scale.y = 1.0;
	    marker.scale.z = 1.0;

	    marker.color.r = 0.0f;
	    marker.color.g = 1.0f;
	    marker.color.b = 0.0f;
	    marker.color.a = 1.0;

		marker.lifetime = ros::Duration();

	   	marker.action = visualization_msgs::Marker::ADD;
	    marker_pub.publish(marker);
		ROS_INFO("Marker added at drop-off point");

	   
		ros::Duration(20.0).sleep();
		break;
	}


	ros::spinOnce();
  }
  return 0;
}

