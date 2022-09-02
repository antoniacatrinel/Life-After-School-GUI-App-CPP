#include "EventsListModel.h"

EventsListModel::EventsListModel(RepositoryUser* repo, QObject* parent) : QAbstractTableModel{ parent }, repoUser{ repo }
{
}


int EventsListModel::rowCount(const QModelIndex& parent) const
{
	return repoUser->getRepoSize();
}

int EventsListModel::columnCount(const QModelIndex& parent) const
{
	return 6;
}

QVariant EventsListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	Event e = this->repoUser->getUserEvents()[row];
	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(e.getTitle());
		case 1:
			return QString::fromStdString(e.getDescription());
		case 2:
			return QString::fromStdString(e.getDate());
		case 3:
			return QString::fromStdString(e.getTime());
		case 4:
			return QString::number(e.getNumberOfPeople());
		case 5:
			return QString::fromStdString(e.getLink());
		}
	}
	else
		if (role == Qt::BackgroundRole)
		{
			if (row % 2 == 1)
				return QBrush(QColor(224, 224, 224));
		}
	return QVariant();
}

QVariant EventsListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		switch (section)
		{
		case 0:
			return QString("Title");
		case 1:
			return QString("Description");
		case 2:
			return QString("Date");
		case 3:
			return QString("Time");
		case 4:
			return QString("Number of people");
		case 5:
			return QString("Link");
		default:
			break;
		}
	return QVariant();
}

bool EventsListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid() || role != Qt::EditRole)
		return false;

	int eventsIndex = index.row();
	if (eventsIndex == this->repoUser->getRepoSize())
	{
		this->beginInsertRows(QModelIndex{}, eventsIndex, eventsIndex);

		switch (index.column())
		{
		case 0:
			this->repoUser->addUserEvent(Event{ value.toString().toStdString(), "", "", "", -1, "" });
			break;
		case 1:
			this->repoUser->addUserEvent(Event{ "" , value.toString().toStdString(), "", "", -1, "" });
			break;
		case 2:
			this->repoUser->addUserEvent(Event{ "" , "", value.toString().toStdString(), "", -1, "" });
			break;
		case 3:
			this->repoUser->addUserEvent(Event{ "" , "", "", value.toString().toStdString(), -1, "" });
			break;
		case 4:
			this->repoUser->addUserEvent(Event{ "" , "", "", "", std::stoi(value.toString().toStdString()), "" });
			break;
		case 5:
			this->repoUser->addUserEvent(Event{ "" , "", "", "", -1, value.toString().toStdString() });
			break;
		}

		this->endInsertRows();
		return true;
	}

	Event& currentEvent = this->repoUser->getUserEvents()[eventsIndex];
	Event oldEvent = currentEvent;

	switch (index.column())
	{
	case 0:
		currentEvent.setTitle(value.toString().toStdString());
		break;
	case 1:
		currentEvent.setDescription(value.toString().toStdString());
		break;
	case 2:
		currentEvent.setDate(value.toString().toStdString());
		break;
	case 3:
		currentEvent.setTime(value.toString().toStdString());
		break;
	case 4:
		currentEvent.setNumberOfPeople(std::stoi(value.toString().toStdString()));
		break;
	case 5:
		currentEvent.setLink(value.toString().toStdString());
		break;
	}
	this->repoUser->updateUserEvent(oldEvent, currentEvent);

	emit dataChanged(index, index);
	return true;

}

Qt::ItemFlags EventsListModel::flags(const QModelIndex& index) const
{
	if (index.column() >= 0 and index.column() <= 5)
		return Qt::ItemIsEditable | Qt::ItemIsEnabled;

	return Qt::ItemFlags();
}

