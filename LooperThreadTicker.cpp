/* 
 Copyright (C) 2016, 2019 hidenorly

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
#include "LooperThreadTicker.h"

// --- TimerContextTicker
// Please note that this doesn't require to work with LooperThreadManager.
// We can use this TimerContextTicker alone but the doCallback will be called back as timer context.
TimerContextTicker::TimerContextTicker(CALLBACK_FUNC pFunc, void* pArg, int dutyMSec)
{
  mpFunc = pFunc;
  mpArg = pArg;
  mDutySec = dutyMSec;

  mpETSTimer = NULL;
}

TimerContextTicker::~TimerContextTicker()
{
  unregisterFromTimer();

  mpFunc = NULL;
  mpArg = NULL;
  mDutySec = 0;
}

int TimerContextTicker::getDutyMSec(void)
{
  return mDutySec;
}

void TimerContextTicker::registerToTimer(void)
{
  if( NULL == mpETSTimer ) {
    mpETSTimer = new Ticker();
  } else {
    mpETSTimer->detach();
  }
  mpETSTimer->attach_ms(mDutySec, _timerCallback, reinterpret_cast<void*>(this));

/*  DEBUG_PRINT("Timer attach");
  DEBUG_PRINT(mDutySec);
  DEBUG_PRINT(":");
  DEBUG_PRINTLN((int)this);
*/
}

void TimerContextTicker::unregisterFromTimer(void)
{
  if( NULL != mpETSTimer ) {
    mpETSTimer->detach();
    delete mpETSTimer; mpETSTimer=NULL;
  }
}

void TimerContextTicker::_timerCallback(void* pTimerContextTicker)
{
  TimerContextTicker* pThis = reinterpret_cast<TimerContextTicker*>(pTimerContextTicker);
  pThis->preCallback();
}

void TimerContextTicker::preCallback(void)
{
  doCallback();
}

void TimerContextTicker::doCallback(void)
{
//  DEBUG_PRINTLN("TimerContextTicker");
  if(mpFunc){
    mpFunc(mpArg);
  }
}


// --- LooperThreadTicker
// Please note that this requires to work with LooperThreadManager.
// We need g_LooperThreadManager.add(this);
// And then the doCallback will be called back from looper() context.

LooperThreadTicker::LooperThreadTicker(CALLBACK_FUNC pFunc, void* pArg, int dutyMSec):TimerContextTicker(pFunc, pArg, dutyMSec)
{
  mFlagActivated = false;
}

LooperThreadTicker::~LooperThreadTicker()
{
  mFlagActivated = false;
}


void LooperThreadTicker::setActive(int bActive)
{
  mFlagActivated = bActive;  
}

int LooperThreadTicker::getActive()
{
  return mFlagActivated;
}

void LooperThreadTicker::preCallback(void)
{
  // set just flag to callback from looper()
  setActive(true);
}

// override me
void LooperThreadTicker::doCallback(void)
{
//  DEBUG_PRINTLN("LooperThreadTicker");
  if(mpFunc){
    mpFunc(mpArg);
  }
}



// TODO: I'm not sure why but I cannot instanciate template class here. But TemplateArray.cpp is Ok...
//template class TemplateArray<LooperThreadTicker>;

// --- LooperThreadManager
// Global LooperThreadManager;
LooperThreadManager g_LooperThreadManager; // g_LooperThreadManager(20); // Specify max thread count if you need (default:10)

LooperThreadManager::LooperThreadManager(int nMaxTicker)
{
}

LooperThreadManager::~LooperThreadManager()
{
  for(int i=0, c=size(); i<c; i++){
    LooperThreadTicker* pTicker = getPtr(i);
    if( NULL != pTicker ){
      pTicker->unregisterFromTimer();
      delete pTicker;
    }
  }
}

void LooperThreadManager::handleLooperThread()
{
  for(int i=0, c=size(); i<c; i++){
    LooperThreadTicker* pTicker = getPtr(i);
    if( pTicker && pTicker->getActive() ){
//      char buf[50];
//      sprintf(buf, "LooperThreadTicker::preCallback: %x", pTicker);
//      DEBUG_PRINTLN(buf);
      pTicker->doCallback();
      pTicker->setActive(false);
    }
  }
}

void LooperThreadManager::add(LooperThreadTicker* pTicker)
{
  if( pTicker ){
    TickerArray::add(pTicker);
    pTicker->registerToTimer();
  }
}
