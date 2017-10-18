/** Multi_Thread.h */
#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H

#include <Windows.h>
#include "Task.hpp"
#include "Task_Queue.hpp"
#include "SimParams.h"

enum ROLE { TASK_GENERATOR, TASK_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct ThreadStatusMonitor
{
	CRITICAL_SECTION cs_thrd_mon;
	int numTaskGenerated;
	int numTaskProcessed;
	int totalTaskGenerated;
	int totalTaskProcessed;
	Task taskGenerated[TOTAL_NUM_TASKS]; // used for monitoring only
	Task taskProcessed[TOTAL_NUM_TASKS]; // used for monitoring only
	THREAD_FLAG *pFlagThreadTerminate;
}ThreadStatusMonitor;
typedef struct ThreadParam
{
	CRITICAL_SECTION *pCS_main;
	CRITICAL_SECTION *pCS_thrd_mon;
	Task_Queue *pTask_Q;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetTaskGen;
	int num_tasks;
	ThreadStatusMonitor *pThrdMon;
}ThreadParam_Task;

DWORD WINAPI Thread_TaskHandler(LPVOID pParam);
DWORD WINAPI Thread_TaskGenerator(LPVOID pParam);

#endif