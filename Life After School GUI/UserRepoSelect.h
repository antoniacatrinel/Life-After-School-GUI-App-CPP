#pragma once

#include <QObject>
#include <QPushButton>
#include <qwidget.h>

class UserRepoSelect : public QWidget
{
	Q_OBJECT

public:
	UserRepoSelect(QWidget* parent = nullptr);
	~UserRepoSelect() = default;

private:
	int userRepoType;
	std::unique_ptr<QWidget> gui;

	QPushButton* CSVbutton;
	QPushButton* HTMLbutton;

	void initGUI();
	void connectSignalsAndSlots();

	void CSVHandler();
	void HTMLHandler();
	void next();

signals:
	void userRepoSignal();

};
