#include "AdminGUI.h"

AdminGUI::AdminGUI(Service& serv, ModeSelect* ms, QWidget* parent) : QWidget{ parent }, srv{ serv }, modeSelector{ ms }
{
	this->initGUI();
	this->connectSignalsAndSlots();
	this->populate();
}

void AdminGUI::initGUI()
{
	QFont font("Times", 14);

	// big layout of window
	QVBoxLayout* mainLayout = new QVBoxLayout{ this };

	// at the top -> events list
	QLabel* label = new QLabel{ "Events list:" };
	label->setFont(font);

	this->eventsList = new QListWidget{};
	this->eventsList->setSelectionMode(QAbstractItemView::SingleSelection); // selection mode

	QLinearGradient eventsListGradient(0, 0, 0, this->eventsList->height());
	eventsListGradient.setColorAt(0, Qt::white);
	eventsListGradient.setColorAt(1, Qt::blue);

	QPalette eventsPalette = this->eventsList->palette();
	eventsPalette.setBrush(QPalette::ColorRole::Base, QBrush(eventsListGradient));
	this->eventsList->setPalette(eventsPalette);

	mainLayout->addWidget(label);
	mainLayout->addWidget(this->eventsList);

	// under list of events, display details and menu buttons

	// event details
	QWidget* eventDetailsWidget = new QWidget{};
	QFormLayout* detailsLayout = new QFormLayout{ eventDetailsWidget };

	this->title = new QLineEdit{};
	this->description = new QLineEdit{};
	this->date = new QLineEdit{};
	this->time = new QLineEdit{};
	this->numberOfPeople = new QLineEdit{};
	this->link = new QLineEdit{};

	this->title->setFont(font);
	this->description->setFont(font);
	this->date->setFont(font);
	this->time->setFont(font);
	this->numberOfPeople->setFont(font);
	this->link->setFont(font);

	this->filterOperation = new QLineEdit{};

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

	titleLabel->setFont(font);
	descriptionLabel->setFont(font);
	dateLabel->setFont(font);
	timeLabel->setFont(font);
	peopleLabel->setFont(font);
	linkLabel->setFont(font);

	// add filter
	QLabel* filterLabel = new QLabel{ "&Filter events: " };
	filterLabel->setBuddy(this->filterOperation);
	filterLabel->setFont(font);
	this->filterOperation->setFont(font);
	detailsLayout->addRow(filterLabel, this->filterOperation);

	detailsLayout->addRow(titleLabel, this->title);
	detailsLayout->addRow(descriptionLabel, this->description);
	detailsLayout->addRow(dateLabel, this->date);
	detailsLayout->addRow(timeLabel, this->time);
	detailsLayout->addRow(peopleLabel, this->numberOfPeople);
	detailsLayout->addRow(linkLabel, this->link);

	mainLayout->addWidget(eventDetailsWidget);

	// menu buttons
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* buttonsLayout = new QHBoxLayout{ buttonsWidget };

	this->addButton = new QPushButton("Add event");
	this->deleteButton = new QPushButton("Delete event");
	this->updateButton = new QPushButton("Update event");
	this->modeButton = new QPushButton("Change mode");
	this->undoButton = new QPushButton("Undo");
	this->redoButton = new QPushButton("Redo");

	this->undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
	this->redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);

	this->addButton->setFont(font);
	this->deleteButton->setFont(font);
	this->updateButton->setFont(font);
	this->modeButton->setFont(font);
	this->undoButton->setFont(font);
	this->redoButton->setFont(font);

	buttonsLayout->addWidget(this->addButton);
	buttonsLayout->addWidget(this->deleteButton);
	buttonsLayout->addWidget(this->updateButton);
	buttonsLayout->addWidget(this->modeButton);
	buttonsLayout->addWidget(this->undoButton);
	buttonsLayout->addWidget(this->redoButton);

	mainLayout->addWidget(buttonsWidget);
}


void AdminGUI::connectSignalsAndSlots()
{
	// extra operation
	QObject::connect(filterOperation, &QLineEdit::textChanged, this, &AdminGUI::filter);

	//if an event from the list is selected
	QObject::connect(this->eventsList, &QListWidget::itemSelectionChanged, this, [this]() {this->displaySelectedEvent(); });

	// if list of events is updated, repopulate it from the file
	QObject::connect(this, &AdminGUI::eventsUpdatedSignal, this, &AdminGUI::populate);

	// menu buttons
	QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addButtonHandler);
	QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteButtonHandler);
	QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateButtonHandler);
	QObject::connect(this->modeButton, &QPushButton::clicked, this, &AdminGUI::modeButtonHandler);
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undoButtonHandler);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redoButtonHandler);

	// shortcuts
	QObject::connect(this->undoShortcut, &QShortcut::activated, this, &AdminGUI::undoButtonHandler);
	QObject::connect(this->redoShortcut, &QShortcut::activated, this, &AdminGUI::redoButtonHandler);

	// connect signals to slots
	QObject::connect(this, SIGNAL(addEventSignal(const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)),
		this, SLOT(addEvent(const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)));

	QObject::connect(this, SIGNAL(removeEventSignal(const std::string&, const std::string&)),
		this, SLOT(removeEvent(const std::string&, const std::string&)));

	QObject::connect(this, SIGNAL(updateEventSignal(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)),
		this, SLOT(updateEvent(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&)));

	QObject::connect(this, SIGNAL(undoSignal()), this, SLOT(undo()));

	QObject::connect(this, SIGNAL(redoSignal()), this, SLOT(redo()));

}

void AdminGUI::populate()
{
	QFont font("Times", 14);
	font.setItalic(true);

	this->filterOperation->clear();

	this->events = this->srv.getRepo().getEvents();
	int currentIndex = this->getSelectedIndex();

	// before populating, clear list of it's not empty
	if (this->eventsList->count() > 0)
		this->eventsList->clear();

	for (auto& event : this->events)
	{
		QString newItem = QString::fromStdString(event.getTitle() + ", " + event.getDate());
		QListWidgetItem* item = new QListWidgetItem{ newItem };
		item->setFont(font);
		this->eventsList->addItem(item);
	}

	/*
	// put selection on first event in the list
	if (currentIndex == -1 || this->eventsList->count() == 0)
	{
		this->eventsList->setCurrentRow(0);

		if (this->eventsList->count() > 0)
			this->selectedEvent = this->srv.getRepo().getEvents()[0];
		else
			this->selectedEvent = Event{};
	}
	else
	{
		while (currentIndex >= this->eventsList->count())
			currentIndex--;

		this->eventsList->setCurrentRow(currentIndex);
		this->selectedEvent = this->srv.getRepo().getEvents()[this->getSelectedIndex()];
	}*/
}

void AdminGUI::displaySelectedEvent()
{
	int currentIndex = this->getSelectedIndex();

	// index is invalid -> no event
	if (currentIndex == -1 || currentIndex >= this->events.size())
		return;

	// get current event
	Event e = this->events[currentIndex];
	this->selectedEvent = e;

	this->title->setText(QString::fromStdString(e.getTitle()));
	this->description->setText(QString::fromStdString(e.getDescription()));
	this->date->setText(QString::fromStdString(e.getDate()));
	this->time->setText(QString::fromStdString(e.getTime()));
	this->numberOfPeople->setText(QString::fromStdString(std::to_string(e.getNumberOfPeople())));
	this->link->setText(QString::fromStdString(e.getLink()));
}

int AdminGUI::getSelectedIndex()
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

void AdminGUI::addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link)
{
	try {
		this->srv.addEventService(title, description, date, time, numberOfPeople, link);
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

void AdminGUI::removeEvent(const std::string& title, const std::string& date)
{
	try {
		this->srv.deleteEventService(title, date);
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

void AdminGUI::updateEvent(const std::string& oldtitle, const std::string& olddate, const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link)
{
	try {
		this->srv.updateEventService(oldtitle, olddate, title, description, date, time, numberOfPeople, link);
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

void AdminGUI::undo()
{
	try {
		this->srv.undo();
		// emit signal because list of events is updated
		emit eventsUpdatedSignal();
	}
	catch (UndoRedoException& uerr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(uerr.what().c_str());
		error->setWindowTitle("Undo/Redo error!");
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

void AdminGUI::redo()
{
	try {
		this->srv.redo();
		// emit signal because list of events is updated
		emit eventsUpdatedSignal();
	}
	catch (UndoRedoException& rerr)
	{
		QMessageBox* error = new QMessageBox();
		error->setIcon(QMessageBox::Critical);
		error->setText(rerr.what().c_str());
		error->setWindowTitle("Undo/Redo error!");
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

void AdminGUI::addButtonHandler()
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

void AdminGUI::deleteButtonHandler()
{
	// get selected index
	int currentIndex = this->getSelectedIndex();

	if (currentIndex < 0 || currentIndex >= this->srv.getRepo().getRepoSize())
	{
		QMessageBox::critical(this, "Error", "No event was selected!");
		return;
	}

	// get event
	Event ev = this->srv.getRepo().getEvents()[currentIndex];
	emit removeEventSignal(ev.getTitle(), ev.getDate());
}

void AdminGUI::updateButtonHandler()
{
	// read user input
	std::string etitle = this->title->text().toStdString();
	std::string edescription = this->description->text().toStdString();
	std::string edate = this->date->text().toStdString();
	std::string etime = this->time->text().toStdString();
	int enumber = std::stoi(this->numberOfPeople->text().toStdString());
	std::string elink = this->link->text().toStdString();

	emit updateEventSignal(this->selectedEvent.getTitle(), this->selectedEvent.getDate(), etitle, edescription, edate, etime, enumber, elink);
}

void AdminGUI::modeButtonHandler()
{
	this->close();
	this->modeSelector->show();
}

void AdminGUI::undoButtonHandler()
{
	emit undoSignal();
}

void AdminGUI::redoButtonHandler()
{
	emit redoSignal();
}

void AdminGUI::filter(const QString& qstr)
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
	std::vector<Event> filtered = this->srv.filterRepoByTitle(input);

	if (filtered.size() == 0)
		return;

	this->events = filtered;
	for (auto& ev : this->events)
	{
		QString newItem = QString::fromStdString(ev.getTitle() + ", " + ev.getDate());
		QListWidgetItem* item = new QListWidgetItem{ newItem };
		item->setFont(font);
		this->eventsList->addItem(item);
	}

	// put selection on first event
	this->eventsList->setCurrentRow(0);
}
