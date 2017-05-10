/*
 * MainWindow.cpp
 *
 */
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>
#include<stdlib.h>
#include<list>
using std::list;

#include "MainWindow.h"
#include "ModulationAndAudio.h"
#include "GLprimitives.h"
#include "AMCarrier.h"
#include "Gasket.h"
#include "TemporalSignal.h"
#include<QtGui>
#include<QApplication>
#include <fstream>
#include<math.h>
using namespace std;

const int MAX_CHARS_PER_LINE = 512;

MainWindow::MainWindow() {
	
    widget = new QWidget;
    setCentralWidget(widget);

    textEdit = new QTextEdit();
    glObject = new GLprimitives;
    amCarrier = new AMCarrier;
    gasket = new Gasket(this);
    temporalSignal = new TemporalSignal;

	createActions();	// Create actions to the menu items
	createMenu();	// Create menu
	createToolBar(); // Create tool bar

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createDockWindow(amCarrier),0,0);
    grid->addWidget(createGroupOne(),0,1);
    grid->addWidget(createGroupTwo(),0,2);

    widget->setLayout(grid);
    resize(800, 800);
	setWindowTitle(tr("Software Radio"));
	
}

QGroupBox *MainWindow::createGroupOne() {
    QGroupBox *glObjectGroupBox = new QGroupBox("globject   ");

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addWidget(glObject,0,0,1,3);
    gridlayout->addWidget(amCarrier,1,0);
    glObjectGroupBox->setLayout(gridlayout);
    return glObjectGroupBox;
}

QGroupBox *MainWindow::createGroupTwo() {
    QGroupBox *glObjectGroupBox = new QGroupBox(tr(""));

    QGridLayout *gridlayout = new QGridLayout;
    gridlayout->addWidget(textEdit,0,0);
    gridlayout->addWidget(gasket,1,0);
    gridlayout->addWidget(temporalSignal,2,0);
    glObjectGroupBox->setLayout(gridlayout);
    return glObjectGroupBox;
}

void MainWindow::newFile() {
    textEdit->clear();
}

void MainWindow::open() {
    openfileurl = QFileDialog::getOpenFileName();
	if (openfileurl.isEmpty())
		return;
	QFile file(openfileurl);
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		url = openfileurl;
        textEdit->setPlainText(QString::fromUtf8(file.readAll()));
	}
    readFileAndUpdateGL();
}

void MainWindow::readFileAndUpdateGL() {

    QFile file(url);
    int numberOfSamples =0 ;
    int lineNumber = 0;
    int maxValue = 0;
    list<int> sampleValues;
    bool invalidFile = false;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QTextStream in(&file);
        in.seek(0);
        while (!in.atEnd()) {
            lineNumber++;
            QString line = in.readLine();
            QStringList list = line.split(" ", QString::SkipEmptyParts);

            if(lineNumber == 1) {
                   QString str("S2");
                   if(line.compare(str)!=0) {
                       invalidFile = true;
                       break;
                   }
            }

            if(lineNumber == 5) {
                numberOfSamples = list.at(0).toInt();
                maxValue = abs(list.at(1).toInt());
            }
            if(lineNumber == 6) {
                for(int i=0;(i<numberOfSamples&& i<list.size());i++){
                    int value = list.at(i).toInt();
                    if(value<=maxValue)
                        sampleValues.push_back(value);
                }
            }
        }
        file.close();
        temporalSignal->renderTemporalSignal(sampleValues,maxValue,numberOfSamples);
}

 void MainWindow::save() {
    if (url.isEmpty()) {
		url = QFileDialog::getSaveFileName();
	}
	QFile file(url);
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		file.write(textEdit->toPlainText().toUtf8());
    }
    file.close();
    readFileAndUpdateGL();

}

void MainWindow::undo() {
    QTextDocument *document = textEdit->document();
    document->undo();
}
void MainWindow::redo() {
    QTextDocument *document = textEdit->document();
    document->redo();
}
void MainWindow::cut() {
    textEdit->cut();
}
void MainWindow::copy() {
    textEdit->copy();
}
void MainWindow::paste() {
    textEdit->paste();
}
void MainWindow::about() {

	QMessageBox::about(this,tr("About Software Radio"),
			tr("<font color='red'><b>Application In progress</b></font><br> "
			"<i>The interface enables control of the radio such as modulation"
			"station, and volume, as well as bass settings, treble settings, stereo, etc."
			"It also allows loading music files from several sources and"
			"listening to the audio as well as saving music to the computer. Finally, it enables a visual display"
			"including a view pleasant images such as animations and illustrations</i>"));

}

void MainWindow::createActions() {

	newAction = new QAction(QIcon(":/images/new.png"), tr("&New"),this);
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("create new file"));
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile())); // Connects new Action to the method newFile()

	openAction = new QAction(tr("&Open"), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("open file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));	// Connects open action to the method open()

	saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save..."), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save file"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));	// Connects save action to the method save()

	quitAction = new QAction(tr("&Quit"), this);
	quitAction->setStatusTip(tr("Quit file"));
	quitAction->setShortcut(QKeySequence::Quit);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));	// Connects quit action to the method close()

	undoAction = new QAction(QIcon(":/images/undo.png"), tr("&Undo"), this);
	undoAction->setShortcuts(QKeySequence::Undo);
	undoAction->setStatusTip(tr("Undo the last operation"));
	connect(undoAction, SIGNAL(triggered()), this, SLOT(undo()));	// Connects undo action to the method undo()

	redoAction = new QAction(tr("&Redo"), this);
	redoAction->setShortcuts(QKeySequence::Redo);
	redoAction->setStatusTip(tr("Redo the last operation"));
	connect(redoAction, SIGNAL(triggered()), this, SLOT(redo()));	// Connects redo action to the method redo()

	cutAction = new QAction(tr("&Cut"), this);
	cutAction->setShortcuts(QKeySequence::Cut);
	cutAction->setStatusTip(tr("Cut the contents"));
	connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));	// Connects cut action to the method cut()

	copyAction = new QAction(tr("&Copy"), this);
	copyAction->setShortcuts(QKeySequence::Copy);
	copyAction->setStatusTip(tr("Copy the current selection's contents"));
	connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));	// Connects copy action to the method copy()

	pasteAction = new QAction(tr("&Paste"), this);
	pasteAction->setShortcuts(QKeySequence::Paste);
	pasteAction->setStatusTip(tr("Paste the clipboard's contents"));
	connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));	// Connects paste action to the method paste()

	aboutAction = new QAction(tr("About"), this);
	aboutAction->setStatusTip(tr("Details about the software radio"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));	// Connects about action to the method about()

}
void MainWindow::createMenu() {
	fileMenu = menuBar()->addMenu("&File");
	editMenu = menuBar()->addMenu("&Edit");
	helpMenu = menuBar()->addMenu("&Help");

	//Add actions to the fileMenu
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(quitAction);

	//Add actions to the editMenu
	editMenu->addAction(undoAction);
	editMenu->addAction(redoAction);
	editMenu->addSeparator();
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);

	viewMenu = menuBar()->addMenu(tr("&View"));
	//Add action to the helpMenu
	helpMenu->addAction(aboutAction);

}

QDockWidget *MainWindow::createDockWindow(AMCarrier *amCarrier) {
	QDockWidget *dockWidget = new QDockWidget;
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
	                                 Qt::RightDockWidgetArea);
	ModulationAndAudio *modulationAndAudioSettings = new ModulationAndAudio(dockWidget);
	modulationAndAudioSettings->setAMCarrier(amCarrier);
	dockWidget->setWidget(modulationAndAudioSettings);	// Adds the ModulationAndAudioSettings widget to the dock window
	dockWidget->setWindowTitle(tr("Radio Settings"));
	addDockWidget(Qt::LeftDockWidgetArea,dockWidget);
	viewMenu->addAction(dockWidget->toggleViewAction());
    return dockWidget;
}

void MainWindow::createToolBar() {
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(newAction);
	fileToolBar->addAction(saveAction);
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(undoAction);

}

