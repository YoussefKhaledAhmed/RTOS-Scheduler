/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 * \date: 14/10/2023
 * \brief: source file of the scheduler
 ******************************************************/

/* included files */
#include "../Inc/main.h"
#include "../Inc/standardTypes.h"
#include "../Inc/common_macros.h"

#include "../Inc/RTOS_private.h"
#include "../Inc/RTOS_config.h"
#include "../Inc/RTOS_interface.h"

/* customized SysTick init function for the purpose of this *
 * exercise only.                                           */
void USER_SysTickInit(void);

/* Global variables */
/* this variable is externed in the stm32f1xx_it.c to be used in the SysTick_Handler */
uint8_t USER_definedTicks =  TICK_TIME;

/* declaring the System tasks */
static TASK_type TASKS[ TASKS_NUMBERS ] = { { NULL } };


/******************************************************************
 * Service name: RTOS_Start
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: start the SysTick timer
 ******************************************************************/
void RTOS_Start(void){
	USER_SysTickInit();
}

/******************************************************************
 * Service name: RTOS_CreateTask
 *
 * parameter in: uint8_t priority ,
 *               uint16_t priodicity ,
 *               void(* Task_Handler)(void)
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: creating a task according to its priority.
 ******************************************************************/
Std_ReturnType RTOS_CreateTask(uint8_t priority , uint16_t priodicity , void(* Task_Handler)(void)){
	/* Local variable: */
	Std_ReturnType status = RTE_E_OK;

	/* check if the task with the passed priority is available */
	if(TASKS[(uint32_t) priority ].Task_Handler == NULL){
		/* assign the priodicity */
		TASKS[(uint32_t) priority ].priodicity = priodicity;
		/* assign the task handler where the task is implemented */
		TASKS[(uint32_t) priority ].Task_Handler = Task_Handler;
		/* assign the task state to READY */
		TASKS[(uint32_t) priority ].status = READY;
	}
	else
	{
		/* the passed priority isn't available */
		status = RTE_E_NOK;
	}
	/* returning the status whether the function succedded to create  *
	 * a new task or not.                                             */
	return status;
}


/******************************************************************
 * Service name: RTOS_SuspendTask
 *
 * parameter in: uint8_t Task_Id
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: suspending the task by changing its state
 ******************************************************************/
void RTOS_SuspendTask(uint8_t Task_Id){
	TASKS[(uint32_t) Task_Id ].status = SUSPENDED;
}


/******************************************************************
 * Service name: RTOS_ResumeTask
 *
 * parameter in: uint8_t Task_Id
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: resuming the task if it was suspended by changing
 *              its state to READY.
 ******************************************************************/
void RTOS_ResumeTask(uint8_t Task_Id){
	TASKS[(uint32_t) Task_Id ].status = READY;
}

/****************************************************************
 * Service name: RTOS_DeleteTask
 *
 * parameter in: uint8_t Task_Id
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: deleting the task by assigning its handler by 1
 ****************************************************************/
void RTOS_DeleteTask(uint8_t Task_Id){
	TASKS[(uint32_t) Task_Id ].Task_Handler = NULL;
}


/***************************************************************
 * Service name: RTOS_Schedular
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: -Loops over the TASKS and whatever the
 *               ready task it will be executed.
 *              -Externed in the stm32f1xx_it.c file to be
 *               called by the SysTick handler.
 ***************************************************************/
void RTOS_Schedular(void){
	/* Local counter to loop over the tasks */
	uint8_t Tasks_cnt;

	/* loop over the tasks */
	for(Tasks_cnt = 0; Tasks_cnt <TASKS_NUMBERS ; Tasks_cnt++){
		/* if the handler isn't NULL then this task was created and checking on its  *
		 * state too.                                                                */
		if(TASKS[(uint32_t) Tasks_cnt ].Task_Handler != NULL && TASKS[(uint32_t) Tasks_cnt ].status == READY)
		{
			/* if the counter of the task equals its priodicity then reseting the *
			 * counter to its default value which is 1 and execute the task.      */
			if(TASKS[(uint32_t) Tasks_cnt ].Task_cnt == TASKS[(uint32_t) Tasks_cnt ].priodicity){
				/* resetting the task counter to the default value which is 1 */
				TASKS[(uint32_t) Tasks_cnt ].Task_cnt = 1;
				/* calling the task handler */
				TASKS[(uint32_t) Tasks_cnt ].Task_Handler();
			}
			else
			{
				/* increment the task counter */
				TASKS[(uint32_t) Tasks_cnt ].Task_cnt++;
			}
		}
		else
		{
			/* do nothing */
		}
	}
}


/***************************************************************
 * Service name: USER_SysTickInit
 *
 * parameter in: None
 *
 * parameter in/out: None
 *
 * parameter out: None
 *
 * return: void
 *
 * description: initializing the SysTick timer
 ***************************************************************/
void USER_SysTickInit(void){
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
	SysTick->CTRL = (SysTick_CTRL_TICKINT_Msk|
			SysTick_CTRL_ENABLE_Msk|
			SysTick_CTRL_CLKSOURCE_Msk);
}
