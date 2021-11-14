#include "serialRemote.h"

ISR(TIMER5_OVF_vect) //Wenn Timer ausgelößt wurde, wurde für 10ms nicht gesendet. Syncronisierung!
{
  TCNT5 = 0;
  feedState = 0;
}

ISR(USART3_RX_vect)
{
  TCNT5 = 49536;
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
          memcpy(buffer, rawBuffer, 25);
          newData = 1;
        }
      }
      break;
  }
}

void initRxProcessing()
{
    UBRR3L = 9; // UART3 - 8E2 - 100000 Baud 
    UCSR3B |= (1 << RXCIE3) | (1 << RXEN3);
    UCSR3C |= (1 << UPM31) | (1 << USBS3) | (1 << UCSZ31) | (1 << UCSZ30);

    TCCR5A = 0;
    TCCR5B = 0;
    TCCR5C = 0;  
    TCNT5 = 49536;
    TCCR5B |= (1<<CS50);
    TIMSK5 |= (1<<TOIE5);
    stateCounter    = 0;
    feedState       = 0;
    xTaskCreate(rxProcessing, "RX", 128, NULL, 0, NULL); //Bearbeitung des neuen Daten
}

long mapper(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void rxProcessing(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    if (newData == 1)
    {
      newData = 0;
      _goodFrames++;
      rxDataIn[0]  = mapper(((buffer[1] || buffer[2] << 8) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[1]  = mapper(((buffer[2] >> 3 | buffer[3] << 5) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[2]  = mapper(((buffer[3] >> 6 | buffer[4] << 2 | buffer[5] << 10) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[3]  = mapper(((buffer[5] >> 1 | buffer[6] << 7) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[4]  = mapper(((buffer[6] >> 4 | buffer[7] << 4) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[5]  = mapper(((buffer[7] >> 7 | buffer[8] << 1 | buffer[9] << 9) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[6]  = mapper(((buffer[9] >> 2 | buffer[10] << 6) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[7]  = mapper(((buffer[10] >> 5 | buffer[11] << 3) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[8]  = mapper(((buffer[12]   | buffer[13] << 8) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[9]  = mapper(((buffer[13] >> 3 | buffer[14] << 5) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[10] = mapper(((buffer[14] >> 6 | buffer[15] << 2 | buffer[16] << 10) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[11] = mapper(((buffer[16] >> 1 | buffer[17] << 7) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[12] = mapper(((buffer[17] >> 4 | buffer[18] << 4) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[13] = mapper(((buffer[18] >> 7 | buffer[19] << 1 | buffer[20] << 9) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[14] = mapper(((buffer[20] >> 2 | buffer[21] << 6) & 0x07FF), minIn, maxIn, minOut, maxOut);
      rxDataIn[15] = mapper(((buffer[21] >> 5 | buffer[22] << 3) & 0x07FF), minIn, maxIn, minOut, maxOut);

      //((buffer[23])      && 0x0001) ? rxDataIn[16] = 255 : rxDataIn[16] = 0;
      //((buffer[23] >> 1) && 0x0001) ? rxDataIn[17] = 255 : rxDataIn[17] = 0;

    }
    vTaskDelay(10 / portTICK_PERIOD_MS ); // wait for one second

  }
}