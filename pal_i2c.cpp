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


#include "base.h"
#include "pal_i2c.h"

#define ENABLE_I2C_DEBUG 0


static TwoWire* gsWire[2]={NULL, NULL};

bool isValidChannel(uint8_t i2cBusChannel)
{
	return (i2cBusChannel == I2C_BUS_CHANNEL_0) || (i2cBusChannel == I2C_BUS_CHANNEL_1);
}

void i2c_initialize(uint8_t i2cBusChannel, uint8_t pinSDA, uint8_t pinSCL, uint32_t clock)
{
	if( !isValidChannel(i2cBusChannel) ) return;

	if( NULL == gsWire[i2cBusChannel] ){
		gsWire[i2cBusChannel] = new TwoWire(i2cBusChannel);
		gsWire[i2cBusChannel]->begin(pinSDA, pinSCL, clock);
	}
}

void i2c_finalize(uint8_t i2cBusChannel)
{
	if( !isValidChannel(i2cBusChannel) ) return;

	if( NULL == gsWire[i2cBusChannel] ){
		delete gsWire[i2cBusChannel];
	}
}

int i2c_send_multiple_data(uint8_t i2cBusChannel, int8_t slaveAddress, uint8_t cmd, const uint8_t *send_buf, size_t send_buf_len)
{
	int ret = -1;
	if( !isValidChannel(i2cBusChannel) && (NULL != gsWire[i2cBusChannel]) ) return -1;

	gsWire[i2cBusChannel]->beginTransmission(slaveAddress);
	gsWire[i2cBusChannel]->write(cmd);
#if ENABLE_I2C_DEBUG
	DEBUG_PRINTF("i2c_data write %x:", cmd);
#endif
	for(int i=0; i<send_buf_len; i++){
		gsWire[i2cBusChannel]->write(send_buf[i]);
#if ENABLE_I2C_DEBUG
		DEBUG_PRINTF("%x ", send_buf[i]);
#endif
	}
	ret = (gsWire[i2cBusChannel]->endTransmission() != 0);
#if ENABLE_I2C_DEBUG
		DEBUG_PRINTF("(ret=%d)\r\n", ret);
#endif

	return ret;
}

int i2c_send_byte(uint8_t i2cBusChannel, uint8_t slaveAddress, uint8_t cmd, const uint8_t sendData)
{
	return i2c_send_multiple_data(i2cBusChannel, slaveAddress, cmd, &sendData, 1);
}

int i2c_recv_multiple_data(uint8_t i2cBusChannel, uint8_t slaveAddress, uint8_t cmd, uint8_t *receive_buf, size_t receive_buf_len)
{
	int ret = -1;
	if( !isValidChannel(i2cBusChannel) && (NULL != gsWire[i2cBusChannel]) ) return -1;

	gsWire[i2cBusChannel]->beginTransmission(slaveAddress);
	gsWire[i2cBusChannel]->write(cmd);
	gsWire[i2cBusChannel]->endTransmission(false);
	gsWire[i2cBusChannel]->requestFrom(slaveAddress, receive_buf_len);
	if( 0 == gsWire[i2cBusChannel]->available() ) return -1;

#if ENABLE_I2C_DEBUG
	DEBUG_PRINTF("i2c_data read %x:", cmd);
#endif
	int i=0;
	while ( gsWire[i2cBusChannel]->available() && (i<receive_buf_len) ) {
	    receive_buf[i] = gsWire[i2cBusChannel]->read();
#if ENABLE_I2C_DEBUG
		DEBUG_PRINTF("%x ", receive_buf[i]);
#endif
		i++;
    }
	ret = !(i==receive_buf_len);
#if ENABLE_I2C_DEBUG
		DEBUG_PRINTF("(ret=%d)\r\n", ret);
#endif

	return ret;
}

uint8_t i2c_recv_byte(uint8_t i2cBusChannel, uint8_t slaveAddress, uint8_t cmd)
{
	uint8_t buf;
	int ret = i2c_recv_multiple_data(i2cBusChannel, slaveAddress, cmd, &buf, 1);

	return ret ? 0 : buf;
}

