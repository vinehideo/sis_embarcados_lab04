#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;


typedef struct{
  int time;
  uint8_t led;
}pisca;




void thread1(void *args){
  uint8_t state = 0;
  uint32_t tick;
  pisca *arg = (pisca*)args;
  
  while(1){
    tick = osKernelGetTickCount();
    
    state ^= arg->led;
    LEDWrite(arg->led, state);
    
    osDelayUntil(tick + arg->time);
  } // while
} // thread2



void main(void){
  LEDInit(LED2 | LED1 | LED3 | LED4);

  osKernelInitialize();
  
  pisca p1;
  p1.time=200;
  p1.led=LED1;
  
  pisca p2;
  p2.time=300;
  p2.led=LED2;
  
  pisca p3;
  p3.time=500;
  p3.led=LED3;
  
  pisca p4;
  p4.time=700;
  p4.led=LED4;
  
  osThreadNew(thread1,&p1,NULL);
  osThreadNew(thread1,&p2,NULL);
  osThreadNew(thread1,&p3,NULL);
  osThreadNew(thread1,&p4,NULL);
  

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
