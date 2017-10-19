#include "Task_Queue.hpp"

Task_Queue::Task_Queue(ostream& fo) : fout(fo)
{
	//Urgent_Task_Q = T_DLL<Task>();
	//Normal_Task_Q = T_DLL<Task>();
}

Task_Queue::~Task_Queue()
{
	cout << "Deleting Urgent_Task_Q" << endl;
	Urgent_Task_Q.~Urgent_Task_Q();
	cout << "Deleting Normal_Task_Q" << endl;
	Normal_Task_Q.~Normal_Task_Q();
}

void Task_Queue::enQueue_Task(Task t)
{
	if (t.getPriority() <= URGENT_THRESHOLD)
		Urgent_Task_Q.addBack(t);
	else
		Normal_Task_Q.addBack(t);
}

Task Task_Queue::deQueue_Task()
{
	Task tmp(-1,-1);
	if (!Urgent_Task_Q.empty())
	{
		tmp = Urgent_Task_Q.getBack();
		Urgent_Task_Q.removeBack();
	}
	else
	{
		if (!Normal_Task_Q.empty())
		{
			tmp = Normal_Task_Q.getBack();
			Normal_Task_Q.removeBack();
		}
	}
	return tmp;
}

void Task_Queue::print_Task_Queue()
{
	fout << "Urgent_Queue : " << endl;
	Urgent_Task_Q.printDLL(fout, TASKS_PER_LINE);

	fout << "\nNormal_Queue : " << endl;
	Normal_Task_Q.printDLL(fout, TASKS_PER_LINE);
}
