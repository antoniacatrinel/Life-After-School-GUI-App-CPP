#include "UserRepoSelect.h"
#include <qgridlayout.h>
#include <qlabel.h>
#include "ModeSelect.h"

UserRepoSelect::UserRepoSelect(QWidget* parent) : QWidget{ parent }
{
	this->userRepoType = 0;

	this->initGUI();
	this->connectSignalsAndSlots();
}

void UserRepoSelect::initGUI()
{
	QFont font("Times", 14);

	QGridLayout* layout = new QGridLayout{ this };

	QLabel* welcomeLabel = new QLabel{ "Welcome to Life After School!" };
	welcomeLabel->setFont(font);

	QLabel* label = new QLabel{ "Please choose user repository type:" };
	label->setFont(font);

	this->CSVbutton = new QPushButton("CSV file");
	this->HTMLbutton = new QPushButton("HTML file");
	this->CSVbutton->setFont(font);
	this->HTMLbutton->setFont(font);

	layout->addWidget(welcomeLabel, 0, 1, Qt::AlignCenter);
	layout->addWidget(label, 1, 1, Qt::AlignCenter);
	layout->addWidget(this->CSVbutton, 2, 0);
	layout->addWidget(this->HTMLbutton, 2, 2);
}

void UserRepoSelect::connectSignalsAndSlots()
{
	QObject::connect(this, &UserRepoSelect::userRepoSignal, this, &UserRepoSelect::next);
	QObject::connect(this->CSVbutton, &QPushButton::clicked, this, &UserRepoSelect::CSVHandler);
	QObject::connect(this->HTMLbutton, &QPushButton::clicked, this, &UserRepoSelect::HTMLHandler);
}

void UserRepoSelect::CSVHandler()
{
	this->userRepoType = 1;
	emit userRepoSignal();
}

void UserRepoSelect::HTMLHandler()
{
	this->userRepoType = 2;
	emit userRepoSignal();
}

void UserRepoSelect::next()
{
	this->hide();

	this->gui = std::make_unique<ModeSelect>(this->userRepoType);
	this->gui.get()->show();

	this->close();
}
