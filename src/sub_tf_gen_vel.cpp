//
// Created by flyinsky on 16-3-8.
//

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "tf_listener");
    std::string this_name;
    std::string source_frame;
    double time_delay = 0;

    switch (argc) {
        case 4:
            time_delay = std::stod(argv[3]);
        case 3:
            this_name = argv[1];
            source_frame = argv[2];
            break;
        default:
            ROS_ERROR_STREAM("WRONG NUMBER OF INPUTS, NEED 2 or 3");
            return -1;
    }

    ros::NodeHandle node;
    ros::Publisher cmd_vel_pub = node.advertise<geometry_msgs::Twist>("/" + this_name + "/cmd_vel", 10);

    tf::TransformListener tf_listener;
    ros::Duration(time_delay).sleep();// before time_delay, the subscribe systems sleeps

    ros::Rate rate(10);
    while (node.ok()) {
        tf::StampedTransform transform;

        try {
            ros::Time now = ros::Time::now();
            ros::Time past = now - ros::Duration(time_delay);
            tf_listener.waitForTransform("/" + this_name + "/base_link", now, source_frame, past, "/world",
                                         ros::Duration(1));
            tf_listener.lookupTransform("/" + this_name + "/base_link", now, source_frame, past, "/world", transform);
        }
        catch (tf::TransformException ex) {
            ROS_ERROR_STREAM(ex.what());
            ROS_ERROR_STREAM("FAIL TO READ TRANSFORM!!");
            ros::Duration(0.5).sleep();
        }

        geometry_msgs::Twist msg;
        msg.angular.z = 4 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
        msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));
        msg.linear.z = pow(transform.getOrigin().z(), 2);

        ROS_INFO_STREAM(this_name << " !!sending random velocity x:" << msg.linear.x << "  , theta:" << msg.angular.z <<
                        "  z:" <<
                        msg.linear.z);

        cmd_vel_pub.publish(msg);
        rate.sleep();

    }


}
