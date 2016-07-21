#ifndef STRINGS_H
#define STRINGS_H
#include "strings.h"
#endif

#include "mainwindow.h"
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QToolBar>

MainWindow::MainWindow()
{
    QAction *aboutAction = new QAction(SkyStrings::appInfo(), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    toolBar = new QToolBar(this);
    toolBar->addAction(aboutAction);
    toolBar->setMovable(false);
    this->addToolBar(toolBar);

    mainFrame = new QWidget;
    layout = new QVBoxLayout(mainFrame);

    controls = new Controls;
    controls->setParent(this);
    controls->setFixedWidth(300);
    controls->show();

    layout->addWidget(controls);

    mainFrame->setLayout(layout);
    setCentralWidget(mainFrame);
    setWindowTitle(SkyStrings::appName());
}

void MainWindow::about()
{
    QMessageBox *message = new QMessageBox;
    message->setText(SkyStrings::info());
    message->show();
}
