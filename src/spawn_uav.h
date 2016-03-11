//
// Created by flyinsky on 16-3-9.
//

#ifndef PROJECT_SPAWN_SPHERE_H
#define PROJECT_SPAWN_SPHERE_H

#include "gazebo/common/Plugin.hh"
#include "gazebo/gui/GuiPlugin.hh"

#ifndef Q_MOC_RUN

#include "gazebo/transport/transport.hh"
#include "gazebo/gui/gui.hh"

#endif

using namespace gazebo;

class GAZEBO_VISIBLE SpawnUavGui : public GUIPlugin {
Q_OBJECT;
public:

    SpawnUavGui();

    virtual ~SpawnUavGui();

protected slots:

    void onButton();

private:
    int counter;
//    transport::NodePtr node;
//    transport::PublisherPtr pub;
};


#endif //PROJECT_SPAWN_SPHERE_H
