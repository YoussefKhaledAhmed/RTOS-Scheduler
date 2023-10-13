/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 * \date: 14/10/2023
 * \brief: interface header file of the scheduler
 ******************************************************/

#ifndef INC_RTOS_INTERFACE_H_
#define INC_RTOS_INTERFACE_H_

void RTOS_Start(void);
Std_ReturnType RTOS_CreateTask(uint8_t priority , uint16_t priodicity , void(* Task_Handler)(void));
void RTOS_SuspendTask(uint8_t Task_Id);
void RTOS_ResumeTask(uint8_t Task_Id);
void RTOS_DeleteTask(uint8_t Task_Id);

#endif /* INC_RTOS_INTERFACE_H_ */
