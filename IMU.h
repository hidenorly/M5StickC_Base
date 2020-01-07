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

#ifndef __PAL_SENSOR_IMU_H__
#define __PAL_SENSOR_IMU_H__

#include "base.h"

enum IMU_ASCALE {
	AFS_2G = 0,
	AFS_4G,
	AFS_8G,
	AFS_16G
};

enum IMU_GSCALE {
	GFS_250DPS = 0,
	GFS_500DPS,
	GFS_1000DPS,
	GFS_2000DPS
};

int IMU_Init(void);
void IMU_getGyroData(float* gyroX, float* gyroY, float* gyroZ);
void IMU_getAccelData(float* accelX, float* accelY, float* accelZ);
void IMU_getAhrsData(float* pitch, float* roll, float* yaw);

#endif // __PAL_SENSOR_MPU6886_H__
