#pragma config(Sensor, in4,    lightSensor,    sensorReflection)
#pragma config(Sensor, in5,    lineFollowerRIGHT, sensorLineFollower)
#pragma config(Sensor, in6,    lineFollowerCENTER, sensorLineFollower)
#pragma config(Sensor, in7,    lineFollowerLEFT, sensorLineFollower)
#pragma config(Sensor, in8,    armPotent,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  leverSwitch,    sensorTouch)
#pragma config(Sensor, dgtl8,  buttonSwitch,   sensorTouch)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port6,           clawMotor,     tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------------*\
|*                                      - Movement by Rotation -                                      *|
|*                                      ROBOTC on VEX 2.0 CORTEX                                      *|
|*                                                                                                    *|
|*  This program uses the Shaft Encoders to move forward for a certain distance.                      *|
|*  There is a two second pause at the beginning of the program.                                      *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Reversing 'rightMotor' (port 2) in the "Motors and Sensors Setup" is needed with the        *|
|*        "Squarebot" mode, but may not be needed for all robot configurations.                       *|
|*    2)  Changing the value of 'distance' will change how far your robot will travel.                *|
|*        !! 360 is equal to one full rotation of the axel !!                                         *|
|*    3)  Whichever encoder is being used for feedback should be cleared just before it starts        *|
|*        counting by using the "SensorValue(encoder) = 0;".  This helps ensure consistancy.          *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]          [Name]              [Type]                [Description]                     *|
|*    Motor   - Port 2    rightMotor          VEX 3-wire module     Right side motor                  *|
|*    Motor   - Port 3    leftMotor           VEX 3-wire module     Left side motor                   *|
|*    Digital - Port 1,2  rightEncoder        VEX Quadrature enc.   Right side encoder                *|
|*    Digital - Port 3,4  leftEncoder         VEX Quadrature enc.   Left side encoder                 *|
\*-----------------------------------------------------------------------------------------------4246-*/
// Declare Global Variables
//const float circle = 360;

int power = 50;

float radius = 5.9;
float ummal = 2 * PI * radius;
int counter = 1;

int threshold = 1500;      /* found by taking a reading on both DARK and LIGHT    */
  										     /* surfaces, adding them together, then dividing by 2. */

//const float eX = 4.1;
const float eX = 3;

void lineFollow () {
	    // RIGHT sensor sees dark:
    if(SensorValue(lineFollowerRIGHT) > threshold)
    {
      // counter-steer right:
      motor[leftMotor]  = power;
      motor[rightMotor] = 0;
    }
    // CENTER sensor sees dark:
    if(SensorValue(lineFollowerCENTER) > threshold)
    {
      // go straight
      motor[leftMotor]  = power;
      motor[rightMotor] = power;
    }
    // LEFT sensor sees dark:
    if(SensorValue(lineFollowerLEFT) > threshold)
    {
      // counter-steer left:
      motor[leftMotor]  = 0;
      motor[rightMotor] = power;
    }
  }

void forward(int dist){
	SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
	float length = 360 * (dist / ummal);
	wait1Msec(500);

  //wait1Msec(1000);

	while(abs(SensorValue[leftEncoder]) < length && SensorValue[rightEncoder] > (-length))
	{
		lineFollow();
	}
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;

	SensorValue[rightEncoder] = 0;
	SensorValue[leftEncoder] = 0;
}

void turnLeft (float rotate) {
		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;
		int turn = -1 * (eX * rotate);
		wait1Msec(500);

		//wait1Msec(1000);
		motor[rightMotor] = power;         // Run the right motor bakward at half speed
	  motor[leftMotor]  = -power;        // Run the left motor forward at half speed
	  wait1Msec(500);

		// While the encoders have not yet met their goal: (left is compared negativly since it will in reverse)
	  while((SensorValue[rightEncoder] > turn && SensorValue[leftEncoder] > turn) && SensorValue[lineFollowerCENTER] < threshold)
	  {
	    motor[rightMotor] = power;         // Run the right motor forward at half speed
	    motor[leftMotor]  = -power;        // Run the left motor backward at half speed
	  }
	  motor[rightMotor] = 0;            /* Stop both motors!  This is important so that each function*/
	  motor[leftMotor]  = 0;            /* can act independantly as a "chunk" of code, without any loose ends.*/

		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;
}

void turnRight (float rotate) {
		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;
		int turn = (eX * rotate);
		wait1Msec(500);

		//wait1Msec(1000);
	    motor[rightMotor] = -power;         // Run the right motor bakward at half speed
	    motor[leftMotor]  = power;        // Run the left motor forward at half speed
	    wait1Msec(500);

	  while((SensorValue[leftEncoder] < turn && SensorValue[rightEncoder] < turn) && (SensorValue[lineFollowerCENTER] < threshold && SensorValue[lineFollowerLEFT] < threshold))
	  {
	    motor[rightMotor] = -power;         // Run the right motor bakward at half speed
	    motor[leftMotor]  = power;        // Run the left motor forward at half speed
	  }
	  motor[rightMotor] = 0;            /* Stop both motors!  This is important so that each function*/
	  motor[leftMotor]  = 0;            /* can act independantly as a "chunk" of code, without any loose ends.*/

		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;
}

void turnForLine (float rotate, int side) {
		SensorValue[rightEncoder] = 0;
		SensorValue[leftEncoder] = 0;
		float turns = (eX * rotate);
		if (side == 1){
			while(SensorValue[leftEncoder] > -turns && SensorValue[rightEncoder] > -turns/* && SensorValue(lineFollowerCENTER) < threshold*/)
			{
			  motor[rightMotor] = power  * side;         // Run the right motor bakward at half speed
			  motor[leftMotor]  = -power * side;        // Run the left motor forward at half speed
			}
		}
		else {
			while(SensorValue[leftEncoder] < turns && SensorValue[rightEncoder] < turns && (SensorValue[lineFollowerCENTER] < threshold && SensorValue[lineFollowerRIGHT] < threshold))
			{
			  motor[rightMotor] = power  * side;         // Run the right motor bakward at half speed
			  motor[leftMotor]  = -power * side;        // Run the left motor forward at half speed
			}
		}

	  motor[rightMotor] = 0;            /* Stop both motors!  This is important so that each function          */
	  motor[leftMotor]  = 0;            /* can act independantly as a "chunk" of code, without any loose ends. */
}

void liftArm () {

}
/*
void commands() {
	forward(200);
	wait1Msec(50);
	turnForLine(90, 1);
	wait1Msec(50);
	forward(50);
	wait1Msec(50);
	turn(180, 1);
	wait1Msec(50);
	forward(50);
	wait1Msec(50);
	turnForLine(20, -1);
	wait1Msec(50);
	forward(150);
	wait1Msec(50);
	turnForLine(20, 1);
	wait1Msec(50);
	forward(50);
	wait1Msec(50);
	turn(180, 1);
	wait1Msec(50);
}*/

	//int mainLineList[];
	//int secondaryMainLineList[];
	int turnList[3] = {-1, -1, 1};
	int SecondaryTurnList[3] = {-1, 1, -1};
	int SecondSecondaryTurnList[3] = {1, -1 ,1};
	int SecondarySecondSecondaryTurnList[3] = {1, 1, -1};

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main()
{
	forward(205);
	wait1Msec(100);
  turnRight(360);
  wait1Msec(100);
  forward(55);
  wait1Msec(100);
  turnRight(180);
  wait1Msec(100);
  forward(55);
  wait1Msec(100);
  turnLeft(90);
  wait1Msec(100);
  forward(155);
  wait1Msec(100);
  turnRight(90);
  wait1Msec(100);
  forward(55);


		/* --------------------------------------------------- */
		/*for(int i = 0; i < 4; i++) {
				forward(50);
				turn(20, turnList[i]);
				while(SensorValue(lineFollowerCENTER) < threshold) {
					turn(1, turnList[i]);
				}
				forward(50);
				// TAKA UPP GLASS
				turn(180, 1);
				forward(50);
				turn(20, SecondaryTurnList[i]);
				while(SensorValue(lineFollowerCENTER) < threshold) {
					turn(1, SecondaryTurnList[i]);
				}
				forward(150);
				turn(20, SecondSecondaryTurnList[i]);
				while(SensorValue(lineFollowerCENTER) < threshold) {
					turn(1, 1);
				}
				forward(50);
				// SETJA GLAS I KORFU
				turn(180, 1);
				}

	  /*while (true) {
	  	for(; counter <= 4; counter++){
	  	//wait1Msec(1000);
				forward(200);
				turn(20);
				while(SensorValue(lineFollowerCENTER) < threshold) {
				turn(1, turnList[counter])
				}

		  if (counter == 1) {
		  	forward(200);
		  	wait1Msec(1000);
		  	//turnLeft(180);
		  	while(SensorValue(lineFollowerCENTER) < threshold && SensorValue(lineFollowerLEFT) < threshold) {
		  	turnRight(1);
		  	}
		  	turnRight(20);
		  	wait1Msec(1000);
		  }
		  else if ((counter <= 3 && counter > 1) || (counter == 7)) {
		  	turnRight(20);
		  	while(SensorValue(lineFollowerCENTER) < threshold) {
		  	turnRight(1);
		  }
		  	wait1Msec(1000);
		  }
		  else if (counter == 4) {
		  		turnRight(1);
		  	wait1Msec(1000);
		  }
		  //wait1Msec(1000);
		}*/

	  motor[rightMotor] = 0;            /* Stop the motors once desired */
	  motor[leftMotor]  = 0;            /* distance has been reached.   */
	  if (SensorValue(buttonSwitch) == 1  || vexRT[Btn8D] == 1 || SensorValue(leverSwitch) == 1){
	  	StopAllTasks();
	  }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
