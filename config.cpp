/* 
 Copyright (C) 2016,2018,2019 hidenorly

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
#include "config.h"

#include "GpioDetector.h"
#include "RemoteController.h"

// --- config
const int HUMAN_DETCTOR_PIN = GpioDetector::GPIO_G36;
const int HUMAN_UNDETECT_TIMEOUT=1000*60*1; // 1min
const int HUMAN_POLLING_PERIOD=1000; // polling per 1 sec

const int BTN_POLLING_PERIOD=100; // polling per 100msec

const int IR_SEND_PIN = 32; // Use 9 if you want to use M5StickC's Ir LED
KEYIRCODE KEYIrCodes[] = {
  {IRemoteController::KEY_POWER_ON, 0x41B6659AUL},
  {IRemoteController::KEY_POWER_OFF, 0x41B67D82UL},
  {(int)NULL, (uint64_t)NULL}
};


// --- GPIO config
void initializeGPIO(void) {
  // General config
  M5.begin();     // Initialze M5 stack C
  DEBUG_PRINTLN("M5.begin()");

  // If pin is NC, we should set {output / High} or {input / pull up enabled} on the pin.
  // Project related config
  pinMode(HUMAN_DETCTOR_PIN, INPUT_PULLUP);   // Optical Detector Input (High: detected)
}
