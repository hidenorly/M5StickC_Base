/* 
 Copyright (C) 2020 hidenorly

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

#ifndef __PAL_I2C_H__
#define __PAL_I2C_H__

#include "base.h"

enum I2C_BUS_CHANNLES
{
	I2C_BUS_CHANNEL_0 = 0,
	I2C_BUS_CHANNEL_1
};

void i2c_initialize(uint8_t i2cBusChannel, uint8_t pinSDA, uint8_t pinSCL, uint32_t clock);
void i2c_finalize(uint8_t i2cBusChannel);

int i2c_send_multiple_data(uint8_t i2cBusChannel, int8_t slaveAddress, uint8_t cmd, const uint8_t *send_buf, size_t send_buf_len);
int i2c_send_byte(uint8_t i2cBusChannel, uint8_t slaveAddress, uint8_t cmd, const uint8_t sendData);
int i2c_recv_multiple_data(uint8_t i2cBusChannel, uint8_t slaveAddress, uint8_t cmd, uint8_t *receive_buf, size_t receive_buf_len);
uint8_t i2c_recv_byte(uint8_t i2cBusChannel, uint8_t slaveAddress, uint8_t cmd);


#endif // __PAL_I2C_H__
