#pragma once

#include "ModeSelect.h"
#include <qmessagebox.h>
#include <qlistwidget.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <QObject>
#include <qwidget.h>
#include <qshortcut.h>
#include "Service.h"
#include <vector>

class AdminGUI : public QWidget
{
	Q_OBJECT

public:
	AdminGUI(Service& serv, ModeSelect* ms, QWidget* parent = nullptr);
	~AdminGUI() = default;

private:
	Service& srv;
	ModeSelect* modeSelector;

	std::vector<Event> events;
	Event selectedEvent;

	QListWidget* eventsList;

	QLineEdit* title;
	QLineEdit* description;
	QLineEdit* date;
	QLineEdit* time;
	QLineEdit* numberOfPeople;
	QLineEdit* link;

	QLineEdit* filterOperation;

	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;
	QPushButton* modeButton;
	QPushButton* undoButton;
	QPushButton* redoButton;

	QShortcut* undoShortcut;
	QShortcut* redoShortcut;

	void initGUI();
	void connectSignalsAndSlots();

	void populate();
	void displaySelectedEvent();
	int getSelectedIndex();

	void addButtonHandler();
	void deleteButtonHandler();
	void updateButtonHandler();
	void modeButtonHandler();
	void undoButtonHandler();
	void redoButtonHandler();

signals:
	void eventsUpdatedSignal();
	
	void addEventSignal(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);
	void removeEventSignal(const std::string& title, const std::string& date);
	void updateEventSignal(const std::string& oldtitle, const std::string& olddate, const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);
	
	void undoSignal();
	void redoSignal();

public slots:
	void addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);
	void removeEvent(const std::string& title, const std::string& date);
	void updateEvent(const std::string& oldtitle, const std::string& olddate, const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);
	
	void filter(const QString& qstr);
	
	void undo();
	void redo();
};
