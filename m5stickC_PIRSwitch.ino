/* 
 Copyright (C) 2016, 2018, 2019 hidenorly

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
#include "LooperThreadTicker.h"

#include "GpioDetector.h"
#include "RemoteController.h"
#include "PowerControl.h"
#include "PowerControlPoller.h"

class ManualCursorPoller:public LooperThreadTicker
{
  protected:
    PowerControl* mpPowerControl;

  public:
    ManualCursorPoller(PowerControl* pPowerControl=NULL, int dutyMSec=100):LooperThreadTicker(NULL, NULL, dutyMSec),mpPowerControl(pPowerControl)
    {
    }
    virtual ~ManualCursorPoller(){
    }

     void doCallback(void)
    {
      static bool bLastPowerStatus = mpPowerControl->getPowerStatus();
      M5.update();
      if ( M5.BtnA.wasPressed() ) {
        mpPowerControl->setPower(!mpPowerControl->getPowerStatus());
      }
      bool curPowerStatus = mpPowerControl->getPowerStatus();
      if(bLastPowerStatus != curPowerStatus){
        M5.Lcd.setRotation(3);
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(0, 8);
        M5.Lcd.setTextSize(7);
        M5.Lcd.print(curPowerStatus ? "ON" : "OFF");
        bLastPowerStatus = curPowerStatus;
      }
    }
 };



// --- General setup() function
void setup() {
  // Initialize SerialPort
  Serial.begin(115200);

  // Initialize GPIO
  initializeGPIO();

  // Initialize LCD
  M5.Lcd.fillScreen(BLACK);

  static GpioDetector humanDetector(HUMAN_DETCTOR_PIN, true, HUMAN_UNDETECT_TIMEOUT);
  static IrRemoteController remoteController(IR_SEND_PIN, KEYIrCodes);
  static PowerControl powerControl(&remoteController); // defined in config.cpp
  PowerControlPoller* pPowerControllerPoller = new PowerControlPoller(&powerControl, &humanDetector, HUMAN_UNDETECT_TIMEOUT, HUMAN_POLLING_PERIOD);
  if(pPowerControllerPoller){
    g_LooperThreadManager.add(pPowerControllerPoller);
  }

  ManualCursorPoller* pManualCursorPoller = new ManualCursorPoller(&powerControl, BTN_POLLING_PERIOD);
  if(pManualCursorPoller){
    g_LooperThreadManager.add(pManualCursorPoller);
  }
}

void loop() {
  g_LooperThreadManager.handleLooperThread();
}
