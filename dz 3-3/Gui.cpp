#include "Gui.h"
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QTextStream>

Gui::Gui(int width, int height) : QMainWindow()
{
	QDesktopWidget* desktop = QApplication::desktop();

	int deskW = desktop->width();
	int deskH = desktop->height();

	int maxWidth = width > deskW ? deskW : width;
	int maxHeight = height > deskH ? deskH : height;

	int x = deskW / 2 - (width > deskW ? maxWidth : width) / 2;
	int y = deskH / 2 - (height > deskH ? maxHeight : height) / 2;
	this->setGeometry(x, y, width, height);

	this->initialize();
}

void Gui::initialize()
{
	QFrame* centralFrame = new QFrame(this);
	this->setCentralWidget(centralFrame);

	QVBoxLayout* centralframeLayout = new QVBoxLayout(centralFrame);

	QVBoxLayout* tableLayout = new QVBoxLayout;
	tableLayout->setMargin(0);

	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->setMargin(0);

	centralframeLayout->addLayout(tableLayout);
	centralframeLayout->addLayout(buttonsLayout);
	tableLayout->setAlignment(Qt::AlignCenter);
	buttonsLayout->setAlignment(Qt::AlignCenter);

	database =new QTableWidget(5, 3, this);;
	databaseStart();
	tableLayout->addWidget(database);
	database->setFixedWidth(610);	

	addButton = new QPushButton(tr("Add row"));
	buttonsLayout->addWidget(addButton);
	addButton->setFixedWidth(300);
	addButton->setFixedHeight(50);

	addButton->connect(addButton, SIGNAL(clicked()), this, SLOT(addSlot()));

	saveButton = new QPushButton(tr("Save table"));
	buttonsLayout->addWidget(saveButton);
	saveButton->setFixedWidth(300);
	saveButton->setFixedHeight(50);

	saveButton->connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSlot()));

}

void Gui::databaseStart()
{
	QStringList header = { "Name" , "Cost" , "Quantity" };
	database->setHorizontalHeaderLabels(header);
}

void Gui::addSlot()
{
	database->setRowCount(database->rowCount() + 1);
}

QString Gui::showFileChooseDialog(QFileDialog::AcceptMode acceptMode) {
	QFileDialog chooseFileDialog(this);
	chooseFileDialog.setFileMode(acceptMode == QFileDialog::AcceptSave ? QFileDialog::AnyFile : QFileDialog::ExistingFile);
	chooseFileDialog.setNameFilter("Text Files (*.txt)");
	chooseFileDialog.setViewMode(QFileDialog::Detail);
	chooseFileDialog.setAcceptMode(acceptMode);

	if (chooseFileDialog.exec())
	{
		QStringList selectedFiles = chooseFileDialog.selectedFiles();
		if (selectedFiles.size() != 0)
		{
			QString selectedFile = selectedFiles.first();

			return selectedFile;
		}
	}

	return "";
}

void Gui::saveSlot()
{
	QString fileContent;
	for (int i = 1; i < database->rowCount(); i++)
	{
		for (int j = 0; j < database->colorCount(); j++)
		{
			fileContent = fileContent + database->item(i, j)->text();
		}
	}
	
	QString selectedFile = showFileChooseDialog(QFileDialog::AcceptSave);

	if (QString::compare("", selectedFile, Qt::CaseInsensitive) != 0)
	{
		QFile file(selectedFile);

		file.open(QFile::WriteOnly | QFile::Text);

		QTextStream fileStream(&file);

		fileStream << fileContent;

		file.close();
	}
}

Gui::~Gui()
{
}
