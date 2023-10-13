/******************************************************
 * \author: Youssef Khaled Ahmed (558)
 * \date: 14/10/2023
 * \brief: private header file of the scheduler
 ******************************************************/

#ifndef INC_RTOS_PRIVATE_H_
#define INC_RTOS_PRIVATE_H_

/* Task states */
typedef enum{
	RUNING = 1,
	READY,
	SUSPENDED
} TASK_status;

/* task type*/
typedef struct{
	uint16_t priodicity;
	void (* Task_Handler)(void);
	uint16_t Task_cnt;
	TASK_status status;
} TASK_type;

#endif /* INC_RTOS_PRIVATE_H_ */
