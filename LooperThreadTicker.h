/* 
 Copyright (C) 2016 hidenorly

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

#ifndef __LOOPERTHREADTICKER_H__
#define __LOOPERTHREADTICKER_H__

#include "base.h"
#include <Ticker.h>
#include "TemplateArray.h"

class TimerContextTicker
{
  public:
    typedef void (*CALLBACK_FUNC)(void*);
    TimerContextTicker(CALLBACK_FUNC pFunc=NULL, void* pArg=NULL, int dutyMSec=0);
    virtual ~TimerContextTicker();
    int getDutyMSec(void);

  protected:
    static void _timerCallback(void* pTimerContextTicker);
    virtual void preCallback(void);

  public:
    void registerToTimer(void);
    void unregisterFromTimer(void);

    virtual void doCallback(void);

  protected:
    CALLBACK_FUNC mpFunc;
    void* mpArg;
    int mDutySec;
    Ticker* mpETSTimer;
};

class LooperThreadTicker:public TimerContextTicker
{
  public:
    LooperThreadTicker(CALLBACK_FUNC pFunc=NULL, void* pArg=NULL, int dutyMSec=0);
    ~LooperThreadTicker();
    void setActive(int bActive);
    int getActive();

    // --- for LooperThreadManager
    virtual void doCallback(void);

  protected:
    virtual void preCallback(void);
    volatile int mFlagActivated;
};

extern template class TemplateArray<LooperThreadTicker>;
typedef TemplateArray<LooperThreadTicker> TickerArray;

//typedef VoidPtrArray TickerArray;

class LooperThreadManager:public TickerArray
{
  public:
    LooperThreadManager(int nMaxTicker=10);
    ~LooperThreadManager();
    void handleLooperThread();

    void add(LooperThreadTicker* pTicker);
};

// Global LooperThreadManager;
extern LooperThreadManager g_LooperThreadManager;

#endif // __LOOPERTHREADTICKER_H__
