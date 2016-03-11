//
// Created by flyinsky on 16-3-10.
//

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

std::string uav_name;
double time_delay;
int uav_number;

void follow();

void fly_first();

int main(int argc, char **argv) {
    ros::init(argc, argv, "follower");
    time_delay = 2;// set initial time delay

    switch (argc) {
        case 3:
            time_delay = std::stod(argv[2]);
        case 2:
            uav_name = argv[1];
            break;
        default:
            ROS_ERROR_STREAM("WRONG NUMBER OF INPUTS, NEED 1 or 2 ");
            return -1;
    }
    uav_number = std::stoi(uav_name.substr(3));

    if (uav_number == 1) {
        fly_first();
    }
    else {
        follow();
    }
    return 0;
}

void follow() {
    std::string former_uav = "uav" + std::to_string(uav_number - 1);

    ros::NodeHandle node;
//    tf::TransformBroadcaster broadcaster;

    ros::Publisher cmd_vel_pub = node.advertise<geometry_msgs::Twist>("/" + uav_name + "/cmd_vel",
                                                                      10);//cmd_vel publisher
    tf::TransformListener tf_listener;

    ros::Duration(time_delay).sleep();// before time_delay, the subscribe systems sleeps
    ros::Rate rate(10);

    while (node.ok()) {
        tf::StampedTransform transform;

        try {
            ros::Time now = ros::Time::now();
            ros::Time past = now - ros::Duration(time_delay);
            tf_listener.waitForTransform("/" + uav_name + "/base_link", now, "/" + former_uav + "/base_link", past,
                                         "/world",
                                         ros::Duration(1));
            tf_listener.lookupTransform("/" + uav_name + "/base_link", now, "/" + former_uav + "/base_link", past,
                                        "/world", transform);
        }
        catch (tf::TransformException ex) {
            ROS_ERROR_STREAM(ex.what());
            ROS_ERROR_STREAM("FAIL TO READ TRANSFORM!!");
            ros::Duration(0.5).sleep();
        }

        geometry_msgs::Twist msg;
        msg.angular.z = 4 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
        msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));
        msg.linear.z = (transform.getOrigin().z() < 0) ? -sqrt(fabs(transform.getOrigin().z())) : sqrt(
                fabs(transform.getOrigin().z()));

        ROS_INFO_STREAM(uav_name << " !!sending random velocity x:" << msg.linear.x << "  , theta:" << msg.angular.z <<
                        "  z:" << msg.linear.z);

        cmd_vel_pub.publish(msg);
        rate.sleep();

    }

}

void fly_first() {
    ros::NodeHandle node;
    ros::Publisher pub = node.advertise<geometry_msgs::Twist>(uav_name + "/cmd_vel", 1000);

    srand(time(0));
    ros::Rate rate(10);

    ros::Time start = ros::Time::now();
    ros::Duration duration = ros::Duration(30);


    while (ros::ok()) {
        geometry_msgs::Twist msg;

        if (ros::Time::now() - start <= duration) {
            msg.linear.x = double(rand()) / double(RAND_MAX);
            msg.angular.z = double(rand()) / double(RAND_MAX);
            msg.linear.z = 0.5;
        }


        else {
            const double VEL_X = 1;
            msg.linear.x = VEL_X;
            msg.angular.z = M_PI / 10;
            msg.linear.z = sin((ros::Time::now() - start).toSec());
        }

        pub.publish(msg);
        ROS_INFO_STREAM(
                uav_name << "!!sending random velocity x:" << msg.linear.x << "  , theta:" << msg.angular.z << "  z:" <<
                msg.linear.z);
        rate.sleep();
    }

    while (ros::ok()) {

    }
}

