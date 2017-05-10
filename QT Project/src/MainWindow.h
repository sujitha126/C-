/*
 * MainWindow.h
 *
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<QMainWindow>
#include<list>
using std::list;

class QAction;
class QActionGroup;
class QMenu;
class QTextEdit;
class QString;
class QToolBar;
class GLprimitives;
class QDockWidget;
class AMCarrier;
class QGroupBox;
class QWidget;
class Gasket;
class TemporalSignal;

class MainWindow:public QMainWindow {

	Q_OBJECT
public:
	MainWindow();

private slots:
	void newFile();
	void open();
	void save();
	void undo();
	void redo();
	void cut();
	void copy();
	void paste();
	void about();

private:
	QDockWidget *createDockWindow(AMCarrier *amCarrier);
    QGroupBox *createGroupOne();
    QGroupBox *createGroupTwo();
	void createMenu();
	void createActions();
	void createToolBar();
    void readFileAndUpdateGL();

    QWidget *widget;
    GLprimitives *glObject;
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *viewMenu;
	QMenu *helpMenu;
	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *quitAction;
	QAction *undoAction;
	QAction *redoAction;
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;
	QAction *aboutAction;
	QTextEdit *textEdit;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
    	QString openfileurl;
	QString url;
	AMCarrier *amCarrier;
    Gasket *gasket;\
    TemporalSignal *temporalSignal;
};

#endif /* MAINWINDOW_H_ */
