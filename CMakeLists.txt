cmake_minimum_required(VERSION 2.8.3)
project(parallel_uav)

find_package(catkin REQUIRED COMPONENTS genmsg roscpp rospy std_msgs std_srvs tf turtlesim)
find_package(Qt4)
find_package(Protobuf REQUIRED)
find_package(gazebo REQUIRED)
catkin_package()


include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

#
include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(SYSTEM ${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})

#
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

## set cmd_vel of a uav [arg1], uav_name
add_executable(set_cmd_vel src/set_cmd_vel.cpp)
target_link_libraries(set_cmd_vel ${catkin_LIBRARIES})

## subscribe tf & generate cmd_vel to follow, [arg1] this_name [arg2] source_tf opt:[arg3] time_delay
add_executable(sub_tf_gen_vel src/sub_tf_gen_vel.cpp)
target_link_libraries(sub_tf_gen_vel ${catkin_LIBRARIES})

## subscribe tf & generate cmd_vel to follow, [arg1] source_tf [arg2] target_tf opt:[arg 3-5] x y z
add_executable(sub_tf_gen_tf src/sub_tf_gen_tf.cpp)
target_link_libraries(sub_tf_gen_tf ${catkin_LIBRARIES})

## spawn several quadrotors, using spawn_and_fly.launch [arg1] total number of uavs
add_executable(spawn_new src/spawn_new.cpp)
target_link_libraries(spawn_new ${catkin_LIBRARIES})

## follow former uav [arg1] this uav name [arg2] time delay
add_executable(follow_uav src/follow_uav.cpp)
target_link_libraries(follow_uav ${catkin_LIBRARIES})


## spawn uav gui
QT4_WRAP_CPP(headers_MOC src/spawn_uav.h)
add_library(spawn_uav_gui SHARED ${headers_MOC} src/spawn_uav.cpp)
target_link_libraries(spawn_uav_gui ${GAZEBO_LIBRARIES} ${QT_LIBRARIES} ${PROTOBUF_LIBRARIES})