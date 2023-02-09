#ifndef RECIEVER_HG
#define RECIEVER_HG

#include <Arduino.h>
#include <RH_RF95.h>


void SerialMonitorSetup();
void RecieverTest(RH_RF95 *rf95);
float * ParseBuffer(uint8_t buffer[], float* result, int size);
void PrintBuff(float* buff);

void RF_Task(void* p_arg);


#endif