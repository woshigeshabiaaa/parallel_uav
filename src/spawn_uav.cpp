//
// Created by flyinsky on 16-3-9.
//

#include <ros/node_handle.h>
#include "spawn_uav.h"

using namespace gazebo;

GZ_REGISTER_GUI_PLUGIN(SpawnUavGui);

SpawnUavGui::SpawnUavGui()
        : GUIPlugin() {

    this->counter = 0;
    this->setStyleSheet("QFrame {background-color : rgba(100,100,100,255); color : white;}");

    QHBoxLayout *main_layout = new QHBoxLayout();
    QFrame *main_frame = new QFrame();
    QVBoxLayout *frame_layout = new QVBoxLayout();

    QPushButton *button = new QPushButton(tr("Spawn Quadrotor"));
    connect(button, SIGNAL(clicked()), this, SLOT(onButton()));

    frame_layout->addWidget(button);
    main_frame->setLayout(frame_layout);
    main_layout->addWidget(main_frame);

    frame_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout);

    this->move(10, 10);
    this->resize(120, 30);
}

SpawnUavGui::~SpawnUavGui() { }

void SpawnUavGui::onButton() {
    ROS_INFO_STREAM("!!!!! kai shi yun xing qprocess");
    this->counter++;

    QString uav_number = QString("uav_number:=").append(QString::number(this->counter));
    QString x = QString("x:=").append(QString::number(this->counter));
//    QString x = QString("x:=10");

    QString program = "roslaunch";
    QStringList arguments;

    arguments << "parallel_uav" << "spawn_and_fly.launch" << uav_number << x;
//    arguments << "parallel_uav" << "spawn_and_fly.launch" << x;

    QProcess *my_process = new QProcess();
    my_process->start(program, arguments);
    ROS_INFO_STREAM("!!!!! done xing qprocess");

}
