#pragma once

#include "EventsListModel.h"
#include "service.h"
#include <qtableview.h>
#include <qmessagebox.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <QObject>
#include <qwidget.h>
#include <qlistwidget.h>
#include <QObject>
#include "ModeSelect.h"

class UserGUI : public QWidget
{
	Q_OBJECT

public:
	UserGUI(Service& serv, ModeSelect* ms, QWidget* parent = nullptr);
	~UserGUI() = default;

private:
	Service& srv;
	ModeSelect* modeSelector;

	std::vector<Event> userEvents;
	Event selectedEvent;
	QListWidget* eventsList;

	QWidget* tableWidget;
	EventsListModel* eventsTableModel;
	QTabWidget* newTabWidget;
	QTableView* tableView;

	QLineEdit* monthToParse;

	QLineEdit* title;
	QLineEdit* description;
	QLineEdit* date;
	QLineEdit* time;
	QLineEdit* numberOfPeople;
	QLineEdit* link;

	QPushButton* deleteButton;
	QPushButton* listAllButton;
	QPushButton* viewTableButton;
	QPushButton* openInAppButton;
	QPushButton* modeButton;

	QPushButton* addButton;
	QPushButton* nextButton;
	QPushButton* exitParseButton;

	void populate();
	void initGUI();
	void connectSignalsAndSlots();

	int getSelectedIndex();
	void displaySelectedEvent();

	void deleteButtonHandler();
	void listAllButtonHandler();
	void viewTableButtonHandler();
	void openInAppButtonHandler();
	void modeButtonHandler();

	void addButtonHandler();
	void nextButtonHandler();
	void exitButtonHandler();

signals:
	void eventsUpdatedSignal();

	void addEventSignal(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);
	void removeEventSignal(const std::string& title, const std::string& date);

public slots:
	void parseEvents(const QString& qstr);
	void addEvent(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int numberOfPeople, const std::string& link);
	void removeEvent(const std::string& title, const std::string& date);
};
