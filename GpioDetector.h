/* 
 Copyright (C) 2018,2019,2020 hidenorly

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

#ifndef __GPIO_DETCTOR_H__
#define __GPIO_DETCTOR_H__

#ifndef GPIO_DETECTION_MIN_UPDATE
#define GPIO_DETECTION_MIN_UPDATE 100 	// minimum period of update
#endif
#ifndef GPIO_DETECTION_THRESHOLD
#define GPIO_DETECTION_THRESHOLD 512 	// if ADC value is greater than this, GPIO is detected.
#endif
#ifndef GPIO_DETECTION_HISTERESES
#define GPIO_DETECTION_HISTERESES 10000	// if ADC value is kept less than this for this period, GPIO is not detected
#endif

class GpioDetector
{
public:
	enum GPIO_CONFIG
	{
		GPIO_G0 = 0,	// Ext G0
		GPIO_G26 = 26,  // Ext G26
		GPIO_G32 = 32,  // GROVE G32
		GPIO_G33 = 33,  // GROVE G33
		GPIO_G36 = 36,  // Ext G36
		GPIO_ADC1 = 0x1000
	};
	GpioDetector(int gpio = GPIO_ADC1, bool bActive=true, unsigned long hysterisis = GPIO_DETECTION_HISTERESES);
	virtual ~GpioDetector();

	bool getStatus(void);
	void update(void);
	void resetToPhysicalState(void);

protected:
	bool _getADCAsDigital(void);

protected:
	int mGPIO;
	bool mPreviousStatus;
	bool mbActive;
	unsigned long mHysterisis;
  unsigned long mLastMeasured = 0;
  unsigned long mLastActive = 0;
  
};

#endif // __GPIO_DETCTOR_H__
