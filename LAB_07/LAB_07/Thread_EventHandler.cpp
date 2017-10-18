/* Thread_EventHandler.cpp */
#include <Windows.h>

#include "Multi_Thread.h"
#include "Task_Queue.hpp"
#include "Task.hpp"

DWORD WINAPI Thread_TaskHandler(LPVOID pParam)
{
	ThreadParam_Task *pThrdParam;
	Task_Queue *pTask_Q;
	ROLE myRole;
	Task task;
	int maxRound;
	ThreadStatusMonitor *pThrdMon;

	int target_task_gen = 0;
	int myAddr = -1;
	int num_tasks = 0;

	pThrdParam = (ThreadParam_Task *)pParam;
	pTask_Q = pThrdParam->pTask_Q;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	maxRound = pThrdParam->maxRound;
	target_task_gen = pThrdParam->targetTaskGen;
	num_tasks = pThrdParam->num_tasks;
	pThrdMon = pThrdParam->pThrdMon;

		for (int round = 0; round < maxRound; round++)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			task = pTask_Q->deQueue_Task();
			if (task.getTaskId() != -1)
			{
				EnterCriticalSection(&pThrdMon->cs_thrd_mon);
				pThrdMon->taskProcessed[pThrdMon->totalTaskProcessed] = task;
				pThrdMon->totalTaskProcessed++;
				LeaveCriticalSection(&pThrdMon->cs_thrd_mon);
			}
			Sleep(300 + rand() % 500);
		}
	return 0;
}