/** Task_Queue.h */
#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <string>
#include <iostream>

#include "T_DLL.hpp"
#include "Task.hpp"

#define TASKS_PER_LINE 5

using namespace std;

class Task_Queue
{
public:
	Task_Queue(ostream& fo);
	~Task_Queue();
	void enQueue_Task(Task t);
	Task deQueue_Task();
	void print_Task_Queue(); // print current status of Task_Queue
private:
	ostream& fout;
	T_DLL<Task> Urgent_Task_Q;
	T_DLL<Task> Normal_Task_Q;
};

#endif