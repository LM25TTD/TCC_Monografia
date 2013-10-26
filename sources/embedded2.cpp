
boolean createSocket()
{
  if(cell.connectToHostTCP(&connectionId, &HOST, &PORT))
  {
#ifdef DEBUG_MESSAGES
    Serial.println(F("Connect"));
#endif
    if(cell.configureDisplayFormat(&connectionId, GSM_SHOW_ASCII, GSM_NOT_ECHO_RESPONSE))
    {
#ifdef DEBUG_MESSAGES
      Serial.println(F("Display"));      
#endif
      return (true);
    }
  }
  return false; 
}


void rebootGSMProcedure()
{
  digitalWrite(REBOOT_PIN, LOW);
}

void signalizeError()
{
  numOfErrors++;
  if(numOfErrors>MAX_NUM_ERRORS)
  {
    rebootGSMProcedure();
  } 
}

boolean sendMessageToServer(String *request, byte *connectionId)
{     
  if(cell.checkSocketStatusTCP())
  {
    numOfErrors=0;
#ifdef DEBUG_MESSAGES
    Serial.println(F("Socket is Open"));
#endif
    if(cell.sendData(request, connectionId))
    {
#ifdef DEBUG_MESSAGES
      Serial.println(F("SendData"));
#endif
      delay(TIME_TO_READ_RESPONSE);
      responseFromServer = cell.getServerResponse(connectionId);
      cell.cleanCounters();
      return (true);
    }
    else
    {
      signalizeError();
#ifdef DEBUG_MESSAGES
      Serial.println(F("FAIL!!! SendData"));
#endif
      return (false);
    }
  }
  else
  {
#ifdef DEBUG_MESSAGES
    Serial.println(F("Fail on Socket Status!"));
#endif
    while(!cell.dataStart(connectionId))
    {  
      signalizeError();
    }  
    signalizeError();
    cell.cleanCounters();
    return (false);    
  }
  delay(100); 
}