#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

namespace {

    using namespace enviro;

    class MovingForward : public State, public AgentInterface {
    public:
        void entry(const Event& e) {}
        void during() {
            track_velocity(10, 0);
            std::cout << "sensor" << sensor_value(0) << std::endl;
            if (sensor_value(0) < 30) {
                std::cout << "movingforward->rorate state change"<<"angle" <<angle()<< std::endl;
                emit(Event("tick"));
            }
        }
        void exit(const Event& e) {}
    };

    class Rotating : public State, public AgentInterface {
    public:
        void entry(const Event& e) { }
        void during() {
            if (lock == 0) {
                lock = 1;
                if (sensor_value(1) > sensor_value(2)) {
                    direction = 0;
                    total_angle += 1.5708;

                }
                else if (sensor_value(2) > sensor_value(1)) {
                    direction = 1;
                    total_angle -= 1.5708;
                }
            }
            if ((direction == 0)&&(angle()<= total_angle)){
                track_velocity(0, 1.5708);
                
            }
            else if ((direction == 1) && (angle() <= total_angle)) {
                track_velocity(0, -1.5708);
                
            }
            std::cout << "angle"<<this->angle()<<"total_angle"<< total_angle << std::endl;
            if (angle() >= total_angle) {
                std::cout << "rotate->movingforward state change" << std::endl;
                lock = 0;
                emit(Event("tick"));
            }
           
        }
        void exit(const Event& e) {}
    private:
        float total_angle = 0;
        int lock = 0,direction=0;
    };
    


    class WandererController : public StateMachine, public AgentInterface {

    public:
        WandererController() : StateMachine() {
            set_initial(moving_forward);
            add_transition("tick", moving_forward, rotating);
            add_transition("tick", rotating, moving_forward);
        }

        MovingForward moving_forward;
        Rotating rotating;
    };

    class Wanderer : public Agent {

    public:
        Wanderer(json spec, World& world) : Agent(spec, world) {
            add_process(wc);
        }

        WandererController wc;

    };

    DECLARE_INTERFACE(Wanderer);

}

#endif