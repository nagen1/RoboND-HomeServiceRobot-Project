#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main( int argc, char** argv )
{
    ros::init(argc, argv, "basic_shapes");
    ros::NodeHandle n;
    ros::Rate r(1);
    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    MoveBaseClient ac("move_base", true);
    move_base_msgs::MoveBaseGoal goal;

    ac.waitForServer(ros::Duration(5.0));
    float x = 5.5;
    float y = 1.20;
    int goalCount = 0;

    //Sending 1st Goal
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose.position.x = x; //was 5.5;
    goal.target_pose.pose.position.y = y; // was 1.20;
    goal.target_pose.pose.orientation.w = 1.0; //was 1.0;
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);

    while (goalCount < 2)
    {
       visualization_msgs::Marker marker;
       marker.header.frame_id = "map";
       marker.header.stamp = ros::Time::now();

       marker.ns = "basic_shapes";
       marker.id = 0;

       marker.type = visualization_msgs::Marker::SPHERE;
       marker.action = visualization_msgs::Marker::ADD;

       //Marker 1
       marker.pose.position.x = x;
       marker.pose.position.y = y;
       marker.pose.position.z = 0.50;
       marker.pose.orientation.x = 0.0;
       marker.pose.orientation.y = 0.0;
       marker.pose.orientation.z = 0.0;
       marker.pose.orientation.w = 1.0;

       // Set the scale of the marker -- 1x1x1 here means 1m on a side
       marker.scale.x = 0.25;
       marker.scale.y = 0.25;
       marker.scale.z = 0.25;

       // Set the color -- be sure to set alpha to something non-zero!
       marker.color.r = 255.0f;
       marker.color.g = 1.0f;
       marker.color.b = 0.0f;
       marker.color.a = 1.0;

       marker.lifetime = ros::Duration();

       // Publish the marker
       marker_pub.publish(marker);
       ac.waitForResult();

       if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
        ROS_INFO("Hooray, the turtle reached Goal Position x: %f y: %f and Object Picked up", x, y);
        ROS_INFO("5 Seconds delay/Wait time before Next Goal triggers");
        ros::Duration(5.0).sleep();
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        ++goalCount;

        //Sending 2nd Goal and Marker 2
        x = -2.5;
        y = -6.20;
        goal.target_pose.pose.position.x = x; //was 5.5;
        goal.target_pose.pose.position.y = y; // was 1.20;
        goal.target_pose.pose.orientation.w = 1.0; //was 1.0;
        ROS_INFO("Sending goal");
        ac.sendGoal(goal);
        }

      else {
        ROS_INFO("The turtle failed to reach goal for some reason");
        ros::Duration(5.0).sleep();
        }
    }
 }
