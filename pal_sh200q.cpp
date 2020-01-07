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

#define SH200Q_IMPL
#include "pal_sh200q.h"
#include "base.h"
#include "pal_i2c.h"


#define ENABLE_MPU6886_I2C_DEBUG 0


int SH200Q_i2c_send_data(uint8_t cmd, size_t send_buf_len, const uint8_t *send_buf)
{
	return i2c_send_multiple_data(SH200Q_I2C_BUS, SH200Q_I2C_SLA, cmd, send_buf, send_buf_len);
}

int SH200Q_i2c_send_byte(uint8_t cmd, const uint8_t sendData)
{
	return i2c_send_byte(SH200Q_I2C_BUS, SH200Q_I2C_SLA, cmd, sendData);
}

int SH200Q_i2c_recv_data(uint8_t cmd, size_t receive_buf_len, uint8_t *receive_buf)
{
	return i2c_recv_multiple_data(SH200Q_I2C_BUS, SH200Q_I2C_SLA, cmd, receive_buf, receive_buf_len);
}

uint8_t SH200Q_i2c_recv_byte(uint8_t cmd)
{
	return i2c_recv_byte(SH200Q_I2C_BUS, SH200Q_I2C_SLA, cmd);
}


int SH200Q_Init(void)
{
	// setup GPIOs for I2C & the I2C
	i2c_initialize(SH200Q_I2C_BUS, SH200Q_I2C_PIN_SDA, SH200Q_I2C_PIN_SCL, 400000);

	if( SH200Q_i2c_recv_byte(SH200Q_CHIPID) != SH200Q_CHIPID_VALUE ){
		DEBUG_PRINTF("This device doesn't have SH200Q.\r\n");
		// Chip ID's register will return 0x18. Otherwise, it's not SH200Q.
		i2c_finalize(SH200Q_I2C_BUS);
		return -1;
	}
	DEBUG_PRINTLN("SH200Q detected");

	delay(1);

	// Reset
	uint8_t tmpData = SH200Q_i2c_recv_byte(SH200I_RESET);
	SH200Q_i2c_send_byte(SH200I_RESET, tmpData | SH200I_RESET_OR_MASK);
	delay(1);
	SH200Q_i2c_send_byte(SH200I_RESET, tmpData & SH200I_RESET_AND_MASK);
	delay(10);

	// Reset ADC
	tmpData = SH200Q_i2c_recv_byte(SH200I_ADC_RESET);
	SH200Q_i2c_send_byte(SH200I_ADC_RESET, tmpData | SH200I_ADC_OR_MASK);
	delay(1);
	SH200Q_i2c_send_byte(SH200I_ADC_RESET, tmpData & SH200I_ADC_AND_MASK);
	delay(1);

	// clear FIFO status
	tmpData = SH200Q_i2c_recv_byte(SH200Q_ACCEL_FIFO_STATUS);
	tmpData = SH200Q_i2c_recv_byte(SH200Q_GYRO_FIFO_STATUS);

	// clear INT status
	tmpData = SH200Q_i2c_recv_byte(SH200Q_INT_STATUS);

	// setup accelerometer
	// config Accelerometer as 8G
	SH200Q_i2c_send_byte(SH200Q_ACCEL_DATA_FMT, SH200Q_ACCEL_DATA_FMT_8G);
	SH200Q_i2c_send_byte(SH200Q_ACCEL_CONFIG, SH200Q_ACCEL_CONFIG_VAL);

	// setup gyro
	// config Gyro DPS as 2000DPS
	SH200Q_i2c_send_byte(SH200Q_GYRO_CONFIG, SH200Q_GYRO_CONFIG_2000DPSG);
	SH200Q_i2c_send_byte(SH200Q_GYRO_CONFIG2, SH200Q_GYRO_CONFIG2_VAL);

	// Disable interrupt
	SH200Q_i2c_send_byte(SH200Q_INT_ENABLE, 0);

	return 0;
}

void SH200Q_getGyroData(float* gyroX, float* gyroY, float* gyroZ)
{
	uint8_t buf[6] = {0,0,0,0,0,0};
	SH200Q_i2c_recv_data(SH200Q_GYRO_X_OUT_L, 6, buf);

	*gyroX=(float)(((int16_t)buf[1]<<8) | buf[0]) * g_gyroK;
	*gyroY=(float)(((int16_t)buf[3]<<8) | buf[2]) * g_gyroK;
	*gyroZ=(float)(((int16_t)buf[5]<<8) | buf[4]) * g_gyroK;
}

void SH200Q_getAccelData(float* accelX, float* accelY, float* accelZ)
{
	uint8_t buf[6] = {0,0,0,0,0,0};
	SH200Q_i2c_recv_data(SH200Q_ACCEL_X_OUT_L, 6, buf);

	*accelX=(float)(((int16_t)buf[1]<<8) | buf[0]) * g_accelK;
	*accelY=(float)(((int16_t)buf[3]<<8) | buf[2]) * g_accelK;
	*accelZ=(float)(((int16_t)buf[5]<<8) | buf[4]) * g_accelK;
}

void SH200Q_getAhrsData(float* pitch, float* roll, float* yaw)
{

}
