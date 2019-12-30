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

#ifndef __CONFIG_H__
#define __CONFIG_H__

// --- config: WIFI
extern const char* WIFI_CONFIG;
extern const char* WIFIAP_PASSWORD;

// --- config: NTP
extern const char* NTP_SERVER;
extern const int NTP_TIMEZONE_OFFSET;

// --- config: httpd
extern int HTTP_SERVER_PORT;
extern const char* HTML_HEAD;

// --- GPIO config
extern const int HUMAN_DETCTOR_PIN;
extern const int IR_SEND_PIN;

// -- params
extern const int HUMAN_UNDETECT_TIMEOUT;
extern const int HUMAN_POLLING_PERIOD;
extern const int BTN_POLLING_PERIOD;

#include "RemoteController.h"
extern KEYIRCODE KEYIrCodes[];

void initializeGPIO(void);


#endif // __CONFIG_H__
