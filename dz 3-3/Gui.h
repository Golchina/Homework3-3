#pragma once

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QFileDialog>

class Gui : public QMainWindow
{
private:
	QString showFileChooseDialog(QFileDialog::AcceptMode acceptMode);
	QTableWidget* database;
	QPushButton* addButton;
	QPushButton* saveButton;

	void initialize();
	void databaseStart();

private slots:
	void addSlot();
	void saveSlot();

public:
	Gui(int width, int height);
	~Gui();
};