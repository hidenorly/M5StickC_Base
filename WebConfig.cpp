/* 
 Copyright (C) 2016, 2018 hidenorly

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
#include "WiFiUtil.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include "WebConfig.h"
#include <SPIFFS.h>

// --- HTTP server related
static WebServer* g_pHttpd = NULL; // http server for WiFi AP Mode

char* HTML_TAIL = "</body></html>";

void httpd_handleRootGet(void);
void httpd_handleRootPost(void);

void setup_httpd() {
  if( g_pHttpd == NULL ){
    g_pHttpd = new WebServer(HTTP_SERVER_PORT);
  }
  g_pHttpd->on("/", HTTP_GET, httpd_handleRootGet);
  g_pHttpd->on("/", HTTP_POST, httpd_handleRootPost);
  g_pHttpd->begin();
  DEBUG_PRINTLN("HTTP server started.");
}

void httpd_handleRootGet() {
  DEBUG_PRINTLN("Receive: GET /");
  if (g_pHttpd != NULL) {
    String html = HTML_HEAD;
    html += "<h1>WiFi/Power Control Settings</h1>";
    html += "<form method='post'>";
    html += "  <input type='text' name='ssid' placeholder='ssid'><br>";
    html += "  <input type='text' name='pass' placeholder='pass'><br>";
    html += "  <input type='submit'><br>";
    html += "</form>";
    html += HTML_TAIL;
    g_pHttpd->send(200, "text/html", html);
  }
}

void httpd_handleRootPost() {
  DEBUG_PRINTLN("Receive: POST /");
  if( g_pHttpd != NULL ){
    String ssid = g_pHttpd->arg("ssid");
    String pass = g_pHttpd->arg("pass");
  
    // --- SSID & Password are specified.
    if( (ssid=="format") && (pass=="format") ){
      SPIFFS.format();
      String html = HTML_HEAD;
      html += "Format successful on SPIFFS!";
      html += HTML_TAIL;
      g_pHttpd->send(200, "text/html", html);
    } else {
      WiFiUtil::saveWiFiConfig(ssid, pass);
    }
    
    String html = HTML_HEAD;
    html += "<h1>WiFi Settings</h1>";
    html += ((ssid!="") ? ssid : "ssid isn't changed") + "<br>";
    html += ((pass!="") ? pass : "password isn't changed") + "<br>";
    html += HTML_TAIL;

    g_pHttpd->send(200, "text/html", html);

    delay(1000*3);

    ESP.restart();
  }
}

void handleWebServer(){
  if( g_pHttpd ){
    g_pHttpd->handleClient();
  }
}
