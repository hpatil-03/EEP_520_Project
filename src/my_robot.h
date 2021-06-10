#ifndef __WANDERER_AGENT__H
#define __WANDERER_AGENT__H 

#include <string>
#include <math.h>
#include "enviro.h"

double total_angle = 0;
namespace {

	using namespace enviro;

	//! Class MovingForward inheritates from State and AgentInterface class
	//! The State MovingForward is used when the agent is going forward 
	class MovingForward : public State, public AgentInterface {
	public:

		//! Initiate and retrieve current angle of the agent 
		//! \param e Event 
		void entry(const Event& e) {
			total_angle = angle();
		}

		//! moves agent with constant velocity until sensor value reaches threshold
		//! triggers event to change state to rotating  
		void during() {
			track_velocity(25, 0);
			std::cout << "sensor" << sensor_value(0) << std::endl;
			if (sensor_value(0) < 25) {
				std::cout << "movingforward->rotate state change" << "angle" << angle() << std::endl;
				emit(Event("tick"));
			}
		}
		//! exit MovingForward state
		//! \param e Event
		void exit(const Event& e) {}
	};

	//! Class Rotating inheritates from State and AgentInterface class
	//! The State MovingForward is used when the agent is going forward 
	class Rotating : public State, public AgentInterface {
	public:
		//! Enter Rotating state
		//! \param e Event
		void entry(const Event& e) { }

		//! rotates agent with and an angleo 0f 1.5708 radians or -1.5708 depending on the sensor values
		//! to precise with the angle, agent's angle is checked before triggering event to change state to MovingForward   
		void during() {
			if (lock == 0) {
				lock = 1;
				if (sensor_value(1) > sensor_value(2)) {
					direction = 0;
					total_angle += 1.5708;

				}
				else if (sensor_value(2) >= sensor_value(1)) {
					direction = 1;
					total_angle -= 1.5708;
				}
			}
			if ((direction == 0) && (angle() <= total_angle)) {
				track_velocity(0, 1.5708);
			}
			else if ((direction == 1) && (angle() >= total_angle)) {
				track_velocity(0, -1.5708);
			}
			std::cout << "angle" << this->angle() << "total_angle" << total_angle << std::endl;
			if ((direction == 0 && angle() >= total_angle) || (direction == 1 && angle() <= total_angle)) {
				auto pos_agent = position();
				while (angle() != total_angle)
				{
					teleport(pos_agent.x, pos_agent.y, total_angle);
				}
				std::cout << "rotate->movingforward state change" << std::endl;
				lock = 0;
				emit(Event("tick"));
			}

		}
		//! exit MovingForward state
		//! \param e Event
		void exit(const Event& e) {}

	private:

		int lock = 0, direction = 0;
	};


	//! Class RobotController inheritates from StateMachine and AgentInterface class
	//! The class RobotController is set initial state to moveforward and to add_transition function 
	//! triggered via events 
	class RobotController : public StateMachine, public AgentInterface {

	public:
		//! Constructor setting initial movement to forward
		RobotController() : StateMachine() {
			set_initial(moving_forward);
			add_transition("tick", moving_forward, rotating);
			add_transition("tick", rotating, moving_forward);
		}

		MovingForward moving_forward;
		Rotating rotating;
	};

	//! Class Controller inheritates from Agent class
	//! The class RobotController adds a process and creates RobotController object
	class Controller : public Agent {

	public:
		//! Constructor adds a process
		Controller(json spec, World& world) : Agent(spec, world) {
			add_process(wc);
		}

		RobotController wc;

	};

	DECLARE_INTERFACE(Controller);

}

#endif