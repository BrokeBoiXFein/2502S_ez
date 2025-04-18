#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

pros::Motor Intake(-13);
// pros::Motor LB(5);
// pros::Rotation LBRotation(18);

bool EnableLB = true;
//pneumatic
pros::adi::Pneumatics Clamp(8, false);
pros::adi::Pneumatics Doinker(1,false);
pros::adi::Pneumatics Raise(7,false);


// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-18, -20, 19},     // Left Chassis Ports (negative port will reverse it!)
    {9, -8, 10},  // Right Chassis Ports (negative port will reverse it!)

    2,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM


// bool runningLift = true;
// int liftMode = 0;
// void liftTask(){
//   while(1){
//     if(runningLift){
//       LB = 0.01*(liftMode - LBRotation.get_position());
//     }
//     pros::delay(20);
//   }
// }


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  Lift_Task.suspend();
  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(1, 1);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)
  LB.set_encoder_units(pros::MotorEncoderUnits::degrees);
  LB.set_zero_position(0);
  // Set the   drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
      Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
      Auton("Motion Chaining\n\nDrive forward, turn, and come back, but blend everything together :D", motion_chaining),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),

  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  LB.tare_position();
  LBRotation.set_position(36000);
  master.rumble(".");

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  Clamp.retract();
  EnableLB = false;
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */



    
void runIntake() {
if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
		Intake.move(-118);
		
	}
else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
        Intake.move(127);
      
    }
else{
		Intake.brake();
	
		}
}

void Clamping(){
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
        Clamp.extend();
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
        Clamp.retract();
    }
}

void RaiseIntake(){
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)){
        Raise.extend();
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
        Raise.retract();
    }
}

void Doink(){
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)){
        Doinker.extend();
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
        Doinker.retract();
    }
}





bool durgh = false;

  
 int LBPresets(){
  bool Braking = false;
 
  LB.set_brake_mode(pros::MotorBrake::hold);    
    if (master.get_digital(DIGITAL_Y)) {
      Braking = false;
      Lift_Task.resume();
      liftPID.target_set(1000);
      Braking = true;
   
      
      //liftControl(5000);
     
    //  liftControl(-100);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
      Lift_Task.suspend();
      LB.move(127);
      Braking = true;
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
      Lift_Task.suspend();
      LB.move(-127);
      Braking = true;
    } 
    
    else if((Braking = true && master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 0) || (Braking == true && master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1) == 0) || (Braking == true && master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y) == 0) ){
      LB.brake();
    }

    
  
   
  
   // SpinLB(liftPID.compute(LB.get_position()));

    pros::delay(ez::util::DELAY_TIME);
  

  return 1;
}
void opcontrol() {
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;

  chassis.drive_brake_set(driver_preference_brake);

  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X))
        chassis.pid_tuner_toggle();
      
      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
        autonomous();
        chassis.drive_brake_set(driver_preference_brake);
      }

      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    std::cout<< LB.get_position() << std::endl;

    //chassis.opcontrol_tank();  // Tank control
     chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade
    runIntake();
    Clamping();
    //LadyBrown();
    Doink();
    RaiseIntake();
    LBPresets();
    // . . .
    // Put more user control code here!
    // . . .
    printf("%d/n", LBRotation.get_position());
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}