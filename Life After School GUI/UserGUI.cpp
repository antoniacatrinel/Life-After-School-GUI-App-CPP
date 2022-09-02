#include "UserGUI.h"

UserGUI::UserGUI(Service& serv, ModeSelect* ms, QWidget* parent) : QWidget{ parent }, srv{ serv }, modeSelector{ ms }
{
	this->eventsTableModel = new EventsListModel{ this->srv.getUserRepo() };
	this->initGUI();
	this->connectSignalsAndSlots();
}

void UserGUI::populate()
{
	QFont font("Times", 14);
	font.setItalic(true);

	this->userEvents = this->srv.getUserRepo()->getUserEvents();
	int currentIndex = this->getSelectedIndex();

	// before populating, clear list of it's not empty
	if (this->eventsList->count() > 0)
		this->eventsList->clear();

	for (auto& event : this->userEvents)
	{
		QString newItem = QString::fromStdString(event.getTitle() + ", " + event.getDate());
		QListWidgetItem* item = new QListWidgetItem{ newItem };
		item->setFont(font);
		this->eventsList->addItem(item);
	}
}

void UserGUI::initGUI()
{
	QFont font("Times", 14);

	QHBoxLayout* bigLayout = new QHBoxLayout{ this };
	this->newTabWidget = new QTabWidget{ this };
	this->newTabWidget->setFont(font);

	// First window -> application window
	QWidget* firstWindow = new QWidget{};
	// big layout of window
	QVBoxLayout* firstWindowLayout = new QVBoxLayout{ firstWindow };

	// at the top -> user events list
	QLabel* label = new QLabel{ "Your list of events:" };
	label->setFont(font);

	this->eventsList = new QListWidget{};
	this->eventsList->setSelectionMode(QAbstractItemView::SingleSelection); // selection mode

	firstWindowLayout->addWidget(label);
	firstWindowLayout->addWidget(this->eventsList);

	// under list of events, display details and menu buttons
	// event details
	QWidget* eventDetailsWidget = new QWidget{};
	QFormLayout* detailsLayout = new QFormLayout{ eventDetailsWidget };

	// month for parsing
	this->monthToParse = new QLineEdit{};

	this->title = new QLineEdit{};
	this->description = new QLineEdit{};
	this->date = new QLineEdit{};
	this->time = new QLineEdit{};
	this->numberOfPeople = new QLineEdit{};
	this->link = new QLineEdit{};

	this->monthToParse->setFont(font);
	this->title->setFont(font);
	this->description->setFont(font);
	this->date->setFont(font);
	this->time->setFont(font);
	this->numberOfPeople->setFont(font);
	this->link->setFont(font);

	QLabel* monthLabel = new QLabel{ "&Month to parse: " };
	monthLabel->setBuddy(this->monthToParse);

	QLabel* titleLabel = new QLabel{ "&Event title: " };
	titleLabel->setBuddy(this->title);

	QLabel* descriptionLabel = new QLabel{ "&Event description: " };
	descriptionLabel->setBuddy(this->description);

	QLabel* dateLabel = new QLabel{ "&Event date: " };
	dateLabel->setBuddy(this->date);

	QLabel* timeLabel = new QLabel{ "&Event time: " };
	timeLabel->setBuddy(this->time);

	QLabel* peopleLabel = new QLabel{ "&Event number of people: " };
	peopleLabel->setBuddy(this->numberOfPeople);

	QLabel* linkLabel = new QLabel{ "&Event link: " };
	linkLabel->setBuddy(this->link);

	monthLabel->setFont(font);
	titleLabel->setFont(font);
	descriptionLabel->setFont(font);
	dateLabel->setFont(font);
	timeLabel->setFont(font);
	peopleLabel->setFont(font);
	linkLabel->setFont(font);

	detailsLayout->addRow(monthLabel, this->monthToParse);
	detailsLayout->addRow(titleLabel, this->title);
	detailsLayout->addRow(descriptionLabel, this->description);
	detailsLayout->addRow(dateLabel, this->date);
	detailsLayout->addRow(timeLabel, this->time);
	detailsLayout->addRow(peopleLabel, this->numberOfPeople);
	detailsLayout->addRow(linkLabel, this->link);

	firstWindowLayout->addWidget(eventDetailsWidget);

	// menu buttons
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* buttonsLayout = new QHBoxLayout{ buttonsWidget };

	this->deleteButton = new QPushButton("Delete event");
	this->listAllButton = new QPushButton("List your events");
	this->viewTableButton = new QPushButton("View table");
	this->openInAppButton = new QPushButton("Open events");
	this->modeButton = new QPushButton("Change mode");

	QWidget* additionalButtonsWidget = new QWidget{};
	QHBoxLayout* buttonsLayout2 = new QHBoxLayout{ additionalButtonsWidget };

	this->addButton = new QPushButton("Add event");
	this->nextButton = new QPushButton("Next");
	this->exitParseButton = new QPushButton("Exit");

	this->deleteButton->setFont(font);
	this->listAllButton->setFont(font);
	this->viewTableButton->setFont(font);
	this->openInAppButton->setFont(font);
	this->modeButton->setFont(font);

	this->addButton->setFont(font);
	this->nextButton->setFont(font);
	this->exitParseButton->setFont(font);

	buttonsLayout->addWidget(this->deleteButton);
	buttonsLayout->addWidget(this->listAllButton);
	buttonsLayout->addWidget(this->viewTableButton);
	buttonsLayout->addWidget(this->openInAppButton);
	buttonsLayout->addWidget(this->modeButton);

	buttonsLayout2->addWidget(this->addButton);
	buttonsLayout2->addWidget(this->nextButton);
	buttonsLayout2->addWidget(this->exitParseButton);

	firstWindowLayout->addWidget(buttonsWidget);
	firstWindowLayout->addWidget(additionalButtonsWidget);

	// second window -> events Table Model
	this->tableWidget = new QWidget{};
	QHBoxLayout* secondWindowLayout = new QHBoxLayout{ this->tableWidget };

	this->tableView = new QTableView(this->tableWidget);
	this->tableView->setModel(this->eventsTableModel);

	this->tableView->resizeColumnsToContents();
	this->tableView->resizeRowsToContents();

	secondWindowLayout->addWidget(this->tableView);

	// add the tabs
	this->newTabWidget->addTab(firstWindow, "Events");
	//this->newTabWidget->addTab(secondWindow, "Events you're interested in");
	bigLayout->addWidget(this->newTabWidget);
}

void UserGUI::connectSignalsAndSlots()
{
	QObject::connect(this->modeButton, &QPushButton::clicked, this, &UserGUI::modeButtonHandler);

	//if an event from the list is selected
	QObject::connect(this->eventsList, &QListWidget::itemSelectionChanged, this, [this]() {this->displaySelectedEvent(); });

	// if list of events is updated, repopulate it from the file
	QObject::connect(this, &UserGUI::eventsUpdatedSignal, this, &UserGUI::populate);

	// menu buttons
	QObject::connect(this->monthToParse, &QLineEdit::textChanged, this, &UserGUI::parseEvents);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &UserGUI::deleteButtonHandler);
	QObject::connect(this->listAllButton, &QPushButton::clicked, this, &UserGUI::listAllButtonHandler);
	QObject::connect(this->viewTableButton, &QPushButton::clicked, this, &UserGUI::viewTableButtonHandler);
	QObject::connect(this->openInAppButton, &QPushButton::clicked, this, &UserGUI::openInAppButtonHandler);
	QObject::connect(this->modeButton, &QPushButton::clicked, this, &UserGUI::modeButtonHandler);

	QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addButtonHandler);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &UserGUI::nextButtonHandler);
	QObject::connect(this->exitParseButton, &QPushButton::clicked, this, &UserGUI::exitButtonHandler);

	// connect signals to slots
	QObject::connect(this, SIGNAL(addEventSignal(const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)),
		this, SLOT(addEvent(const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)));

	QObject::connect(this, SIGNAL(removeEventSignal(const std::string&, const std::string&)),
		this, SLOT(removeEvent(const std::string&, const std::string&)));
}

void UserGUI::displaySelectedEvent()
{
	int currentIndex = this->getSelectedIndex();

	// index is invalid -> no event
	if (currentIndex == -1 || currentIndex >= this->userEvents.size())
		return;

	// get current event
	Event e = this->userEvents[currentIndex];
	this->selectedEvent = e;

	this->title->setText(QString::fromStdString(e.getTitle()));
	this->description->setText(QString::fromStdString(e.getDescription()));
	this->date->setText(QString::fromStdString(e.getDate()));
	this->time->setText(QString::fromStdString(e.getTime()));
	this->numberOfPeople->setText(QString::fromStdString(std::to_string(e.getNumberOfPeople())));
	this->link->setText(QString::fromStdString(e.getLink()));
	std::string display = std::string("start ").append(e.getLink());
	system(display.c_str());
}

int UserGUI::getSelectedIndex()
{
	// events list is empty
	if (this->eventsList->count() == 0)
		return -1;

	QModelIndexList seletectedIndex = this->eventsList->selectionModel()->selectedIndexes();
	// nothing is selected, clear event fields and return -1
	if (seletectedIndex.size() == 0)
	{
		this->title->clear();
		this->description->clear();
		this->date->clear();
		this->time->clear();
		this->numberOfPeople->clear();
		this->link->clear();
		return -1;
	}
	// return index
	int i = seletectedIndex.at(0).row();
	return i;
}

void UserGUI::parseEvents(const QString& qstr)
{
	QFont font("Times", 14);
	font.setItalic(true);

	std::string input = qstr.toStdString();

	if (input.size() == 0)
	{
		emit eventsUpdatedSignal();
		return;
	}

	this->eventsList->clear();
	std::vector<Event> filtered;
	try {
		filtered = this->srv.parseUserEvents(input);
	}
	catch (ValidatorException& verr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(verr.what().c_str());
		error->setWindowTitle("Input error!");
		error->exec();
	}
	catch (RepositoryException& rerr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(rerr.what().c_str());
		error->setWindowTitle("Repository error!");
		error->exec();
	}

	if (filtered.size() == 0)
		return;

	this->userEvents = filtered;
	for (auto& ev : this->userEvents)
	{
		QString newItem = QString::fromStdString(ev.getTitle() + ", " + ev.getDate());
		QListWidgetItem* item = new QListWidgetItem{ newItem };
		item->setFont(font);
		this->eventsList->addItem(item);
	}

	// put selection on first event
	this->eventsList->setCurrentRow(0);
}

void UserGUI::addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link)
{
	try {
		Event e{ title, description, date, time, numberOfPeople, link };
		this->srv.addEventToUserList(e);
		emit this->eventsTableModel->layoutChanged();
		this->tableView->resizeColumnsToContents();
		this->tableView->resizeRowsToContents();
	}
	catch (ValidatorException& verr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(verr.what().c_str());
		error->setWindowTitle("Input error!");
		error->exec();
	}
	catch (RepositoryException& rerr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(rerr.what().c_str());
		error->setWindowTitle("Repository error!");
		error->exec();
	}
}

void UserGUI::removeEvent(const std::string& title, const std::string& date)
{
	try {
		this->srv.deleteEventUserService(title, date);
		emit this->eventsTableModel->layoutChanged();
		this->tableView->resizeColumnsToContents();
		this->tableView->resizeRowsToContents();
	}
	catch (ValidatorException& verr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(verr.what().c_str());
		error->setWindowTitle("Input error!");
		error->exec();
	}
	catch (RepositoryException& rerr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(rerr.what().c_str());
		error->setWindowTitle("Repository error!");
		error->exec();
	}
	// emit signal because list of events is updated
	emit eventsUpdatedSignal();
}

void UserGUI::deleteButtonHandler()
{
	// get selected index
	int currentIndex = this->getSelectedIndex();

	if (currentIndex < 0 || currentIndex >= this->srv.getUserRepo()->getRepoSize())
	{
		QMessageBox::critical(this, "Error", "No event was selected!");
		return;
	}

	// get event
	Event ev = this->srv.getUserRepo()->getUserEvents()[currentIndex];
	emit removeEventSignal(ev.getTitle(), ev.getDate());
}

void UserGUI::listAllButtonHandler()
{
	this->populate();
}

void UserGUI::viewTableButtonHandler()
{
	if (!this->tableWidget->isVisible())
		this->tableWidget->resize(this->size() / 1.5);

	this->tableWidget->show();
}

void UserGUI::openInAppButtonHandler()
{
	this->srv.getUserRepo()->writeToFile();

	this->srv.getUserRepo()->openInApp();
}

void UserGUI::modeButtonHandler()
{
	if (this->tableWidget->isVisible())
		this->tableWidget->close();

	this->close();
	this->modeSelector->show();
}

void UserGUI::addButtonHandler()
{
	// read user input
	std::string etitle = this->title->text().toStdString();
	std::string edescription = this->description->text().toStdString();
	std::string edate = this->date->text().toStdString();
	std::string etime = this->time->text().toStdString();
	int enumber = std::stoi(this->numberOfPeople->text().toStdString());
	std::string elink = this->link->text().toStdString();

	// add event
	emit addEventSignal(etitle, edescription, edate, etime, enumber, elink);
}

void UserGUI::nextButtonHandler()
{
	int currentIndex = this->getSelectedIndex();
	// index is invalid -> start from beginning again
	if (currentIndex == -1 || currentIndex >= this->userEvents.size())
		this->eventsList->setCurrentRow(0);

	// move selection to next element
	currentIndex++;
	this->eventsList->setCurrentRow(currentIndex);
}

void UserGUI::exitButtonHandler()
{
	this->monthToParse->clear();
	this->eventsList->clear();
}

