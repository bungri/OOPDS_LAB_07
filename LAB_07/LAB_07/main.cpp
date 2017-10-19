/** Main.cpp */
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <time.h>

#include "SimParams.h"
#include "ConsoleDisplay.h"
#include "T_DLL.hpp"
#include "Task_Queue.hpp"
#include "Multi_Thread.h"

using namespace std;

#define NUM_TASKS 10

DWORD WINAPI Thread_TaskGenerator(LPVOID pParam);
DWORD WINAPI Thread_TaskHandler(LPVOID pParam);

void main()
{
	ThreadParam *pThrTaskHndlrParam, *pThrTaskGenParam;
	CRITICAL_SECTION cs_main;
	HANDLE hThreadTaskGen, hThreadTaskHandler;
	HANDLE consHndlr;
	ThreadStatusMonitor thrdMon;
	THREAD_FLAG taskThreadFlag = RUN;
	InitializeCriticalSection(&cs_main);
	InitializeCriticalSection(&thrdMon.cs_thrd_mon);
	consHndlr = initConsoleHandler();
	srand(time(NULL));
	thrdMon.pFlagThreadTerminate = &taskThreadFlag;

	int numTaskGenerated, numTaskProcessed;
	thrdMon.totalTaskGenerated = 0;
	thrdMon.totalTaskProcessed = 0;
	thrdMon.numTaskGenerated = 0;
	thrdMon.numTaskProcessed = 0;

	Task *pTask, task;
	Task_Queue task_Q(cout);

	/* Create Task Handler Thread */
	EnterCriticalSection(&cs_main);
	cout << "\nCreation of Task Handler Thread in main() .... " << endl;
	LeaveCriticalSection(&cs_main);
	pThrTaskHndlrParam = new ThreadParam;
	pThrTaskHndlrParam->role = TASK_HANDLER;

	pThrTaskHndlrParam->myAddr = 1; // link address
	pThrTaskHndlrParam->pCS_main = &cs_main;
	pThrTaskHndlrParam->pCS_thrd_mon = &thrdMon.cs_thrd_mon;
	pThrTaskHndlrParam->pTask_Q = &task_Q;
	pThrTaskHndlrParam->maxRound = MAX_ROUND;
	pThrTaskHndlrParam->pThrdMon = &thrdMon;

	hThreadTaskHandler = CreateThread(NULL, 0, Thread_TaskHandler, pThrTaskHndlrParam, 0, NULL);

	/* Create Task Generator Thread */
	EnterCriticalSection(&cs_main);
	cout << "\nCreation of Task Generation Thread in main() .... " << endl;
	LeaveCriticalSection(&cs_main);
	pThrTaskGenParam = new ThreadParam;
	pThrTaskGenParam->role = TASK_GENERATOR;

	pThrTaskGenParam->targetTaskGen = NUM_TASKS_PER_GEN;
	pThrTaskGenParam->myAddr = 0; // link address
	pThrTaskGenParam->pCS_main = &cs_main;
	pThrTaskGenParam->pCS_thrd_mon = &thrdMon.cs_thrd_mon;
	pThrTaskGenParam->pTask_Q = &task_Q;
	pThrTaskGenParam->maxRound = MAX_ROUND;
	pThrTaskGenParam->pThrdMon = &thrdMon;

	hThreadTaskGen = CreateThread(NULL, 0, Thread_TaskGenerator, pThrTaskGenParam, 0, NULL);
	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main);
		system("cls");
		gotoxy(consHndlr, 0, 0);
		EnterCriticalSection(&cs_main);
		cout << "Thread monitoring by main() :: round(" << setw(2) << round;
		cout << "), current total_task_gen(" << setw(2) << thrdMon.totalTaskGenerated;
		cout << "), total_task_proc(" << setw(2) << thrdMon.totalTaskProcessed << ")" << endl;
		cout << "Task_Gen generated " << setw(2) << thrdMon.numTaskGenerated << " tasks" << endl;
		cout << "Tasks processed up to now : " << endl;
		numTaskGenerated = thrdMon.totalTaskGenerated;
		for (int tsk = 0; tsk < numTaskGenerated; tsk++)
		{
			task = thrdMon.taskGenerated[tsk];
			if (task.getTaskId() != -1)
			{
				cout << task;
				if (((tsk + 1) % TASKS_PER_LINE) == 0)
					cout << endl;
			}
		}
		cout << endl;
		cout << "Task_Handler processed " << setw(2) << thrdMon.numTaskProcessed << " tasks" << endl;
		cout << "Tasks processed up to now : " << endl;
		numTaskProcessed = thrdMon.totalTaskProcessed;
		for (int tsk = 0; tsk < numTaskProcessed; tsk++)
		{
			task = thrdMon.taskProcessed[tsk];
			if (task.getTaskId() != -1)
			{
				cout << task;
				if (((tsk + 1) % TASKS_PER_LINE) == 0)
					cout << endl;
			}
		}
		cout << endl;
		cout << endl << "============================================" << endl;
		cout << "Tasks in Task_Q::";
		task_Q.print_Task_Queue();
		cout << endl;
		LeaveCriticalSection(&cs_main);
		if (numTaskProcessed >= TOTAL_NUM_TASKS)
		{
			taskThreadFlag = TERMINATE; // set 1 to terminate threads
			break;
		}
		Sleep(100);
	}
	/* Wait until the threads are terminated */
	CloseHandle(hThreadTaskGen);
	CloseHandle(hThreadTaskHandler);
	EnterCriticalSection(&cs_main);
	cout << "Thread Task Generator closed.\n";
	cout << "Thread Task Handler closed.\n";
	cout << "Deleting all critical sections...\n";
	LeaveCriticalSection(&cs_main);
	DeleteCriticalSection(&cs_main);
	delete pThrTaskGenParam;
	delete pThrTaskHndlrParam;
}