//
// Created by flyinsky on 16-3-8.
//
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "tf_change");
    std::string source_frame;
    std::string target_frame;
    double x = 0;
    double y = 0;
    double z = 0;

    switch (argc) {
        case 1:
        case 2:
            ROS_ERROR_STREAM("NEED AT LEAST A SOURCE FRAME & A TARGET FRAME");
            return -1;
        case 4:
        case 5:
            ROS_ERROR_STREAM("NEED XYZ COORDINATES");
            return -1;
        case 6:
            x = std::stod(argv[3]);
            y = std::stod(argv[4]);
            z = std::stod(argv[5]);
        case 3:
            source_frame = argv[1];
            target_frame = argv[2];
            break;
        default:
            ROS_ERROR_STREAM("NO MORE THAN 6 INPUTS");
            return -1;
    }

    ros::NodeHandle node;
    tf::TransformBroadcaster broadcaster;
    tf::Transform transform;

    ros::Rate rate(10);

    while (node.ok()) {
        transform.setOrigin(tf::Vector3(x, y, z));
        transform.setRotation(tf::Quaternion(0, 0, 0, 1));

        broadcaster.sendTransform(tf::StampedTransform(transform, ros::Time::now(), source_frame, target_frame));

        rate.sleep();
    }
    return 0;

}


