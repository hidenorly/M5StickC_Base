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

#include "WiFiUtil.h"
#include "WebConfig.h"
#include <SPIFFS.h>
#include <WiFi.h>

// --- mode changer
bool initializeProperMode(bool bSPIFFS){
  M5.update();

  if( !bSPIFFS || M5.BtnA.wasPressed() || (!SPIFFS.exists(WIFI_CONFIG))){
    // setup because WiFi AP mode is specified or WIFI_CONFIG is not found.
    WiFiUtil::setupWiFiAP();
    setup_httpd();
    return false;
  } else {
    WiFiUtil::setupWiFiClient();
  }
  return true;
}

// --- handler for WiFi client enabled
class MyNetHandler
{
  protected:
    static void onWiFiClientConnected(void* pArg){
      DEBUG_PRINTLN("WiFi connected.");
      DEBUG_PRINT("IP address: ");
      DEBUG_PRINTLN(WiFi.localIP());

      setup_httpd();  // comment this out if you don't need to have httpd on WiFi client mode
      configTime(NTP_TIMEZONE_OFFSET * 3600L, 0, NTP_SERVER);
    }

  public:
    static void setup(void)
    {
      WiFiUtil::setStatusCallback(onWiFiClientConnected, NULL);
    }
};


class SwitchBtnPoller:public LooperThreadTicker
{
  protected:
    PowerControl* mpPowerControl;

  public:
    SwitchBtnPoller(PowerControl* pPowerControl=NULL, int dutyMSec=100):LooperThreadTicker(NULL, NULL, dutyMSec),mpPowerControl(pPowerControl)
    {
    }
    virtual ~SwitchBtnPoller(){
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


class TimePoller:public LooperThreadTicker
{
  public:
    TimePoller(int dutyMSec=0):LooperThreadTicker(NULL, NULL, dutyMSec)
    {
    }

  protected:
    const int NTP_SYNC_DURATION = 900; //15min;

    void syncTime(void)
    {
      static int i=0;
      i++;
      if((i % NTP_SYNC_DURATION) == 0){
        configTime(NTP_TIMEZONE_OFFSET * 3600L, 0, NTP_SERVER);
      }
    }

    virtual void doCallback(void)
    {
      struct tm timeInfo;
      char s[20];

      getLocalTime(&timeInfo);
      sprintf(s, "%04d/%02d/%02d %02d:%02d:%02d",
              timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
              timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    
      DEBUG_PRINTLN(s);

      syncTime();
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

  // Initialize SPI File System
  bool bSPIFFS = SPIFFS.begin();
  if(!bSPIFFS){
    SPIFFS.format();
  }

  // Check mode
  delay(1000);
  if(initializeProperMode(bSPIFFS)){
    static TimePoller* sPoll=new TimePoller(1000);
    g_LooperThreadManager.add(sPoll);
  }

  MyNetHandler::setup();

  static GpioDetector humanDetector(HUMAN_DETCTOR_PIN, true, HUMAN_UNDETECT_TIMEOUT);
  static IrRemoteController remoteController(IR_SEND_PIN, KEYIrCodes);
  static PowerControl powerControl(&remoteController); // defined in config.cpp
  PowerControlPoller* pPowerControllerPoller = new PowerControlPoller(&powerControl, &humanDetector, HUMAN_UNDETECT_TIMEOUT, HUMAN_POLLING_PERIOD);
  if(pPowerControllerPoller){
    g_LooperThreadManager.add(pPowerControllerPoller);
  }

  SwitchBtnPoller* pSwitchBtnPoller = new SwitchBtnPoller(&powerControl, BTN_POLLING_PERIOD);
  if(pSwitchBtnPoller){
    g_LooperThreadManager.add(pSwitchBtnPoller);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiUtil::handleWiFiClientStatus();
  handleWebServer();
  g_LooperThreadManager.handleLooperThread();
}
