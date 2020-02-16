/* 
 Copyright (C) 2019,2020 hidenorly

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

#ifndef __POWER_CONTROL_POLLER_H__
#define __POWER_CONTROL_POLLER_H__

#include "base.h"
#include "LooperThreadTicker.h"
#include "PowerControl.h"
#include "GpioDetector.h"
#include "config.h"
 
class PowerControlPoller:public LooperThreadTicker
{
  public:
    PowerControlPoller(PowerControl* pPowerControl=NULL, GpioDetector* pHumanDetector=NULL, int humanTimeout=HUMAN_UNDETECT_TIMEOUT, int dutyMSec=0);
    virtual ~PowerControlPoller();

    virtual void doCallback(void);
    void notifyManualOperation(bool bOn);

protected:
	PowerControl* mpPowerControl;
	GpioDetector* mpHumanDetector;
	int mHumanTimeout;
	unsigned long mManualOperationRequestedTime;
	bool mbManualOperationPowerRequest;
};

#endif /* __POWER_CONTROL_POLLER_H__ */
