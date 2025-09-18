#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Canvas.h"

#include <QTextEdit>
#include <QToolBar>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Canvas * canvas = new Canvas(this);
    canvas->setMinimumSize(200,200);
    this->setCentralWidget(canvas);

    QMenuBar * menubar = this->menuBar();
    QMenu * colorMenu = menubar->addMenu(tr("&Color"));

    QAction * redAction = new QAction(tr("Red"), this);
    QAction * blueAction = new QAction(tr("Blue"), this);

    connect(redAction,  &QAction::triggered, [=]{ canvas->selectColor(redAction); });
    connect(blueAction, &QAction::triggered, [=]{ canvas->selectColor(blueAction); });


    colorMenu->addAction(redAction);
    colorMenu->addAction(blueAction);

    this->statusBar();


}


MainWindow::~MainWindow()
{
    delete ui;
}

