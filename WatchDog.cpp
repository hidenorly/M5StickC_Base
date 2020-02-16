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
#include "WatchDog.h"

hw_timer_t* WatchDog::mTimer = NULL;

static void IRAM_ATTR handleWatchDogFired(void)
{
  ets_printf("watch dog fired!\r");
  esp_restart();
}

void WatchDog::disable(void)
{
  if( mTimer ){
    timerAlarmDisable(mTimer);
    timerEnd(mTimer);
    mTimer = NULL;
  }
}

void WatchDog::enable(int nPeriod)
{
  disable();

  mTimer = timerBegin(0, 80, true); // timer 0 with div 80
  timerAttachInterrupt(mTimer, &handleWatchDogFired, true);
  timerAlarmWrite(mTimer, nPeriod * 1000, false);
  timerAlarmEnable(mTimer);
}

bool WatchDog::getEnabled(void)
{
  return mTimer ? true : false;
}

void WatchDog::heartBeat(void)
{
  if( mTimer ){
    timerWrite(mTimer, 0);
  }
}


int HeapWatchDog::mThreshold = HEAP_CHECKER_DISABLE;

void HeapWatchDog::enable(int nHeapThreshold)
{

}
void HeapWatchDog::disable(void)
{
  mThreshold = HEAP_CHECKER_DISABLE;
}

bool HeapWatchDog::getEnabled(void)
{
  return (mThreshold != HEAP_CHECKER_DISABLE);
}

void HeapWatchDog::check(void)
{
  if( getEnabled() ){
      if(xPortGetFreeHeapSize() < mThreshold){
        ESP.restart();
      }
  }
}


