#pragma once
#include "GameWorkItemData.h"
#include "WorkItem.h"
#include "QueueEl/QueueEl.h"

class WorkQueue
{
public:
	WorkQueue();
	void addWorkItem(WorkItem* workItem);
	void ProcessItems();

private:
	QueueEl* first;
	QueueEl* last;
};



