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

#include "RemoteController.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>

IrRemoteController::IrRemoteController(int irPort, KEYIRCODE keys[])
{
  mIRsend = new IRsend(irPort);
  if( mIRsend ){
//    DEBUG_PRINTLN("IRsend.begin()");
    mIRsend->begin();
  }
  mpKeys = keys;
}

IrRemoteController::~IrRemoteController()
{
  if( mIRsend ){
    delete mIRsend;
    mIRsend = NULL;
  }
}

void IrRemoteController::sendKey(int keyCode)
{
  if(mpKeys && mIRsend){
    KEYIRCODE* pKeys = mpKeys;
    while( pKeys->keyCode != (int)NULL ){
      if( pKeys->keyCode == keyCode ){
        for(int i=0; i<pKeys->repeatCount; i++){
          mIRsend->sendNEC(pKeys->irCode);
          delay(pKeys->repeatDelay);
        }
      }
      pKeys++;
    }
  }
}
