#pragma config(Sensor, in4,    lightSensor,    sensorReflection)
#pragma config(Sensor, dgtl8,  buttonSwitch,   sensorTouch)
#pragma config(Sensor, dgtl9,  sonarSensor,    sensorSONAR_cm)
#pragma config(Motor,  port2,           rightMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                         - Wait for Dark -                                          *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to wait until the lights around it go down to move forward for   *|
|*  1.5 seconds.  There is a two second pause at the beginning of the program.                        *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Lighting conditions change from place to place, so the value '200' may need to be changed   *|
|*        to better suit your environment.                                                            *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor  - Port 2     rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor  - Port 3     leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Analog - Port 8     lightSensor         VEX Light Sensor      Mounted facing up                 *|
\*-----------------------------------------------------------------------------------------------4246-*/
int power = 63;

//+++++++++++++++++++++++++++++++++++++++++++++| VOID |+++++++++++++++++++++++++++++++++++++++++++++++

void driveForward()
{
	while(SensorValue(lightSensor) < 300 && (SensorValue(sonarSensor) > 30 || SensorValue(sonarSensor) == -1)) // While the ambient lightSensor reads a value less than 200
		{
			motor[rightMotor] = power;			          // Motor on port2 is run at half (63) power forward
			motor[leftMotor]  = power;			          // Motor on port3 is run at half (63) power forward
			if (SensorValue(buttonSwitch) == 1) {
				StopAllTasks();
			};
		}
}

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	wait1Msec(1000);
	while(SensorValue(buttonSwitch) == 0) {
		driveForward();

		motor[rightMotor] = -power;
		motor[leftMotor]= power;
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
