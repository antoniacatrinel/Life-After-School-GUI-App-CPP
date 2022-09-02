#pragma once

#include <QAbstractTableModel>
#include "RepositoryUser.h"
#include <qcolor.h>
#include <qbrush.h>

class EventsListModel : public QAbstractTableModel
{

private:
	RepositoryUser* repoUser;

public:
	EventsListModel(RepositoryUser* repo, QObject* parent = Q_NULLPTR);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;
};

