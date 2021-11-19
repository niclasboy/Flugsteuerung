#include "rx.h"
#include "flugstr.h"

volatile byte buffer[25];
volatile byte rawBuffer[25];
volatile byte stateCounter = 0;
volatile byte feedState = 0;
uint8_t counter10msTick;
bool failSafeActive = 1;

void initRx()
{

  UBRR3L = 9; // UART3 - 8E2 - 100000 Baud - Interrupt füllt Ringbuffer
  UCSR3B |= (1 << RXCIE3) | (1 << RXEN3);
  UCSR3C |= (1 << UPM31) | (1 << USBS3) | (1 << UCSZ31) | (1 << UCSZ30);

  TCNT5 = 2786;
  TCCR5B = (1 << CS52);
  TIMSK5 = (1 << TOIE5);

  initServos();
  xTaskCreate(rxProcessing, "RX", 128, NULL, 0, NULL); //Bearbeitung des Ringbuffers, wenn neu Daten anliegen
}

void rxProcessing(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    counter10msTick++;
    uint8_t failSafeCondition1 = buffer[23] & SBUS_FAILSAFE;
    uint8_t failSafeCondition2 = false;    
    if(counter10msTick==100)
    {
      if(_goodFrames < 5)
      {
        failSafeCondition2 = true;
      }
      _goodFrames = 0;
      counter10msTick = 0;
    }
    failSafeActive = failSafeCondition1 || failSafeCondition2;
    if (failSafeActive == SBUS_FAILSAFE_INACTIVE)
    {
      rxDataIn[0] = map(((buffer[1] | buffer[2] << 8) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[1] = map(((buffer[2] >> 3 | buffer[3] << 5) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[2] = map(((buffer[3] >> 6 | buffer[4] << 2 | buffer[5] << 10) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[3] = map(((buffer[5] >> 1 | buffer[6] << 7) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[4] = map(((buffer[6] >> 4 | buffer[7] << 4) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[5] = map(((buffer[7] >> 7 | buffer[8] << 1 | buffer[9] << 9) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[6] = map(((buffer[9] >> 2 | buffer[10] << 6) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[7] = map(((buffer[10] >> 5 | buffer[11] << 3) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[8] = map(((buffer[12] | buffer[13] << 8) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[9] = map(((buffer[13] >> 3 | buffer[14] << 5) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[10] = map(((buffer[14] >> 6 | buffer[15] << 2 | buffer[16] << 10) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[11] = map(((buffer[16] >> 1 | buffer[17] << 7) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[12] = map(((buffer[17] >> 4 | buffer[18] << 4) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[13] = map(((buffer[18] >> 7 | buffer[19] << 1 | buffer[20] << 9) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[14] = map(((buffer[20] >> 2 | buffer[21] << 6) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[15] = map(((buffer[21] >> 5 | buffer[22] << 3) & 0x07FF), minIn, maxIn, minOut, maxOut);
    }
    else
    { //Failsave Condition

    }
    applyChanges();
    vTaskDelay(10 / portTICK_PERIOD_MS); // wait for one second
  }
}

ISR(TIMER5_OVF_vect) //Wenn Timer ausgelößt wurde, wurde für 10ms nicht gesendet. Syncronisierung!
{
  TCNT5 = 2786;
  feedState = 0;  
}

ISR(USART3_RX_vect)
{
  TCNT5 = 2786;
  byte dataIn = UDR3;
  switch (feedState)
  {
  case 0:
    if (dataIn == 0x0f) //Data OK
    {
      stateCounter = 0;
      feedState = 1;
      rawBuffer[stateCounter] = dataIn;
      rawBuffer[24] = 0xff;
      stateCounter++;
    }
    break;
  case 1:
    rawBuffer[stateCounter] = dataIn;
    stateCounter++;
    if (stateCounter == 25) //last byte recieved
    {
      stateCounter = 0;
      feedState = 0;
      if (rawBuffer[24] == 0x00) //Packet OK
      {
        _goodFrames++;
        //memcpy(buffer, rawBuffer, 25);
        for (int i = 0; i < 25; i++)
        {
          buffer[i] = rawBuffer[i];
        }
      }
    }
    break;
  }
}
