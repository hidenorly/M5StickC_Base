/* 
 Copyright (C) 2019,2020 hidenorly

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
#include "NtpUtil.h"
#include <SPIFFS.h>


String NtpUtil::mNtpServer = NTP_DEFAULT_SERVER;
int NtpUtil::mTimeZoneOffset = NTP_DEFAULT_TIMEZONE_OFFSET;

bool NtpUtil::isTimeValid(void)
{
  struct tm timeInfo;
  getLocalTime(&timeInfo);
  return timeInfo.tm_year!=1970;
}

String NtpUtil::getServer(void)
{
  return mNtpServer;
}

int NtpUtil::getTimeZoneOffset(void)
{
  return mTimeZoneOffset;
}


void NtpUtil::saveConfig(String ntpServer, String timeZoneOffset)
{
  if( ntpServer=="" ){
    ntpServer = getServer();
  }
  if(timeZoneOffset==""){
    timeZoneOffset = getTimeZoneOffset();
  }
  if ( SPIFFS.exists(NTP_CONFIG) ) {
    SPIFFS.remove(NTP_CONFIG);
  }

  File f = SPIFFS.open(NTP_CONFIG, "w");
  f.println(ntpServer);
  f.println(timeZoneOffset);
  f.close();

  mNtpServer = ntpServer;
  mTimeZoneOffset = timeZoneOffset.toInt();
}

void NtpUtil::loadConfig(void)
{
  if ( SPIFFS.exists(NTP_CONFIG) ) {
    // found existing config
    File f = SPIFFS.open(NTP_CONFIG, "r");
    String ntpServer = f.readStringUntil('\n');
    String timeZoneOffset = f.readStringUntil('\n');
    f.close();

    ntpServer.trim();
    timeZoneOffset.trim();
    mNtpServer = ntpServer;
    mTimeZoneOffset = timeZoneOffset.toInt();
  } else {
    // not found existing config
    mNtpServer = NTP_DEFAULT_SERVER;
    mTimeZoneOffset = NTP_DEFAULT_TIMEZONE_OFFSET;
  }
}

void NtpUtil::sync(void)
{
  DEBUG_PRINT("NTP sync");
  configTime(mTimeZoneOffset * 3600L, 0, mNtpServer.c_str());
  DEBUG_PRINTLN("ed");
}
