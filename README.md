# M5StickC_Base

This is IoT Framework for M5StickC with WiFi AP & NTP,  PIR Sensor for M5StickC, Infrared LED and MPU6886 or SH200Q sensors.

This supports
 * Turn ON through Ir Remote Transmiter while human is detected.
 * Turn Off if human is not detected for a while.
 * The Ir Code is configurable.
 * Show On/Off status through LCD
 * Manually turn On/Off by M5 Switch
 * For improving availability, sending Ir few times (the count is configurable)
 * Show NTP synced time
 * WebConfig
 * Sensor (MPU6886 or SH200Q)

# HW Config

| Infrared LED Unit | M5StickC |
| :---: | :---: |
| IN | G33 |
| OUT | G32 |
| +5V | +5V |
| GND | GND |

| PIR Unit | M5StickC |
| :---: | :---: |
| OUT | G36 |
| +3.3V | +3.3V |
| GND | GND |
| NC | +5V |
| NC | G0 |
| NC | G26 |
| NC | BAT|

# Config

```config.cpp
// --- config
const int HUMAN_DETCTOR_PIN = GpioDetector::GPIO_G36;
const int HUMAN_UNDETECT_TIMEOUT=1000*60*3; // 3min
const int HUMAN_POLLING_PERIOD=1000; // polling per 1 sec

const int BTN_POLLING_PERIOD=100; // polling per 100msec

const int IR_SEND_PIN = 32; // Use 9 if you want to use M5StickC's Ir LED
KEYIRCODE KEYIrCodes[] = {
  {IRemoteController::KEY_POWER_ON, 0x41B6659AUL, 3, 50},
  {IRemoteController::KEY_POWER_OFF, 0x41B67D82UL, 3, 50},
  {NULL, (uint64_t)NULL, (uint8_t)NULL}
};
```

You can use the IrCode by dumping result of IRrecvDumpV2.

# Dependent libraries

You can install the following libraries from Manage Library in Arduino IDE.

* M5StickC library
* Esp8266IrRemote library

# Configure SSID/Password

Please access to M5StickC's Mac Address with "esp32-wifi" and open browser at 192.168.10.1 to configure them.
