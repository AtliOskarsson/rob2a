#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorServoContinuousRotation, openLoop)
#include "controllerTasks.c"

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                    - Single Joystick Control -                                     *|
|*                                      ROBOTC on VEX 2.0 Cortex                                      *|
|*                                                                                                    *|
|*  This program uses a single joystick, either right or left (this is configurable below) to drive   *|
|*  the robot.                                                                                        *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    2)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Motor - Port 2          rightMotor           VEX Motor           Right motor                    *|
|*    Motor - Port 3          leftMotor            VEX Motor           Left motor                     *|
\*----------------------------------------------------------------------------------------------------*/

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main ()
{

  while(1 == 1)
  {
    motor[leftMotor]  = (vexRT[Ch3] + vexRT[Ch4])/2;  // (y + x)/2
    motor[rightMotor] = (vexRT[Ch3] - vexRT[Ch4])/2;  // (y - x)/2

    motor[armMotor] = (vexRT[Ch2]);
    //motor[armMotor] = (-vexRT[Ch2])/2;

    // Raise, lower or do not move arm
		if(vexRT[Btn6U] == 1)       	//If button 5U is pressed...
		{
			motor[armMotor] = 64;    	//...raise the arm.
		}
		else if(vexRT[Btn6D] == 1)  	//Else, if button 5D is pressed...
		{
			motor[armMotor] = -64;   	//...lower the arm.
		}
		else if(vexRT[Btn5U] == 1) {
			motor[clawMotor] = 64;
		}
		else if(vexRT[Btn5D] == 1) {
			motor[clawMotor] = -64;
		}
		else                      		//Else (neither button is pressed)...
		{
			motor[armMotor] = 0;      	//...stop the arm.
			motor[clawMotor] = 0;
		}

		if(vexRT[Btn8D]) {
				StartTask(calledTask);
				wait10Msec(4000);
		}

		if(vexRT[Btn8U]) {
				motor[leftMotor] = 0; //Stoppar left motor
				motor[rightMotor] = 0; //Stoppar right motor
				motor[armMotor] = 0; //Stoppar arm motor
				motor[clawMotor] = 0; //Stoppar claw motor
				StopTask(calledTask);

				wait10Msec(200);
		}
  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
