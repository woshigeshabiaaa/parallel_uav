//
// Created by flyinsky on 16-3-8.
//

#include <ros/ros.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "fly_command");
    const int TOTAL_NUMBER = std::stoi(argv[1]);

    ros::NodeHandle node;


    for (int i = 1; i <= TOTAL_NUMBER && node.ok(); i++) {
        double x_place = 4 * i;
        std::stringstream cmd_stream;
        cmd_stream << "roslaunch parallel_uav spawn_and_fly.launch uav_number:=" << i << " x:=" << x_place;
        const char *cmd = cmd_stream.str().c_str();
        system(cmd);
    }
//    system("rosrun parallel_uav sub_tf_gen_tf uav1/base_link carrot");
//    system("rosrun parallel_uav sub_tf_gen_vel uav2 carrot 2");


    return 0;
}