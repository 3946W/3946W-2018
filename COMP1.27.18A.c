#pragma config(Sensor, in1,    secondLift,     sensorPotentiometer)
#pragma config(Sensor, in2,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in4,    Gyro,           sensorGyro)
#pragma config(Sensor, in5,    mobileGoalDetector, sensorReflection)
#pragma config(Sensor, dgtl1,  lDrive,         sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rDrive,         sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  coneDetector,   sensorSONAR_cm)
#pragma config(Motor,  port1,           leftMobileIntake, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rightFourBar,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           topLeftLift,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           bottomLeftLift, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           bottomRightLift, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           topRightLift,  tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftFourBar,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightMobileIntake, tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//1.27.18A is a WORKING FILE for testing
#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#define fourBarUp 1300;
#define fourBarDown 2200;
#define liftUp 800;
<<<<<<< HEAD:COMP1.27.18A.c
#define liftDown 2700;//lift is reversed
int secondStageTarget = fourBarUp;
int liftTarget = 1800;
int taskWait = 25;
=======
#define liftDown 2700;
int secondStageTarget = 2200;
int liftTarget = 2700;
int taskWait = 10;
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
bool liftPidEnabled = true;
bool mobileGoalToggleUp = false;
void liftMotors(int power){
	motor[topRightLift] = power;
	motor[bottomRightLift] = power;
	motor[topLeftLift] = power;
	motor[bottomLeftLift] = power;
}
void pre_auton()
{
	bStopTasksBetweenModes = true;
}
task secondLiftPID(){
	float kp = 0.1;
	float error;
	while(true){
		error = secondStageTarget - SensorValue[secondLift];
<<<<<<< HEAD:COMP1.27.18A.c

		if(motorVal < -20){
			motorVal = -20;
			}else if(motorVal > 127){
			motorVal = 127;
		}

		if(abs(error) < 300){//only use integral when nearing target
			integral = integral + error;
			}else{
			integral = 0;
		}

		motorVal = (error * kp) + (integral * ki);

		motor[rightFourBar] = motorVal;
		motor[leftFourBar] = motorVal;
		if(vexRT[Btn6UXmtr2]){
			while(vexRT[Btn6UXmtr2]){}
			isUp = !isUp;
		}//toggle button
		if(isUp){
			secondStageTarget = fourBarUp;
			}else{
			secondStageTarget = fourBarDown;
		}
=======
		motor[rightFourBar] = ((error * kp) * -1);
		motor[leftFourBar] = ((error * kp) * -1);
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
	}
	wait1Msec(taskWait);
}
task peakDetect(){
	while(true){
<<<<<<< HEAD:COMP1.27.18A.c
		if(vexRT[Btn5UXmtr2]){
			int min = SensorValue[liftPot];
			clearTimer(T3);
			while(time1(T3) < 250){
				if(SensorValue[liftPot] < min){//min is actually increasing height since lift values are reversed
=======
		if(vexRT[Btn5U]){
			clearTimer(T3);
			int min = SensorValue[liftPot];
			while(time1(T3) < 2000){
				if(SensorValue[liftPot] < min){
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
					min = SensorValue[liftPot];
					liftTarget = min;
				}
			}
		}
	}
}
task liftPID(){
	float kp = 0.05;
	float error;
	while(true){
		if(vexRT[Btn5U]){
			while(vexRT[Btn5U]){
				liftMotors(127);
			}
		} else if(vexRT[Btn5D]) {
				while(vexRT[Btn5D]){
					liftMotors(-60);
				}
				liftTarget = SensorValue[liftPot];
			} else {
			error = liftTarget - SensorValue[liftPot];
			liftMotors(error * kp * -1);
			wait1Msec(taskWait);
		}
	}
}
task autonomousMultitask(){
	while(true){
		if(mobileGoalToggleUp){
			motor[rightMobileIntake]=-127;
			motor[leftMobileIntake]=-127;
			wait1Msec(1000);
			motor[rightMobileIntake]=0;
			motor[leftMobileIntake]=0;
			mobileGoalToggleUp = false;
		}
	}
}
void fwdTicks(int target, int mgTarget){//mgTarget defines the absolute value of the ticks where the mobile goal will lift up
	float kp = 0.8;
	float error = 6;
	int motorPower;
	int MaxMotorValue = 80;
	SensorValue[lDrive] = 0;
	SensorValue[rDrive] = 0;
	clearTimer(T1);
	clearTimer(T2);
	while(time1[T2] < 500 && time1[T1] < 3000){//will stop running if value has been within 5 ticks of target for .5 sec or it has been 3 sec since began
		error = target - ((SensorValue[lDrive] + SensorValue[rDrive]) / 2);
		motorPower = error * kp;
<<<<<<< HEAD:COMP1.27.18A.c
		if(abs(error) < mgTarget){//will bring mobile goal up once defined value ia passed
=======
		if(error < mgTarget){
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
			mobileGoalToggleUp = true;
		}
		if(abs(error) > 5){
			clearTimer(T2);
		}
		if(motorPower > MaxMotorValue){
			motorPower = MaxMotorValue;
		}
		else if(motorPower < (MaxMotorValue * -1)){
			motorPower = MaxMotorValue * -1;
		}
		motor[leftDrive] = motorPower;
		motor[rightDrive] = motorPower;
	}
	playTone(2048, 10);//once task is complete
}
void fwdTicks(int target){
	float kp = 0.8;
	float error = 6;
	int motorPower;
	int MaxMotorValue = 80;
	SensorValue[lDrive] = 0;
	SensorValue[rDrive] = 0;
	clearTimer(T1);
	clearTimer(T2);
<<<<<<< HEAD:COMP1.27.18A.c
	while(time1[T2] < 500 && time1[T1] < 2000){
		error = target - ((SensorValue[lDrive] + SensorValue[rDrive]) / 2);
		motorPower = error * kp;
		if(abs(error) > 5){
			clearTimer(T2);
		}
		if(motorPower > MaxMotorValue){
			motorPower = MaxMotorValue;
		}
		else if(motorPower < (MaxMotorValue * -1)){
			motorPower = MaxMotorValue * -1;
		}
		motor[leftDrive] = motorPower;
		motor[rightDrive] = motorPower;
	}
	playTone(2048, 10);
}
void fwdTicksSlow(int target){
	float kp = 0.8;
	float error = 6;
	int motorPower;
	int MaxMotorValue = 50;
	SensorValue[lDrive] = 0;
	SensorValue[rDrive] = 0;
	clearTimer(T1);
	clearTimer(T2);
=======
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
	while(time1[T2] < 500 && time1[T1] < 3000){
		error = target - ((SensorValue[lDrive] + SensorValue[rDrive]) / 2);
		motorPower = error * kp;
		if(abs(error) > 5){
			clearTimer(T2);
		}
<<<<<<< HEAD:COMP1.27.18A.c
		if(abs(error) < 300){
			MaxMotorValue = 20;//slows as reaches mobile goal
		}
=======
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
		if(motorPower > MaxMotorValue){
			motorPower = MaxMotorValue;
		}
		else if(motorPower < (MaxMotorValue * -1)){
			motorPower = MaxMotorValue * -1;
		}
		motor[leftDrive] = motorPower;
		motor[rightDrive] = motorPower;
	}
	playTone(2048, 10);
}
<<<<<<< HEAD:COMP1.27.18A.c
//void fwdTicksFast(){//to get over bar between zones
//		float kp = 0.8;
//	float error = 6;
//	int motorPower;       need to determine how many ticks it takes to get over bar
//	int MaxMotorValue = 127;
//	SensorValue[lDrive] = 0;
//	SensorValue[rDrive] = 0;
//	clearTimer(T1);
//	clearTimer(T2);
//	while(time1[T2] < 500 && time1[T1] < 2000){
//		//error = target - ((SensorValue[lDrive] + SensorValue[rDrive]) / 2);
//		motorPower = error * kp;
//		if(abs(error) > 5){
//			clearTimer(T2);
//		}
//		if(abs(error) < 300){
//			MaxMotorValue = 20;
//		}
//		if(motorPower > MaxMotorValue){
//			motorPower = MaxMotorValue;
//		}
//		else if(motorPower < (MaxMotorValue * -1)){
//			motorPower = MaxMotorValue * -1;
//		}
//		motor[leftDrive] = motorPower;
//		motor[rightDrive] = motorPower;
//	}
//	playTone(2048, 10);

//}
=======
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
void swingRight(int target){
	SensorValue[rDrive] = 0;
	while(((SensorValue[rDrive]) / 2) < target){
		motor[rightDrive] = 100;
	}
	motor[rightDrive] = -60;
	wait1Msec(50);
	motor[rightDrive] = 0;
	playTone(2048, 10);
}
void swingLeft(int target){
	SensorValue[lDrive] = 0;
	while(((SensorValue[lDrive]) / 2) < target){
		motor[leftDrive] = 100;
	}
	motor[leftDrive] = -60;
	wait1Msec(50);
	motor[leftDrive] = 0;
	playTone(2048, 10);
}
void gyroTurn(float target){
	target = target * 10;
	SensorValue[Gyro] = 0;
	int error = target - SensorValue[Gyro];
	float kp = 0.8;
	clearTimer(T1);
	clearTimer(T2);
	while((time1[T1] <= 1000) && (time1[T2] <= 5000)){
		error = target - SensorValue[Gyro];
		if(abs(error) >= 5){
			clearTimer(T1);
		}
<<<<<<< HEAD:COMP1.27.18A.c

		motorVal = error * kp;

		if(motorVal > MaxMotorValue){
			motorVal = MaxMotorValue;
		}
		else if(motorVal < (MaxMotorValue * -1)){
			motorVal = MaxMotorValue * -1;
		}

		motor[leftDrive] = motorVal * -1;//input positive target to right and neg to go left
		motor[rightDrive] = motorVal;
=======
		motor[leftDrive] = error * kp * -1;
		motor[rightDrive] = error * kp;
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
	}
	motor[leftDrive] = 0;
	motor[rightDrive] = 0;
	playTone(2048, 10);
}
void mobileGoalUp(){
	motor[rightMobileIntake]=-127;
	motor[leftMobileIntake]=-127;
	wait1Msec(1000);
	motor[rightMobileIntake]=0;
	motor[leftMobileIntake]=0;
}
void mobileGoalDown(){
	motor[rightMobileIntake]=127;
	motor[leftMobileIntake]=127;
	wait1Msec(1000);
	motor[rightMobileIntake]=20;
	motor[leftMobileIntake]=20;
}
int lastGoodValue;
int cleanUltrasonic(int input){
	if(input <= 0){
		return lastGoodValue;
	}
	else{
		lastGoodValue = input;
		return input;
	}
}
void programmingSkills(){
	startTask(autonomousMultitask);
	startTask(liftPID);
	liftTarget = 2700;
	fwdTicks(800);//first forward
	mobileGoalDown();
	fwdTicks(700,100);//mobile goal picked up
	fwdTicks(-1200);
	gyroTurn(100.0);
	fwdTicks(500);
	gyroTurn(90.0);
	fwdTicks(1150);//goes into mobile goal zone
	//mobileGoalDown();
	fwdTicks(-1150, -200);




	//old code
	//fwdTicks(700);
	//mobileGoalDown();
	//fwdTicks(650);
	//mobileGoalUp();
	//fwdTicks(-1100);
	//wait1Msec(500);
	//gyroTurn(100.0);
	//wait1Msec(250);
	//fwdTicks(350);
	//wait1Msec(250);
	//gyroTurn(90.0);
	//fwdTicks(1050);//move into 20 point zone
	//mobileGoalDown();
	//wait1Msec(700);
	//mobileGoalUp();
	//fwdTicks(-800);
	//gyroTurn(-90.0);
	//wait1Msec(250);
	//fwdTicks(400);
	//gyroTurn(-90.0);
	//wait1Msec(250);
	//fwdTicks(-350);
	//wait1Msec(250);
	//fwdTicks(700);
	//mobileGoalDown();
	//fwdTicks(650);
	//mobileGoalUp();
	//fwdTicks(-1100);
}
task mobileGoalDriver(){
	while(true){
		if(vexRT[Btn6D]){
			clearTimer(T4);
			while(vexRT[Btn6D]){
				if(time1[T4] < 1000){//will run mobile goal down at full speed and then at 5, to prevent motor burnout
					motor[rightMobileIntake]=127;
					motor[leftMobileIntake]=127;
				}
				else{
					motor[rightMobileIntake]=5;
					motor[leftMobileIntake]=5;
				}
			}
			}else if(vexRT[Btn6U]){
			motor[rightMobileIntake]=-127;
			motor[leftMobileIntake]=-127;
<<<<<<< HEAD:COMP1.27.18A.c
			}else if(vexRT[Btn5D]){//can be pressed to slow down mobile goal
			motor[rightMobileIntake]=60;
			motor[leftMobileIntake]=60;
=======
>>>>>>> parent of 2d1192a... pushed again:COMP1.16.18.c
			}else{
			motor[rightMobileIntake]=0;
			motor[leftMobileIntake]=0;
		}
	}
}
task autonomous()
{
//	programmingSkills();
}
task usercontrol()
{
	//startTask(secondLiftPID);
	startTask(liftPID);
	//startTask(peakDetect);
	startTask(mobileGoalDriver);
	secondStageTarget = fourBarUp;

	while (true)
	{
		motor[leftDrive]=vexRT[Ch1] + vexRT[Ch3];//drive control
		motor[rightDrive]=vexRT[Ch3] - vexRT[Ch1];
	}
}
