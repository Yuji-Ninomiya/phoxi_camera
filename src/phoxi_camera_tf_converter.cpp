#include <std_msgs/String.h>
#include <pcl_ros/point_cloud.h>
#include <pcl_ros/transforms.h>
#include <ros/ros.h>

#include <tf/transform_broadcaster.h>
// #include <turtlesim/Pose.h>

// usenamespace: PCL



void pointcloudCallBack(const sensor_msgs::PointCloud2::ConstPtr& phoxi_pointcloud )
{

	tf::Transform phoxi_frame;
	tf::TransformListener tf_lis;
	tf::TransformBroadcaster br;
	tf::StampedTransform transform;

	ros::Time time = ros::Time::now();
	
	try{
		tf_lis.waitForTransform("/world", phoxi_pointcloud->header.frame_id, ros::Time(0), ros::Duration(10.0));
		tf_lis.lookupTransform("/world", phoxi_pointcloud->header.frame_id, ros::Time(0), transform);

		br.sendTransform(tf::StampedTransform(phoxi_frame, time, "/world", "phoxi_frame"));
		
		// ros::NodeHandle nh;
		// ros::Publisher phoxi_pub = nh.advertise<sensor_msgs::PointCloud2>("/phoxi_xl_", 1);
		// phoxi_cloud_pub.publish(phoxi_xl_);

		// ros::Subscriber phoxi_sub = nh.advertise<sensor_msgs::PointCloud2>("/phoxi_camera/pointcloud", 10, &pointcloudCallBack);

	}catch (tf::TransformException ex){
		ROS_ERROR("%s",ex.what());
		ros::Duration(1.0).sleep();
	}
}
	
			
int main(int argc, char **argv)
{
	ros::init(argc, argv, "phoxi_tf_converter");
	ros::NodeHandle nh;
	// ros::Subscriber phoxi_sub = nh.advertise<sensor_msgs::PointCloud2>("/phoxi_camera/pointcloud", 10, pointcloudCallBack);
	ros::Subscriber phoxi_sub = nh.subscribe("/phoxi_camera/pointcloud", 10, pointcloudCallBack);
	
	ros::spin();
	return 0;
};
