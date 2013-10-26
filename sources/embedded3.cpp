boolean doPost(byte *connectionId, String *path, float *latitude, float *longitude)
{
  String request = "";
  String parameters = buildJsonContent(latitude, longitude);
  request += "POST ";
  request += *path;
  request += " HTTP/1.1\nHost: ";
  request += HOST;
  request += "\nConnection: keep-alive";
  request += "\nUser-Agent: ";
  request += (USER_AGENT+"\n");
  request += "Accept: application/json\n";
  request += "Content-Length: ";
  request += parameters.length();
  request += "\n";
  request += "Content-Type: application/json\n\n";
  request += parameters;

  return sendMessageToServer(&request, connectionId);  
}

String buildJsonContent(float *latitude, float *longitude)
{
  String jsonContent= "";
  jsonContent = "{";
  jsonContent += "\"idModule\":\"12345678\",\"codAccess\":\"25897\",";

  char latConverted[10] = "";

  jsonContent += "\"latitude\":\"";
  dtostrf(*latitude, 1, 4, latConverted);
  jsonContent+= latConverted;

  char longConverted[10] = "";

  jsonContent += "\",\"longitude\":\"";
  dtostrf(*longitude, 1, 4, longConverted);
  jsonContent += longConverted;
  jsonContent += "\",\"alarm\":\"";
  jsonContent += digitalRead(ALARM_STATUS_PIN); 
  jsonContent += "\"}";

  return jsonContent;
}

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
  digitalWrite(REBOOT_PIN, HIGH);
  pinMode(REBOOT_PIN, OUTPUT);
  
  pinMode(IO_PIN, OUTPUT);
  moduleState = EEPROM.read(STATE_PERM_DATA_ADDR);
  digitalWrite(IO_PIN, moduleState);

  pinMode(ALARM_STATUS_PIN, INPUT);
#ifdef DEBUG_MESSAGES  
  Serial.begin(9600);
#endif  
  cell.initializeModule(9600);
  attachNetwork();
  createSocket();
  gpsCommunicator.begin(4800);
#ifdef DEBUG_MESSAGES  
  Serial.println(F("Setup Ok!"));
#endif
}