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

#ifndef __WEBCONFIG_H__
#define __WEBCONFIG_H__

#include <WebServer.h>

class WebConfig
{
public:
	static void setup_httpd(void);
	static void handleWebServer(void);

protected:
	static void httpd_handleRootGet(void);
	static void httpd_handleRootPost(void);

	static WebServer* mpHttpd; // http server for WiFi AP Mode
	static const char* const HTML_TAIL;
};

#endif // __WEBCONFIG_H__