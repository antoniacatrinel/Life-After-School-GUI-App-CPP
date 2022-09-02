#pragma once

#include <qwidget.h>
#include <QObject>
#include <qpushbutton.h>
#include "Service.h"
#include <memory>
#include "FileRepository.h"
#include "InmemoryRepository.h"
#include "RepositoryUser.h"
#include "CSVEventsList.h"
#include "HTMLEventsList.h"
#include "Validation.h"
#include "ModeSelect.h"

class ModeSelect : public QWidget
{
	Q_OBJECT

public:
	ModeSelect(const int& repoType, QWidget* parent = nullptr);
	~ModeSelect() = default;

private:
	int selectedMode;
	std::unique_ptr<QWidget> gui;

	std::unique_ptr<RepositoryUser> eventsList;
	std::unique_ptr<FileRepository> fileRepo;
	std::unique_ptr<Validator> valid;
	std::unique_ptr<Service> srv;

	QPushButton* adminButton;
	QPushButton* userButton;

	void initGUI();
	void connectSignalsAndSlots();

	void adminHandler();
	void userHandler();

	void next();

signals:
	void selectedModeSignal();

};
