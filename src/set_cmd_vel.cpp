//
// Created by flyinsky on 16-3-8.
//

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "uav_cmd_vel");

    if (argc != 2) {
        ROS_INFO_STREAM("need a uav name");
        return -1;
    }

    std::string uav_name = argv[1];

    ros::NodeHandle node;
    ros::Publisher pub = node.advertise<geometry_msgs::Twist>(uav_name + "/cmd_vel", 1000);

    srand(time(0));
    ros::Rate rate(10);

    while (ros::ok()) {
        geometry_msgs::Twist msg;
        msg.linear.x = double(rand()) / double(RAND_MAX);
        msg.angular.z = double(rand()) / double(RAND_MAX);

        msg.linear.z = 0.25;

        pub.publish(msg);
        ROS_INFO_STREAM(uav_name<<"!!sending random velocity x:" << msg.linear.x << "  , theta:" << msg.angular.z << "  z:" <<
                        msg.linear.z);
        rate.sleep();
    }
    return 0;
}
