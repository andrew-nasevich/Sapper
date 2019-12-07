#pragma once
#include "../WorkItem.h"
class QueueEl
{
public:
	QueueEl(WorkItem* _workItem);

	WorkItem* workItem;

	QueueEl* next;
};

