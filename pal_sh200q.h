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

#ifndef __PAL_SENSOR_SH200Q_H__
#define __PAL_SENSOR_SH200Q_H__

#include "base.h"
#include "pal_i2c.h"

int SH200Q_Init(void);
void SH200Q_getGyroData(float* gyroX, float* gyroY, float* gyroZ);
void SH200Q_getAccelData(float* accelX, float* accelY, float* accelZ);
void SH200Q_getAhrsData(float* pitch, float* roll, float* yaw);

// board config
#define SH200Q_I2C_BUS		I2C_BUS_CHANNEL_1    // iic1
#define SH200Q_I2C_PIN_SCL	22
#define SH200Q_I2C_PIN_SDA	21
#define SH200Q_I2C_SLA		0x6C

#ifdef SH200Q_IMPL
static float g_accelK = 8.0f/32768.0f;
static float g_gyroK = 2000.0f/32768.0f;
int SH200Q_i2c_send_data(uint8_t cmd, size_t send_buf_len, const uint8_t *send_buf);
int SH200Q_i2c_send_byte(uint8_t cmd, const uint8_t sendData);

int SH200Q_i2c_recv_data(uint8_t cmd, size_t receive_buf_len, uint8_t *receive_buf);
uint8_t SH200Q_i2c_recv_byte(uint8_t cmd);

#define BIT0	(0x01)
#define BIT1	(0x01<<1)
#define BIT2	(0x01<<2)
#define BIT3	(0x01<<3)
#define BIT4	(0x01<<4)
#define BIT5	(0x01<<5)
#define BIT6	(0x01<<6)
#define BIT7	(0x01<<7)

#define SH200Q_CHIPID            0x30
#define SH200Q_CHIPID_VALUE		 0x18

#define SH200I_RESET			 0x75
#define SH200I_RESET_OR_MASK	 0x80
#define SH200I_RESET_AND_MASK	 0x7F

#define SH200I_ADC_RESET		 0xC2
#define SH200I_ADC_OR_MASK		 0x04
#define SH200I_ADC_AND_MASK		 0xFB

#define SH200Q_ACCEL_X_OUT_L     0x00
#define SH200Q_ACCEL_CONFIG      0x0E
#define SH200Q_ACCEL_CONFIG_VAL  (BIT0 | BIT1 | BIT4)
#define SH200Q_ACCEL_FIFO_STATUS 0x2E
#define SH200Q_ACCEL_DATA_FMT	 0x16
#define SH200Q_ACCEL_DATA_FMT_4G (0)
#define SH200Q_ACCEL_DATA_FMT_8G (BIT0)
#define SH200Q_ACCEL_DATA_FMT_16G (BIT1)

#define SH200Q_GYRO_X_OUT_L      0x06
#define SH200Q_GYRO_FIFO_STATUS  0x2F
#define SH200Q_GYRO_CONFIG2      0x0F
#define SH200Q_GYRO_CONFIG2_VAL  (BIT0 | BIT2)
#define SH200Q_GYRO_CONFIG       0x2B
#define SH200Q_GYRO_CONFIG_125DPS	(BIT2)
#define SH200Q_GYRO_CONFIG_250DPS	(BIT1 | BIT0)
#define SH200Q_GYRO_CONFIG_500DPS	(BIT1)
#define SH200Q_GYRO_CONFIG_10000DPS	(BIT0)
#define SH200Q_GYRO_CONFIG_2000DPSG	(0)

#define SH200Q_INT_ENABLE		 0x14
#define SH200Q_INT_STATUS		 0x2C
#endif // SH200Q_IMPL

#endif // __PAL_SENSOR_SH200Q_H__
