#include <FreeRTOS.h>
#include <task.h>
#include <Arduino.h>

#include "reciever.cpp"
#include "SourDough_Cellular.cpp"
#include "../lib/common.c"


void setup(){

     Serial.begin(115200); 

    TaskHandle_t cellularTask;
    TaskHandle_t rfTask;
    xMessageBuffer = Message_Buffer_Create_25byte();
    cellularEventGroup = EventGroupCreate();
//Create component tasks
//CORE 0:

   xTaskCreatePinnedToCore(
                   &Cellular_Task,   /* Task function. */
                   "GPS Task",     /* name of task. */
                   10240,       /* Stack size of task */
                   NULL,        /* parameter of the task */
                   10,           /* priority of the task */
                   &cellularTask,      /* Task handle to keep track of created task */
                   0);          /* pin task to core 1 */ 
//    xTaskCreatePinnedToCore(
//                    &RF_Task,   /* Task function. */
//                    "RF Task",     /* name of task. */
//                    10240,       /* Stack size of task */
//                    NULL,        /* parameter of the task */
//                    10,           /* priority of the task */
//                    &rfTask,      /* Task handle to keep track of created task */
//                    0);          /* pin task to core 1 */
   

}

void loop(){
    delay(10);
}

//    My_timer = timerBegin(0, 80, true);
//    timerAttachInterrupt(My_timer, &onTimer, true);
//    timerAlarmWrite(My_timer, 10 * 1000000, true);  