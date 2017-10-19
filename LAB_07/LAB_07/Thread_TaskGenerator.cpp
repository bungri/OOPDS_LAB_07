/* Thread_TaskGenenerator.cpp */
#include <Windows.h>
#include "Multi_Thread.h"
#include "Task_Queue.hpp"
#include "Task.hpp"

DWORD WINAPI Thread_TaskGenerator(LPVOID pParam)
{
	ThreadParam_Task *pThrdParam;
	Task_Queue *pTask_Q;
	int myRole;
	THREAD_FLAG *pFlagThreadTerminate;
	int maxRound;
	Task *pTask, new_task;

	int task_id = 0;
	int task_priority = 0;
	int task_gen_count = 0;
	int target_task_gen;
	int myAddr = -1;
	int event_handler_addr;
	int num_tasks = 0;
	ThreadStatusMonitor *pThrdMon;

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
			if (task_gen_count >= target_task_gen)
			{
				if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
					break;
				else {
					Sleep(500);
					continue;
				}
			}
			new_task.setTaskGenAddr(myAddr);
			new_task.setTaskID(round);
			new_task.setTaskPriority(rand() % 10);
			new_task.setTaskGenAddr(myAddr);
			pTask_Q->enQueue_Task(new_task);

			EnterCriticalSection(&pThrdMon->cs_thrd_mon);
			pThrdMon->taskGenerated[pThrdMon->totalTaskGenerated] = new_task;
			pThrdMon->numTaskGenerated++;
			pThrdMon->totalTaskGenerated++;
			LeaveCriticalSection(&pThrdMon->cs_thrd_mon);

			task_gen_count++;
			Sleep(10);
		}
	return 0;
}