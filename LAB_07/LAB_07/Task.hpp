/** Task.h */

#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream>
#include <iomanip>

#define MAX_TASK_PRIORITY 10
#define URGENT_THRESHOLD 4

typedef unsigned int UINT_32;
typedef unsigned char UINT_8;

using namespace std;

class Task
{
	friend ostream& operator<<(ostream&, const Task &);
	// format: Task [id( 1), priority(2)]
public:
	Task(); // default constructor
	Task(int t_id, int t_pri);
	~Task(); // destructor
	int getTaskId() { return task_id; }
	int getPriority() { return task_priority; }
	void setTaskID(int t_id) { task_id = t_id; }
	void setTaskPriority(int pri) { task_priority = pri; }
	void setTaskGenAddr(int genID) { task_gen_addr = genID; }
	void setTaskHandlerAddr(int handlerID) { task_handler_addr = handlerID; }
protected:
	int task_id;
	int task_priority; // Urgent if priority <= URGENT_THRESHOLD, otherwise Normal
	int task_gen_addr;
	int task_handler_addr;
};

#endif