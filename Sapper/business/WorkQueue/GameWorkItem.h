#pragma once
#include "WorkQueue.h"
#include "GameWorkItemData.h"
#include "WorkItem.h"

class GameWorkItem : public WorkItem
{
public:
	virtual void Work(void* _queue);
	GameWorkItem(GameWorkItemData* ptr);
	~GameWorkItem();

private:
	GameWorkItemData* data;
};
