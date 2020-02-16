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

#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "config.h"
#include "esp_system.h"

class WatchDog
{
public:
  static void enable(int nPeriod = 10000);
  static void disable(void);
  static bool getEnabled(void);
  static void heartBeat(void);

protected:
  static hw_timer_t* mTimer;
};

#ifndef HEAP_CHECKER_THRESHOLD
#define HEAP_CHECKER_THRESHOLD 128000
#endif

#define HEAP_CHECKER_DISABLE -1

class HeapWatchDog
{
public:
  static void enable(int nHeapThreshold = HEAP_CHECKER_THRESHOLD);
  static void disable(void);
  static bool getEnabled(void);
  static void check(void);

protected:
  static int mThreshold;
};


#endif
