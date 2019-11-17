#include "WorkQueue.h"
#include "WorkItem.h"

void WorkQueue::addWorkItem(WorkItem* workItem)
{
	if (first == nullptr)
	{
		first = new QueueEl(workItem);
		last = first;
	}
	else
	{
		last->next = new QueueEl(workItem);
		last = last->next;
	}
}

void WorkQueue::ProcessItems()
{
	QueueEl* currentEl;
	WorkItem* currentWorkItem;

	last = nullptr;

	while (first != nullptr)
	{
		currentEl = first;
		currentWorkItem = first->workItem;
		currentWorkItem->Work(this);

		delete currentWorkItem;

		first = first->next;
		delete currentEl;
	}
}

WorkQueue::WorkQueue()
{
	first = nullptr;
	last = nullptr;
}
