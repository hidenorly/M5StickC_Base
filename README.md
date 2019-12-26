# m5stickC_PIRSwtch

This is PIR Human detection based switch for M5StickC,  PIR Sensor for M5StickC, Infrared LED.

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
const int HUMAN_UNDETECT_TIMEOUT=1000*60*1; // 1min
const int HUMAN_POLLING_PERIOD=1000; // polling per 1 sec

const int BTN_POLLING_PERIOD=100; // polling per 100msec

const int IR_SEND_PIN = 32; // Use 9 if you want to use M5StickC's Ir LED
KEYIRCODE KEYIrCodes[] = {
  {IRemoteController::KEY_POWER_ON, 0x41B6659AUL},
  {IRemoteController::KEY_POWER_OFF, 0x41B67D82UL},
  {NULL, NULL}
};
```
