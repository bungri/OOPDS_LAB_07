#include "Task.hpp"

//friend operator overloading --------------------------
ostream & operator<<(ostream &output, const Task &tsk)
{
	output << "Task [id(" << setw(2) << tsk.task_id << "), pri(" << setw(2) << tsk.task_priority << ")]";
	return output;
}

//constructors and destructors -------------------------
Task::Task()
{
	this->task_id = 0;
	this->task_priority = 0;
}

Task::Task(int t_id, int t_pri)
{
	this->task_id = t_id;
	this->task_priority = t_pri;
}

Task::~Task()
{
}
