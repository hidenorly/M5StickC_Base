/* 
 Copyright (C) 2016,2019 hidenorly

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

#ifndef __WIFIUTIL_H__
#define __WIFIUTIL_H__

#include <arduino.h>
#include <Ticker.h>

typedef void (*CALLBACK_FUNC)(void*);


class WiFiUtil
{
public:
	static String getDefaultSSID(void);
	static void setupWiFiAP(void);
	static void setupWiFiClient(void);

	static void saveWiFiConfig(String ssid, String pass);
	static void loadWiFiConfig(String& ssid, String& pass);
	static void setStatusCallback(CALLBACK_FUNC pFunc=NULL, void* pArg=NULL);
	static void clearStatusCallback(void);
	static void handleWiFiClientStatus(void);

protected:
	static void setupWiFiStatusTracker(void);
	static void checkWiFiStatus(CTrackerParam* p);

public:
    static CALLBACK_FUNC mspCallback;
    static void* mspArg;

	static Ticker msWifiStatusTracker;
	volatile static bool msbNetworkConnected;
};

#endif
