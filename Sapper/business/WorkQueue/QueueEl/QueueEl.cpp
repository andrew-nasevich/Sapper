#include "QueueEl.h"

QueueEl::QueueEl(WorkItem* _workItem)
{
	next = nullptr;
	workItem = _workItem;
}