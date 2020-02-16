/* 
 Copyright (C) 2016,2019,2020 hidenorly

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

#include <Ticker.h>


class WiFiUtil
{
public:
	typedef void (*CALLBACK_FUNC)(void*);

	static String getDefaultSSID(void);
	static void setupWiFiAP(void);
	static void setupWiFiClient(void);
	static void disconnect(void);

	static void saveWiFiConfig(String ssid, String pass);
	static void loadWiFiConfig(String& ssid, String& pass);
	static void setStatusCallback(CALLBACK_FUNC pConnectedFunc=NULL, void* pConnectedArg=NULL, CALLBACK_FUNC pDisconnectedFunc=NULL, void* pDisconnectedArg=NULL);
	static void clearStatusCallback(void);
	static void handleWiFiClientStatus(void);
	static bool isNetworkAvailable(void);
	static int getMode(void);

protected:
    static CALLBACK_FUNC mpConnectedCallback;
    static void* mpConnectedArg;
    static CALLBACK_FUNC mpDisconnectedCallback;
    static void* mpDisconnectedArg;

	static Ticker mWifiStatusTracker;
	static bool mbNetworkConnected;
	static int mbPreviousNetworkConnected;
	static bool mbIsConnecting;
	static int mMode;
};

#endif
