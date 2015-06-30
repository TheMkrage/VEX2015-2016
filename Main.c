#pragma config(Motor,  port1,           RightFrontDrive, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           RightBackDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LeftFrontDrive, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LeftBackDrive, tmotorVex393_MC29, openLoop)

#pragma systemFile

// Necessary File For Vex Competition
#include "Vex_Competition_Includes.c"

#include "DeclarationsAndDefines.h"

// Subsystems
#include "Drive.c"
#include "Intake.c"
#include "Shooter.c"
#include "Elevator.c"
#include "Lift.c"

#include "LCDTask.c"

#include "Auto.c"

#include "MiscFunctions.c"



// Ran when you turn ON Robot, I opt not to use this
void pre_auton() {

}

// Ran in Auto
task autonomous() {
	// Reset Encoders and then run the begin auto method found in AUTO.c
	resetEn();
	startauton();
	stopDrive();
}

//Ran in Teleop
task usercontrol() {
	// Start up the LCD
	LCDInit();
	startTask( runLCD );
	startTask( buttonTask );

	// Clear Encoders and possibly Gyro
	initSensors();
	resetEn();
	resetGyro();

	//Start the tasks that control each aspect of the robot
	startTask( driveTask );
	startBallTasks();

	while(true) {
		// Toggle for switching modes between climbing and shooting
		if ( isTapped(ButtonP8L) ) {
			shiftModes();
		}
	}
}
