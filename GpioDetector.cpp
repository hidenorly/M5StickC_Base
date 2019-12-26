/* 
 Copyright (C) 2018, 2019 hidenorly

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

#include "GpioDetector.h"
#include "base.h"

GpioDetector::GpioDetector(int gpio, bool bActive, unsigned long hysterisis):mGPIO(gpio), mbActive(bActive), mHysterisis(hysterisis)
{
	mLastMeasured = 0;
	mPreviousStatus = false;
	mLastActive = 0;
}

GpioDetector::~GpioDetector()
{

}

bool GpioDetector::getStatus(void)
{
	return mPreviousStatus;
}


void GpioDetector::update(void)
{
	unsigned long n = millis();

	if( (n - mLastMeasured) < GPIO_DETECTION_MIN_UPDATE ) return; // within 100msec barrier
	mLastMeasured = n;

	bool curStatus = false;

	if(mGPIO < GPIO_ADC1){
		curStatus = digitalRead(mGPIO);
	} else {
      curStatus = _getADCAsDigital();
	}

	if( curStatus == mbActive ) {
		mLastActive = n;
		mPreviousStatus = true;
	} else if ((n-mLastActive) > mHysterisis ) {
		mPreviousStatus = false;
	}
}

bool GpioDetector::_getADCAsDigital(void)
{
	int adcVal = 0; //system_adc_read();

	DEBUG_PRINT("adc:");
	DEBUG_PRINTLN(String(adcVal));

	return (adcVal > GPIO_DETECTION_THRESHOLD);
}
