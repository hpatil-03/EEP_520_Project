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
            if (sensor_value(0) < 10) {
                emit(Event("tick"));
            }
        }
        void exit(const Event& e) {}
    };

    class Rotating : public State, public AgentInterface {
    public:
        void entry(const Event& e) { }
        void during() {
            track_velocity(0, 1);
            if (this->angle() > 1.56) {
                std::cout << this->angle() << std::endl;
                emit(Event("tick"));
            }
        }
        void exit(const Event& e) {}
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