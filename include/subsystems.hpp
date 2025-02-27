#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;
// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor LB(5);
inline pros::Rotation LBRotation(18);

inline void SpinLB(int volts){
 LB.move((-0.1)*volts);
}

inline ez::PID liftPID{0.2, 0, 0, 0, "Lift"};


inline void lift_task() {
  pros::delay(2000);  // Set EZ-Template calibrate before this function starts running
  while (true) {
    SpinLB(liftPID.compute(LBRotation.get_position()));

    pros::delay(ez::util::DELAY_TIME);
  }
}

inline pros::Task Lift_Task(lift_task);

inline void liftControl(double target){
  double kp = 0.5;
  double error = target - LBRotation.get_position();
  double velocity = kp * error;
  LB.move(velocity);
}








inline void lift_auto(double target) {
    liftPID.target_set(target);
    while (liftPID.exit_condition({LB}, true) == ez::RUNNING) {
      double output = liftPID.compute(LBRotation.get_position());
      SpinLB(output);
      pros::delay(ez::util::DELAY_TIME);
    }
    SpinLB(0);
  }
  
inline pros::Optical ColorSort(1);


inline void lift_wait() {
  liftPID.exit_condition_set(0.1,-140,0.3,-160,500,500);
  while (liftPID.exit_condition({LB}, true) == ez::RUNNING) {
    pros::delay(ez::util::DELAY_TIME);
  }
}
  
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');