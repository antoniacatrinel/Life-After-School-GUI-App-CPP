#include "Action.h"

ActionAdd::ActionAdd(FileRepository& repo, const Event& event) : repo{ repo }, addedEvent{ event }
{
}

void ActionAdd::executeUndo()
{
	repo.deleteEvent(addedEvent.getTitle(), addedEvent.getDate());
}

void ActionAdd::executeRedo()
{
	repo.addEvent(addedEvent);
}

ActionRemove::ActionRemove(FileRepository& repo, const Event& event) :repo{ repo }, deletedEvent{ event }
{
}

void ActionRemove::executeUndo()
{
	repo.addEvent(deletedEvent);
}

void ActionRemove::executeRedo()
{
	repo.deleteEvent(deletedEvent.getTitle(), deletedEvent.getDate());
}

ActionUpdate::ActionUpdate(FileRepository& repo, const Event& oldEvent, const Event& newEvent) :repo{ repo }, oldEvent{ oldEvent }, newEvent{ newEvent }
{
}

void ActionUpdate::executeUndo()
{
	repo.updateEvent(newEvent, oldEvent);
}

void ActionUpdate::executeRedo()
{
	repo.updateEvent(oldEvent, newEvent);
}
