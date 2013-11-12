#define IO_PIN  12
#define STATE_UNBLOCKED LOW 
#define STATE_BLOCKED HIGH

void setup()
{
  pinMode(IO_PIN, OUTPUT); //Define o modo de operacao do pino
  //... Demais configuracoes e obtencao do valor de moduleState
  digitalWrite(IO_PIN, moduleState);
}

void treatServerResponse(String *response)
{
 //..Leitura da resposta
    if(moduleState!=STATE_BLOCKED)
    {
	 moduleState=STATE_BLOCKED; //HIGH
	 //...Demais rotinas
	 digitalWrite(IO_PIN, moduleState);
    }
    if(moduleState!=STATE_UNBLOCKED)
    {
	 moduleState=STATE_UNBLOCKED; //LOW
	 //...Demais rotinas
	 digitalWrite(IO_PIN, moduleState);
    }
}
//... Demais definicoes, inclusive void loop()  