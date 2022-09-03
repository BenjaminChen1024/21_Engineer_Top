/**
  ******************************************************************************
  * @file   : System_Tasks.h
  * @brief  : None.
  ****************************************************************************** 
**/
#ifndef _SYSTEM_TASKS_H_
#define _SYSTEM_TASKS_H_

#include "cmsis_os.h"

#ifdef __cplusplus
extern "C"
{
#endif
	
extern TaskHandle_t TopPOST_Handle;

void System_Tasks_Init(void);
	

#ifdef __cplusplus
}
#endif

#endif
