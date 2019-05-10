#include "ros/ros.h"
#include <dartv2/Dartv2CmdMotors.h>
#include <geometry_msgs/Twist.h> // got from rostopic type /cmd_vel
extern "C" {
#include "/home/ubuntu/ros/libdartv2i2c/trex_io.h"
#include "/home/ubuntu/ros/libdartv2i2c/i2c.h"
}

int i2c_fd;

// callback activated each time a message is received on the subscribed topic
void cmdMotorsCallback(const dartv2::Dartv2CmdMotors::ConstPtr& msg)
{
  ROS_INFO("Motor's command is [%d:left, %d:right]", msg->cmdLeft, msg->cmdRight);
  // insert here robot hardware command (via i2c)
  int cmdLeft = msg->cmdLeft;
  if (cmdLeft > 255) {
    cmdLeft = 255;
  }
  if (cmdLeft < -255) {
    cmdLeft = -255;
  }
  int cmdRight = msg->cmdRight;
  if (cmdRight > 255) {
    cmdRight = 255;
  }
  if (cmdRight < -255) {
    cmdRight = -255;
  }
  int status = dartv2i2c_trex_cmd_motors (i2c_fd, cmdLeft, cmdRight);
}

// callback activated each time a message from teleop is received
void teleopCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
  float x = msg->linear.x;
  float th = msg->angular.z;
  int cmdLeft = (int) (100.0*x - 100*th);
  int cmdRight = (int) (100.0*x + 100*th);
  ROS_INFO("teleop Motor's command is [%d:left, %d:right]", cmdLeft, cmdRight);
  // insert here robot hardware command (via i2c) 
  if (cmdLeft > 255) {
    cmdLeft = 255;
  }
  if (cmdLeft < -255) {
    cmdLeft = -255;
  }
  if (cmdRight > 255) {
    cmdRight = 255;
  }
  if (cmdRight < -255) {
    cmdRight = -255;
  }
  int status = dartv2i2c_trex_cmd_motors (i2c_fd, cmdLeft, cmdRight);
}

int main(int argc, char **argv)
{
  // Init i2c
  const char *i2c_fname = "/dev/i2c-2";  // device name
  i2c_fd = i2c_init(i2c_fname);

  // init ROS
  ros::init(argc, argv, "cmd_motors");
  // create handle
  ros::NodeHandle n;
  
  // subscribes to dartv2_cmd_motor topic
  ros::Subscriber sub1 = n.subscribe("dartv2_cmd_motor", 1000, cmdMotorsCallback);
  // subscribes to cmd_vel topic from telop
  ros::Subscriber sub2 = n.subscribe("cmd_vel", 1000, teleopCallback);

  // infinite loop wait from messages from topic
  ros::spin();
  return 0;
}