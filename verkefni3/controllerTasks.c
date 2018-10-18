int power = 127;
int time = 1000;
int counter = 1;

void drive_forward(int time, int counter){
	motor[rightMotor] = power;
	motor[leftMotor]  = power;
	wait1Msec(time * counter);
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
	wait1Msec(1000);
}

void drive_backward(int time, int counter){
	motor[rightMotor] = -power;
	motor[leftMotor]  = -power;
	wait1Msec(time * counter);
	motor[rightMotor] = 0;
	motor[leftMotor]  = 0;
	wait1Msec(1000);
}

task calledTask()
{
		for(; counter < 5; counter++){
			drive_forward(time, counter);
			drive_backward(time, counter);
		}
}
