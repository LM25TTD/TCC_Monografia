#include <TinyGPS.h>
#include <SoftwareSerial.h>

#define GPS_T_OUT 5000
#define GPS_TX_PIN 4
#define GPS_RX_PIN 5

TinyGPS gps;
SoftwareSerial gpsCommunicator(GPS_TX_PIN, GPS_RX_PIN);
float actualLatitude = 0.0f;
float actualLongitude = 0.0f;

static bool feedGps()
{
  unsigned long checker = millis();
  while (true)
  {
    if (gpsCommunicator.available() && gps.encode(gpsCommunicator.read()))
      return true;
    if((millis()-checker)>GPS_T_OUT)
      return false;  
  }
}

void setup()
{
  //... Demais configuracoes
  gpsCommunicator.begin(4800); //4800 bps de baudrate
 }

void loop()
{ 
  gpsCommunicator.listen();
  if(feedGps())
    gps.f_get_position(&actualLatitude, &actualLongitude);  
  //... Demais rotinas	
}