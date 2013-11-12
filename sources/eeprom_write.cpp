#include <EEPROM.h>

#define STATE_PERM_DATA_ADDR 0
#define STATE_UNBLOCKED LOW 
#define STATE_BLOCKED HIGH

byte moduleState = STATE_UNBLOCKED;

void setup()
{
  //... Demais configuracoes
  moduleState = EEPROM.read(STATE_PERM_DATA_ADDR);
 }

void treatServerResponse(String *response)
{
  if (response->substring(17, 20)==BLOCK_MESSAGE)
  {
    if(moduleState!=STATE_BLOCKED)
    {
      moduleState=STATE_BLOCKED;
      EEPROM.write(STATE_PERM_DATA_ADDR, moduleState);
      //Comando para bloqueio aqui
    }
  }
  if(response->substring(17, 20)==UNBLOCK_MESSAGE)
  {
    if(moduleState!=STATE_UNBLOCKED)
    {
      moduleState=STATE_UNBLOCKED;
      EEPROM.write(STATE_PERM_DATA_ADDR, STATE_UNBLOCKED);
      //Comando para desbloqueio aqui
    }
  }  
}
//... Demais definicoes, inclusive void loop()  