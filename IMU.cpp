/* 
 Copyright (C) 2019, 2020 hidenorly

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include "base.h"
#include "pal_mpu6886.h"
#include "pal_sh200q.h"

enum IMU_TYPES
{
	IMU_MPU6886,
	IMU_SH200Q
};

static int IMU_TYPE = IMU_MPU6886;

int IMU_Init(void)
{
	int ret = -1;
	if(!(ret=MPU6886_Init())){
		IMU_TYPE = IMU_MPU6886;
	} else if(!(ret=SH200Q_Init())){
		IMU_TYPE = IMU_SH200Q;
	}

	return ret;
}

void IMU_getGyroData(float* gyroX, float* gyroY, float* gyroZ)
{
	switch(IMU_TYPE){
		case IMU_MPU6886:
			MPU6886_getGyroData(gyroX, gyroY, gyroZ);
			break;
		case IMU_SH200Q:
			SH200Q_getGyroData(gyroX, gyroY, gyroZ);
			break;
		default:;
	}
}

void IMU_getAccelData(float* accelX, float* accelY, float* accelZ)
{
	switch(IMU_TYPE){
		case IMU_MPU6886:
			MPU6886_getAccelData(accelX, accelY, accelZ);
			break;
		case IMU_SH200Q:
			SH200Q_getAccelData(accelX, accelY, accelZ);
			break;
		default:;
	}
}

void IMU_getAhrsData(float* pitch, float* roll, float* yaw)
{
	switch(IMU_TYPE){
		case IMU_MPU6886:
			MPU6886_getAhrsData(pitch, roll, yaw);
			break;
		case IMU_SH200Q:
			SH200Q_getAhrsData(pitch, roll, yaw);
			break;
		default:;
	}
}
