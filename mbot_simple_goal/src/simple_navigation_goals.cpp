#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


float goalonecallback(float x, float y, int go){

    MoveBaseClient ac("move_base", true);
    move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = x; //was 5.5;
  goal.target_pose.pose.position.y = y; // was 1.20;
  goal.target_pose.pose.orientation.w = 1.0; //was 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the turtle reached Goal %d Position x: %f y: %f", go, x, y);
    ros::Duration(5.0).sleep();
    }

  else {
    ROS_INFO("The turtle failed to Goal %d for some reason", go);
    ros::Duration(5.0).sleep();
    }

  return 0;
}

int main(int argc, char** argv){

  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // Sending - Goal 1
  goalonecallback(5.5, 1.20, 1);

  // Sending - Goal 2
  goalonecallback(-2.5, -6.20, 2);

}

