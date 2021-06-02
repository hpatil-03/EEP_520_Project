#ifndef __MY_ROBOT_AGENT__H
#define __MY_ROBOT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class MyRobotController : public Process, public AgentInterface {

    public:
    MyRobotController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update(); 
    void stop() {}

};

class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MyRobotController c;
};

DECLARE_INTERFACE(MyRobot)


void MyRobotController::update() {
    {
        if (sensor_value(0) > 50) {
            track_velocity(10, 0);
        }
        else {
            move_toward(0, 1.57);
           //track_velocity(0, 1.57);
            //track_velocity(10, 0);
        }
    }
}




#endif