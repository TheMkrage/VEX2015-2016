#pragma config(UART_Usage, UART1, uartUserControl, baudRate115200, IOPins, None, None)
#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    gyro,           sensorNone)
#pragma config(Sensor, in8,    backupBattery,  sensorAnalog)
#pragma config(Sensor, dgtl1,  elevatorEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  elevatorBotLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl4,  rightDriveTrain, sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  leftDriveTrain, sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  elevatorTopLimitSwitch, sensorTouch)
#pragma config(Sensor, dgtl9,  gyroButton,     sensorTouch)
#pragma config(Sensor, dgtl10, encoderButton,  sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           intake,        tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           shooter1,      tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port3,           shooter2,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           shooter3,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           shooter4,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightDrive,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           leftDrive,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           rightDriveExtra, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftDriveExtra, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          elevator2,     tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma systemFile

// Necessary File For Vex Competition
#include "Vex_Competition_Includes.c"

void sendString ( TUARTs uart, char* hello ) {
	for(int i = 0; i < 32; i++) {
		sendChar(uart, hello[i]);
	}
	sendChar(uart, '\r');
	sendChar(uart, '\n');
}

// --- Joystick Functions ---
// Makes the value 0 if it is less than thresh
int threshold( int value, int thresh) {
	if ( abs(value) < thresh) {
		return 0;
	}
	return value;
}

#include "DeclarationsAndDefines.h"
#include "Sensors.c"
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
	writeDebugStreamLine("WHY DOESNT IT WRUN?");
}

// Ran in Auto
task autonomous() {
	// Reset Encoders and then run the begin auto method found in AUTO.c
	resetEn();
	writeDebugStreamLine("AUTO");
	startauton();
	stopDrive();
}

//Ran in Teleop
task usercontrol() {
	nMotorEncoder[shooter1] = 0;
	nMotorEncoder[rightDrive] = 0;
	nMotorEncoder[leftDrive] = 0;
	clearTimer(T2);
	// Start up the LCD
	//LCDInit();
	//startTask( runLCD );
	writeDebugStreamLine("IT STARTED");

	// Clear Encoders and possibly Gyro
	initSensors();
	resetEn();
	writeDebugStreamLine("ABOUT TO RESET GYRO");
	//resetGyro();

	writeDebugStreamLine("I FINISHED");
	//Start the tasks that control each aspect of the robot
	startTask( driveTask );
	startBallTasks();

	writeDebugStreamLine("IT HAS STARTED");

	while(true) {

		if(vexRT[Btn6U]) {
			stopTask(driveTask);
			motor[port8] = vexRT[Ch2Xmtr2];
			motor[port9] = vexRT[Ch2Xmtr2];
		}else {
			startTask(driveTask);
		}

		displayLCDCenteredString(0, "Hello");

		if(SensorValue(gyroButton)) {
			resetGyro();
		}else if(SensorValue(encoderButton)) {
			resetEn();
		}
		// Toggle for switching modes between climbing and shooting
		/*if ( isTapped(ButtonP8L) ) {
		shiftModes();
		}*/
		wait1Msec(250);
	}
}
