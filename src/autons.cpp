#include "EZ-Template/util.hpp"
#include "main.h"
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

void Brownie(int a){
  while (pros::c::motor_get_position(20) < a)
  {
    LB.move(-127);
  }
  
}

void SpinIntake(int volts){
  Intake.move(volts);
} 

bool isRedTeam = true;
bool colorSortEnabled = true;

void colorSortTask(int volts){
  while (true){
    int hue = ColorSort.get_hue();
    screen_print(std::to_string(hue));

    if (colorSortEnabled){
      ColorSort.set_led_pwm(100);
    }
    else{
      ColorSort.set_led_pwm(0);
    }
    if (hue < 20  && colorSortEnabled){
      Intake.brake();
      pros::delay(390);
      Intake.move(-127);
  
    Intake.move(volts);
    pros::delay(ez::util::DELAY_TIME);
  }
}
}

void Loser(int volts){
  int color = 0;

  ColorSort.set_led_pwm(100);
  // COLORSORT
      // RED
      // Senses for blue rings to eject
      while(true){
      if (color == 0 && (ColorSort.get_hue() <= 230 && ColorSort.get_hue() >= 200) &&
          ColorSort.get_proximity() <= 30) {
        // for proximity => need to tune cuz idk what unit it returns
        // if optical sensor is in a weird spot u might need a delay here
        Intake.move(0); // stops intake
        pros::delay(100);           // ensures the ring has time to fly
      }
      else{
        Intake.move(volts);
      }
    }
}


void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(50, 0, 100);
  chassis.pid_turn_constants_set(6, 0, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches


  // JUST DRIVE
  /*chassis.pid_drive_set(-15_in,70);
  chassis.pid_wait();*/
//BLUE SIDE 5 RING


chassis.pid_turn_set(45_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(1, 60);
chassis.pid_wait();

chassis.pid_drive_set(-20_in,60);
chassis.pid_wait();
chassis.pid_turn_set(0_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-22_in,30);
chassis.pid_wait();
Clamp.extend();
pros::delay(100);
chassis.pid_turn_set(-140_deg,50);
chassis.pid_wait();
chassis.pid_drive_set(11,60);
chassis.pid_wait();
pros::delay(100);
SpinIntake(-127);
chassis.pid_swing_relative_set(LEFT_SWING, 50_deg, 60);
chassis.pid_wait();
pros::delay(100);
chassis.pid_drive_set(11_in,60);
chassis.pid_wait();
chassis.pid_swing_set(LEFT_SWING, 45_deg, 60);
chassis.pid_wait();
chassis.pid_drive_set(20,70);
chassis.pid_wait();
chassis.pid_drive_set(20,60);
chassis.pid_wait();
chassis.pid_turn_set(90_deg,TURN_SPEED);
chassis.pid_wait();
Raise.extend();
chassis.pid_drive_set(15,60);
chassis.pid_wait();
Raise.retract();
chassis.pid_drive_set(-10,40);
chassis.pid_wait();
SpinIntake(80);
pros::delay(100);
SpinIntake(-127);
pros::delay(5000);


//Red SIDE 5 RING
//colorSortTask(-90);
//pros::delay(100000);
//colorSortTask(0);
/*
chassis.pid_turn_set(-45_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(1, 60);
chassis.pid_wait();
Lift_Task.resume();
liftPID.target_set(20000);
lift_wait();
Lift_Task.suspend();
chassis.pid_drive_set(-20_in,60);
chassis.pid_wait();
chassis.pid_turn_set(0_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-22_in,30);
chassis.pid_wait();
Clamp.extend();
pros::delay(100);
chassis.pid_turn_set(140_deg,50);
chassis.pid_wait();
chassis.pid_drive_set(11,60);
chassis.pid_wait();
pros::delay(100);
SpinIntake(-100);
chassis.pid_swing_relative_set(RIGHT_SWING, -50_deg, 60);
chassis.pid_wait();
pros::delay(100);
chassis.pid_drive_set(11_in,60);
chassis.pid_wait();
chassis.pid_swing_set(RIGHT_SWING, -45_deg, 60);
chassis.pid_wait();
chassis.pid_drive_set(20,70);
chassis.pid_wait();
chassis.pid_drive_set(20,60);
chassis.pid_wait();
chassis.pid_turn_set(-90_deg,TURN_SPEED);
chassis.pid_wait();
Raise.extend();
chassis.pid_drive_set(25,60);
chassis.pid_wait();
Raise.retract();
chassis.pid_drive_set(-10,40);
chassis.pid_wait();
SpinIntake(80);
pros::delay(100);
SpinIntake(-110);
pros::delay(5000);
*/


//Red Pos side ladder half awp
/*chassis.pid_turn_set(45_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(1, 60);
Lift_Task.resume();
liftPID.target_set(20000);
lift_wait();
Lift_Task.suspend();
chassis.pid_drive_set(-18_in,60);
chassis.pid_wait();
chassis.pid_turn_set(0_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-22_in,30);
chassis.pid_wait();
Clamp.extend();
pros::delay(200);
SpinIntake(-80);
chassis.pid_turn_set(-90,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(20,70);
chassis.pid_wait();
pros::delay(700);
chassis.pid_turn_set(110_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(30,50);
chassis.pid_wait();
pros::delay(5000);*/
  


//Blue Pos side ladder half awp


/*chassis.pid_turn_set(-45_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(1, 60);
chassis.pid_wait();
Lift_Task.resume();
liftPID.target_set(20000);
lift_wait();
Lift_Task.suspend();
chassis.pid_drive_set(-18_in,60);
chassis.pid_wait();
chassis.pid_turn_set(0_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-22_in,30);
chassis.pid_wait();
Clamp.extend();
pros::delay(200);
SpinIntake(-80);
chassis.pid_turn_set(90,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(20,70);
chassis.pid_wait();
pros::delay(100);
chassis.pid_turn_set(-110_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(30,50);
chassis.pid_wait();
pros::delay(5000);*/

//Blue Pos side no alliance

/*chassis.pid_drive_set(-37_in,30);
chassis.pid_wait();
Clamp.extend();
SpinIntake(-80);
pros::delay(700);
chassis.pid_turn_set(90,70);
chassis.pid_wait();
chassis.pid_drive_set(20,70);
chassis.pid_wait();
pros::delay(500);
chassis.pid_turn_set(-110_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(30,50);
chassis.pid_wait();
pros::delay(5000);*/

//Red Pos Side No alliance
/*chassis.pid_drive_set(-37_in,30);
chassis.pid_wait();
Clamp.extend();
SpinIntake(-80);
pros::delay(700);
chassis.pid_turn_set(-90,70);
chassis.pid_wait();
chassis.pid_drive_set(20,70);
chassis.pid_wait();
pros::delay(500);
chassis.pid_turn_set(110_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(30,50);
chassis.pid_wait();
pros::delay(5000);*/

  //skills
//THIS DROPS FIRST GOAL INTO POSITIVE
/*SpinIntake(-127);
pros::delay(500);
chassis.pid_drive_set(12, 70);
chassis.pid_wait();
chassis.pid_turn_set(-90_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-26_in,40);
chassis.pid_wait();
Clamp.extend();
pros::delay(100);
chassis.pid_turn_set(0_deg,70);
chassis.pid_wait();
chassis.pid_drive_set(26_in,70);
chassis.pid_wait();
chassis.pid_turn_set(28_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(75,90,true);
chassis.pid_wait();
chassis.pid_drive_set(-15_in,70);
chassis.pid_wait();
chassis.pid_turn_set(15_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-37_in,70);
chassis.pid_wait();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(22_in,70);
chassis.pid_wait();
chassis.pid_drive_set(-2_in,40);
chassis.pid_wait();
SpinIntake(-127);
chassis.pid_drive_set(-10_in,70);
chassis.pid_wait();
chassis.pid_turn_set(180_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(60,70);
chassis.pid_wait();
chassis.pid_drive_set(-10_in,70);
chassis.pid_wait();
chassis.pid_turn_set(90_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(22_in,70);
chassis.pid_wait();
chassis.pid_turn_set(-14_deg,TURN_SPEED);
chassis.pid_drive_set(-20,50);
chassis.pid_wait();
Clamp.retract();

// get second goal
chassis.pid_drive_set(10,60);
chassis.pid_wait();
pros::delay(100);
chassis.pid_turn_set(90_deg,TURN_SPEED);
chassis.pid_wait();
pros::delay(100);
chassis.pid_drive_set(10,50);
chassis.pid_wait();

chassis.pid_drive_set(-73,100,true);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-15,40);
chassis.pid_wait();
Clamp.extend();
pros::delay(200);
chassis.pid_turn_set(0_deg,70);
chassis.pid_wait();
chassis.pid_drive_set(26_in,70);
chassis.pid_wait();
chassis.pid_turn_set(-28_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(75,70,true);
chassis.pid_wait();
chassis.pid_drive_set(-15_in,70);
chassis.pid_wait();
chassis.pid_turn_set(-15_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-37_in,70);
chassis.pid_wait();
chassis.pid_turn_set(-90_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(22_in,70);
chassis.pid_wait();
chassis.pid_drive_set(-2_in,40);
chassis.pid_wait();
SpinIntake(-127);
chassis.pid_drive_set(-10_in,70);
chassis.pid_wait();
chassis.pid_turn_set(180_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(60,70);
chassis.pid_wait();
chassis.pid_drive_set(-10_in,70);
chassis.pid_wait();
chassis.pid_turn_set(-90_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(22_in,70);
chassis.pid_wait();
chassis.pid_turn_set(14_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-20,50);
chassis.pid_wait();
Clamp.retract();
chassis.pid_drive_set(10,70);
chassis.pid_wait();

//Fill 3rd goal
chassis.pid_drive_set(83,90,true);
chassis.pid_wait();
SpinIntake(-100);
chassis.pid_drive_set(15,50);
chassis.pid_wait();
SpinIntake(0);
chassis.pid_turn_set(-90_deg,TURN_SPEED);
chassis.pid_wait();
pros::delay(100);
chassis.pid_drive_set(-45,70);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-8,40);
chassis.pid_wait();
Clamp.extend();
pros::delay(100);
chassis.pid_drive_set(30,70);
chassis.pid_wait();
chassis.pid_turn_set(-135_deg,TURN_SPEED);
chassis.pid_wait();
SpinIntake(-110);
chassis.pid_drive_set(33,70);
chassis.pid_wait();
pros::delay(100);
chassis.pid_turn_set(-225_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(33,70);
chassis.pid_wait();
pros::delay(100);
chassis.pid_turn_set(-305_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(55,70);
chassis.pid_wait();
chassis.pid_turn_set(0_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(25,70);
chassis.pid_wait();
chassis.pid_turn_set(-110_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-30,70);
chassis.pid_wait();
Clamp.retract();
chassis.pid_drive_set(15,70);
chassis.pid_wait();


//PUT FIRST BLUE GOAL IN CORNER

/*lift_auto(0);
chassis.pid_drive_set(10_in,60);
chassis.pid_wait();
SpinIntake(-70);
chassis.pid_drive_set(5_in,60);
chassis.pid_wait();
chassis.pid_turn_set(-3_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(70,70);
chassis.pid_wait_quick_chain();
lift_auto(-90);
chassis.pid_drive_set(20,70);
chassis.pid_wait();
chassis.pid_drive_set(-5,50);
chassis.pid_turn_set(120_deg,TURN_SPEED);
chassis.pid_wait();
lift_auto(-200);
SpinIntake(0);
chassis.pid_drive_set(-30_in,35);
chassis.pid_wait();
Clamp.extend();
pros::delay(100);
chassis.pid_turn_set(90_deg,TURN_SPEED);
chassis.pid_wait();
SpinIntake(-100);
Doinker.extend();
chassis.pid_drive_set(40,60);
chassis.pid_wait();
chassis.pid_turn_set(60,TURN_SPEED);
chassis.pid_wait();
Doinker.retract();
chassis.pid_turn_set(-130_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-30,70);
chassis.pid_wait();
Clamp.retract();
chassis.pid_drive_set(15,60);
chassis.pid_wait();
chassis.pid_drive_set(-30,70);
chassis.pid_wait();
chassis.pid_drive_set(17,60);
chassis.pid_wait();

// grab middle goal and put in corner

chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-50,60);
chassis.pid_wait();
Clamp.extend();
pros::delay(200);
chassis.pid_turn_set(-135_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(30,70);
chassis.pid_wait();
chassis.pid_turn_set(-45_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(80,80);
chassis.pid_wait();
chassis.pid_turn_set(-90_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(27,60);
chassis.pid_wait();
chassis.pid_turn_set(180_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(40,60);
chassis.pid_wait();
chassis.pid_turn_set(90_deg,TURN_SPEED);
chassis.pid_wait();
chassis.pid_drive_set(-25,50);
chassis.pid_wait();
Clamp.retract();*/

}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_drive_set(-24_in,DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-90_deg,TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-3_in, DRIVE_SPEED);
  chassis.pid_wait();

  SpinIntake(127);
   
  chassis.pid_drive_set(9_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-40_in, DRIVE_SPEED);
  chassis.pid_wait();

  Clamp.extend();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
  
  SpinIntake(127);

  chassis.pid_drive_set(30_in, DRIVE_SPEED);
  chassis.pid_wait();


  /*chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();*/
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}


void awpringside(){
  chassis.pid_swing_set(ez::RIGHT_SWING, 15_deg, SWING_SPEED,15);
}


///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .