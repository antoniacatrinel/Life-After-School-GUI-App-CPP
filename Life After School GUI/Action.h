#pragma once

#include "Domain.h"
#include "FileRepository.h"

// Classes used for the undo/redo functionality

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

	virtual ~Action() = default;
};

class ActionAdd : public Action
{
private:
	Event addedEvent;
	FileRepository& repo;

public:
	ActionAdd(FileRepository& repo, const Event& event);

	void executeUndo() override;
	void executeRedo() override;
};

class ActionRemove : public Action
{
private:
	Event deletedEvent;
	FileRepository& repo;

public:
	ActionRemove(FileRepository& repo, const Event& event);

	void executeUndo() override;
	void executeRedo() override;
};

class ActionUpdate : public Action
{
private:
	Event oldEvent;
	Event newEvent;
	FileRepository& repo;

public:
	ActionUpdate(FileRepository& repo, const Event& oldEvent, const Event& newEvent);

	void executeUndo() override;
	void executeRedo() override;
};
