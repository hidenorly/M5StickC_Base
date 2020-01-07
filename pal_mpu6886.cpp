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

#define MPU6886_IMPL
#include "pal_mpu6886.h"

#include "pal_i2c.h"

#define ENABLE_MPU6886_I2C_DEBUG 0

int MPU6886_i2c_send_data(uint8_t cmd, size_t send_buf_len, const uint8_t *send_buf)
{
	return i2c_send_multiple_data(MPU6886_I2C_BUS, MPU6886_I2C_SLA, cmd, send_buf, send_buf_len);
}

int MPU6886_i2c_send_byte(uint8_t cmd, const uint8_t sendData)
{
	return i2c_send_byte(MPU6886_I2C_BUS, MPU6886_I2C_SLA, cmd, sendData);
}

int MPU6886_i2c_recv_data(uint8_t cmd, size_t receive_buf_len, uint8_t *receive_buf)
{
	return i2c_recv_multiple_data(MPU6886_I2C_BUS, MPU6886_I2C_SLA, cmd, receive_buf, receive_buf_len);
}

uint8_t MPU6886_i2c_recv_byte(uint8_t cmd)
{
	return i2c_recv_byte(MPU6886_I2C_BUS, MPU6886_I2C_SLA, cmd);
}


int MPU6886_Init(void)
{
	// setup GPIOs for I2C & the I2C
	i2c_initialize(MPU6886_I2C_BUS, MPU6886_I2C_PIN_SDA, MPU6886_I2C_PIN_SCL, 400000);
	delay(1);

	if( MPU6886_i2c_recv_byte(MPU6886_WHOAMI) != MPU6886_WHOAMI_VALUE ){
		i2c_finalize(MPU6886_I2C_BUS);
		DEBUG_PRINT("This device doesn't have MPU6886.\r\n");
		// WHO AM I's register (117) will return 0x19. Otherwise, it's not MPU6886.
		return -1;
	}
	DEBUG_PRINTLN("MPU6886 detected");
	delay(1);

	// Device reset to default
	MPU6886_i2c_send_byte(MPU6886_PWR_MGMT_1, MPU6886_PWR_MGMT_1_RESET);
	delay(10);

	// Device CLKSEL=0 (Internal 20MHz, Enable TEMP sensor, Gyro, Not Sleep)
	MPU6886_i2c_send_byte(MPU6886_PWR_MGMT_1, 0);
	delay(10);

	// Enable X/Y/Z accelerometer, X/Y/Z gyro
	MPU6886_i2c_send_byte(MPU6886_PWR_MGMT_2, 0);
	delay(10);

	// setup accelerometer sensor
	MPU6886_i2c_send_byte(MPU6886_ACCEL_CONFIG, MPU6886_ACCEL_CONFIG_8G);
	delay(1);
	// accelerometer : 3-DB BW 218.1Hz, Noise BW:235Hz, RATE:1KHz
	MPU6886_i2c_send_byte(MPU6886_ACCEL_CONFIG2, 0);
	delay(1);

	// setup gyro sensor
	MPU6886_i2c_send_byte(MPU6886_GYRO_CONFIG, MPU6886_GYRO_CONFIG_2000DPSG);
	delay(1);
	// gyro : Disable FSYNC, Loop FIFO, 3-DB BW 176Hz, Noise BW 177Hz, RATE:1KHz
	MPU6886_i2c_send_byte(MPU6886_CONFIG, 0x01);
	delay(1);

	// Set SAMPLE RATE DIVIDER
	MPU6886_i2c_send_byte(MPU6886_SMPLRT_DIV, 0x05);
	delay(1);

	// DISABLE ALL INTERRUPT from MPU6886
	MPU6886_i2c_send_byte(MPU6886_INT_ENABLE, 0);
	delay(1);

	// Disable FIFO_EN
	MPU6886_i2c_send_byte(MPU6886_USER_CTRL, 0);
	delay(1);

	// Disable each sensor's FIFO_EN
	MPU6886_i2c_send_byte(MPU6886_FIFO_EN, 0);
	delay(1);

	// LATCH_INT_EN=1
	MPU6886_i2c_send_byte(MPU6886_INT_PIN_CFG, MPU6886_INT_PIN_CFG_VAL);
	delay(1);

	// Enable DATA_RDY_INT_EN
	MPU6886_i2c_send_byte(MPU6886_INT_ENABLE, MPU6886_INT_ENABLE_VAL);
	delay(10);

	return 0;
}

void MPU6886_getGyroData(float* gyroX, float* gyroY, float* gyroZ)
{
	uint8_t buf[6] = {0,0,0,0,0,0};
	MPU6886_i2c_recv_data(MPU6886_GYRO_XOUT_H, 6, buf);

	*gyroX=(float)(((int16_t)buf[0]<<8) | buf[1]) * g_gyroK;
	*gyroY=(float)(((int16_t)buf[2]<<8) | buf[3]) * g_gyroK;
	*gyroZ=(float)(((int16_t)buf[4]<<8) | buf[5]) * g_gyroK;
}

void MPU6886_getAccelData(float* accelX, float* accelY, float* accelZ)
{
	uint8_t buf[6] = {0,0,0,0,0,0};
	MPU6886_i2c_recv_data(MPU6886_ACCEL_XOUT_H, 6, buf);

	*accelX=(float)(((int16_t)buf[0]<<8) | buf[1]) * g_accelK;
	*accelY=(float)(((int16_t)buf[2]<<8) | buf[3]) * g_accelK;
	*accelZ=(float)(((int16_t)buf[4]<<8) | buf[5]) * g_accelK;
}

void MPU6886_getAhrsData(float* pitch, float* roll, float* yaw)
{

}
