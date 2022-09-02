#include "ModeSelect.h"
#include <qgridlayout.h>
#include "AdminGUI.h"
#include <qlabel.h>
#include "UserGUI.h"

ModeSelect::ModeSelect(const int& repoType, QWidget* parent) : QWidget{ parent }
{
	if (repoType == 1)
		this->eventsList = std::make_unique<CSVEventsList>();
	else
		this->eventsList = std::make_unique<HTMLEventsList>();

	this->fileRepo = std::make_unique<FileRepository>("file.txt");
	this->valid = std::make_unique<Validator>();
	this->srv = std::make_unique<Service>(*fileRepo.get(), eventsList.get(), *valid.get());

	this->selectedMode = 0;

	this->initGUI();
	this->connectSignalsAndSlots();
}

void ModeSelect::initGUI()
{
	QFont font("Times", 14);

	QGridLayout* layout = new QGridLayout{ this };

	QLabel* label = new QLabel{ "Please choose mode:" };
	label->setFont(font);

	this->adminButton = new QPushButton("Admin Mode");
	this->userButton = new QPushButton("User Mode");
	this->adminButton->setFont(font);
	this->userButton->setFont(font);

	layout->addWidget(label, 1, 1, Qt::AlignCenter);
	layout->addWidget(this->adminButton, 2, 0);
	layout->addWidget(this->userButton, 2, 2);
}

void ModeSelect::connectSignalsAndSlots()
{
	QObject::connect(this, &ModeSelect::selectedModeSignal, this, &ModeSelect::next);
	QObject::connect(this->adminButton, &QPushButton::clicked, this, &ModeSelect::adminHandler);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &ModeSelect::userHandler);
}

void ModeSelect::adminHandler()
{
	this->selectedMode = 1;
	emit selectedModeSignal();
}

void ModeSelect::userHandler()
{
	this->selectedMode = 2;
	emit selectedModeSignal();
}

void ModeSelect::next()
{
	this->hide();

	if (this->selectedMode == 1)
		this->gui = std::make_unique<AdminGUI>(*this->srv.get(), this);
	else
		this->gui = std::make_unique<UserGUI>(*this->srv.get(), this);

	this->gui.get()->show();
}
