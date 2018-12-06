#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port2,           leftMotor,    tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,     tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                              - Forward for Distance with Encoders -                                *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program instructs the robot to move forward for 5 rotations of the left shaft encoder.       *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" model, but may not be needed for all robot configurations.                      *|
|*    2)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Shaft Encoder     Right side                        *|
|*    Digital - Port 3,4  leftEncoder         VEX Shaft Encoder     Left side                         *|
\*----------------------------------------------------------------------------------------------------*/
int power = 63;
// Reiknar lengd halfum metra
float radius = 5.9;
float ummal = 2 * PI * radius;
float length = 360 * (50 / ummal);
int counter = 1;


void drive(int length, int counter, int direction){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	while(abs(SensorValue[leftEncoder]) < length * counter)
	{
		motor[rightMotor] = power * direction;
		motor[leftMotor]  = power * direction;
	}
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}

//const int BASELENGTH = 573;
//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
  wait1Msec(2000);  // 2 Second Delay

  //Clear Encoders
  for(; counter <= 5; counter++){
	  drive(length, counter, 1);
	  wait1Msec(1000);
	  drive(length, counter, -1);
	  wait1Msec(1000);
	}
  /*while(abs(SensorValue[leftEncoder]) < BASELENGTH)  // While less than 1,592356687898089 rotations on the leftEncoder...
  {
    //...Move Forward
  	writeDebugStream("eithvad %d", leftEncoder);
  	writeDebugStream("eithvad %d", rightEncoder);
    motor[rightMotor] = 127;
    motor[leftMotor] = powerLeft;
  }*/

}