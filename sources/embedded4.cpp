

void treatServerResponse(String *response)
{
  if (response->substring(17, 20)==BLOCK_MESSAGE)
  {
    if(moduleState!=STATE_BLOCKED)
    {
      moduleState=STATE_BLOCKED;
      EEPROM.write(STATE_PERM_DATA_ADDR, moduleState);
      digitalWrite(IO_PIN, moduleState);
    }
  }
  if(response->substring(17, 20)==UNBLOCK_MESSAGE)
  {
    if(moduleState!=STATE_UNBLOCKED)
    {
      moduleState=STATE_UNBLOCKED;
      EEPROM.write(STATE_PERM_DATA_ADDR, STATE_UNBLOCKED);
      digitalWrite(IO_PIN, moduleState);
    }
  }  
}

void loop()
{ 
  gpsCommunicator.listen();
  delay(5000);

  if(feedGps())
    gps.f_get_position(&actualLatitude, &actualLongitude);  

  if((actualLatitude==0.0f) || (actualLongitude==0.0f))
    return;  
  
  cell.listen();
  delay(5000);

  if(doPost(&connectionId, &path, &actualLatitude, &actualLongitude))
  {
    treatServerResponse(&responseFromServer);
#ifdef DEBUG_MESSAGES
    Serial.println(F("Delay"));
#endif
    delay(TIME_TO_SEND);
  }
#ifdef DEBUG_MESSAGES
  Serial.println(responseFromServer);
#endif  
  responseFromServer = ""; 
}

