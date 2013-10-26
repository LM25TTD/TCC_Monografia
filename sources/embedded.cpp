#include <SoftwareSerial.h>
#include <SM5100B_GPRS.h>
#include <TinyGPS.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

//#define DEBUG_MESSAGES

#define MAX_NUM_ERRORS 10
#define GSM_TX_PIN 2
#define GSM_RX_PIN 3
#define GPS_TX_PIN 4
#define GPS_RX_PIN 5
#define GPS_T_OUT 5000

#define TIME_TO_SEND 5000
#define TIME_TO_READ_RESPONSE 2000

#define REBOOT_PIN 9
#define STATE_PERM_DATA_ADDR 0
#define STATE_UNBLOCKED LOW 
#define STATE_BLOCKED HIGH
#define IO_PIN  12
#define ALARM_STATUS_PIN 10

#define BLOCK_MESSAGE "300"
#define UNBLOCK_MESSAGE "200"


TinyGPS gps;
SM5100B_GPRS cell(GSM_TX_PIN, GSM_RX_PIN);  
SoftwareSerial gpsCommunicator(GPS_TX_PIN, GPS_RX_PIN);


String USER_AGENT = "Mozilla/5.0";
String HOST = "lm25ttd.no-ip.org";
int PORT = 8229;

String apn = "tim.br";
String user = "tim";
String password = "tim";
String path = "/AutoTrack_WebManager/api/embedded";
String responseFromServer = "";
byte pdpId = 1;
byte connectionId = 1;

byte numOfErrors=0;

byte moduleState = STATE_UNBLOCKED;

float actualLatitude = 0.0f;
float actualLongitude = 0.0f;

boolean attachNetwork()
{
  if (cell.attachGPRS())
  {
#ifdef DEBUG_MESSAGES
    Serial.println(F("GPRS"));
#endif
    if(cell.setUpPDPContext(&pdpId, &apn, &user, &password))
    {
#ifdef DEBUG_MESSAGES
      Serial.println(F("SetPDP"));
#endif
      if(cell.activatePDPContext(&pdpId))
      {
#ifdef DEBUG_MESSAGES
        Serial.println(F("ActivePDP"));
#endif
      return (true);
      }
    }
  }
  return (false);
}