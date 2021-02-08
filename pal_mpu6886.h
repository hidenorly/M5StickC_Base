/* 
 Copyright (C) 2019, 2020, 2021 hidenorly

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

#ifndef __PAL_SENSOR_MPU6886_H__
#define __PAL_SENSOR_MPU6886_H__

#include "base.h"
#include "pal_i2c.h"

int MPU6886_Init(void);
void MPU6886_getGyroData(float* gyroX, float* gyroY, float* gyroZ);
void MPU6886_getAccelData(float* accelX, float* accelY, float* accelZ);
void MPU6886_getAhrsData(float* pitch, float* roll, float* yaw);
void MPU6886_getTemperature(float* temp);

// board config
#define MPU6886_I2C_BUS		I2C_BUS_CHANNEL_1    // iic0
#define MPU6886_I2C_PIN_SCL	22
#define MPU6886_I2C_PIN_SDA	21
#define MPU6886_I2C_SLA		0x68

#ifdef MPU6886_IMPL
static float g_accelK = 8.0f/32768.0f;
static float g_gyroK = 2000.0f/32768.0f;
int MPU6886_i2c_send_data(uint8_t cmd, size_t send_buf_len, const uint8_t *send_buf);
int MPU6886_i2c_send_byte(uint8_t cmd, const uint8_t sendData);

int MPU6886_i2c_recv_data(uint8_t cmd, size_t receive_buf_len, uint8_t *receive_buf);
uint8_t MPU6886_i2c_recv_byte(uint8_t cmd);

#define BIT0	(0x01)
#define BIT1	(0x01<<1)
#define BIT2	(0x01<<2)
#define BIT3	(0x01<<3)
#define BIT4	(0x01<<4)
#define BIT5	(0x01<<5)
#define BIT6	(0x01<<6)
#define BIT7	(0x01<<7)

#define MPU6886_WHOAMI            0x75
#define MPU6886_WHOAMI_VALUE	  0x19
#define MPU6886_PWR_MGMT_1        0x6B
#define MPU6886_PWR_MGMT_1_RESET  BIT7
#define MPU6886_PWR_MGMT_2        0x6C

#define MPU6886_ACCEL_CONFIG      0x1C
#define MPU6886_ACCEL_CONFIG_2G   (0)
#define MPU6886_ACCEL_CONFIG_4G   (BIT3)
#define MPU6886_ACCEL_CONFIG_8G   (BIT4)
#define MPU6886_ACCEL_CONFIG_16G  (BIT3 | BIT4)
#define MPU6886_ACCEL_CONFIG2     0x1D
#define MPU6886_ACCEL_XOUT_H      0x3B

#define MPU6886_GYRO_CONFIG       0x1B
#define MPU6886_GYRO_CONFIG_250DPS		(0)
#define MPU6886_GYRO_CONFIG_500DPS		(BIT3)
#define MPU6886_GYRO_CONFIG_10000DPS	(BIT4)
#define MPU6886_GYRO_CONFIG_2000DPSG	(BIT3 | BIT4)
#define MPU6886_GYRO_XOUT_H       0x43

#define MPU6886_CONFIG            0x1A
#define MPU6886_SMPLRT_DIV        0x19
#define MPU6886_INT_ENABLE        0x38
#define MPU6886_INT_ENABLE_VAL    0x01
#define MPU6886_USER_CTRL         0x6A
#define MPU6886_FIFO_EN           0x23
#define MPU6886_INT_PIN_CFG       0x37
#define MPU6886_INT_PIN_CFG_VAL	  0x20

#define MPU6886_TEMP_OUT_H        0x41
#define MPU6886_TEMP_OUT_L        0x42
#endif // MPU6886_IMPL

#endif // __PAL_SENSOR_MPU6886_H__
