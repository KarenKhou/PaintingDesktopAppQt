#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Canvas.h"

#include <QTextEdit>
#include <QToolBar>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QSpinBox>
#include <QWidgetAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Canvas * canvas = new Canvas(this);
    canvas->setMinimumSize(400,400);
    this->setCentralWidget(canvas);

    QMenuBar * menubar = this->menuBar();
    QMenu * colorMenu = menubar->addMenu(tr("&Color"));


    canvas->pinkAction = new QAction(QIcon(":pink.png"),tr("Pink"), this);
    canvas->blueAction = new QAction(QIcon(":blue.png"),tr("Blue"), this);
    connect(canvas->blueAction,  &QAction::triggered, [=]{ canvas->selectColor(canvas->blueAction); });
    connect(canvas->pinkAction, &QAction::triggered, [=]{ canvas->selectColor(canvas->pinkAction); });
    colorMenu->addAction(canvas->pinkAction);
    colorMenu->addAction(canvas->blueAction);

    QMenu * styleMenu = menubar-> addMenu(tr("Style"));
    canvas->solidLine = new QAction (QIcon(":solid.png"),tr("Solid Line") , this);
    canvas->dashLine = new QAction (QIcon(":dash.png"),tr("Dash Line") , this);
    canvas->dotLine = new QAction (QIcon(":dot.png"),tr("Dot Line"), this);
    connect(canvas->solidLine,  &QAction::triggered, [=]{ canvas->selectStyle(canvas->solidLine); });
    connect(canvas->dashLine,  &QAction::triggered, [=]{ canvas->selectStyle(canvas->dashLine); });
    connect(canvas->dotLine ,  &QAction::triggered, [=]{ canvas->selectStyle(canvas->dotLine ); });
    styleMenu->addAction(canvas->solidLine);
    styleMenu->addAction(canvas->dashLine);
    styleMenu->addAction(canvas->dotLine);


    QMenu * widthMenu = menubar-> addMenu(tr("Width"));
    QSpinBox *widthBox = new QSpinBox(this);
    widthBox->setRange(2, 20);
    widthBox->setValue(5);

    QWidgetAction *spinAction = new QWidgetAction(this);
    spinAction->setDefaultWidget(widthBox);
    widthMenu->addAction(spinAction);

    connect(widthBox, SIGNAL(valueChanged(int)), canvas, SLOT(selectWidth(int)));

    QMenu *shapeMenu = menubar->addMenu(tr("Shape"));
    canvas->lineAction = new QAction(tr("Line"), this);
    canvas->rectAction = new QAction(tr("Rectangle"), this);
    canvas->ellipseAction = new QAction(tr("Ellipse"), this);

    connect(canvas->lineAction,    &QAction::triggered, [=]{ canvas->selectShape(canvas->lineAction); });
    connect(canvas->rectAction,    &QAction::triggered, [=]{ canvas->selectShape(canvas->rectAction); });
    connect(canvas->ellipseAction, &QAction::triggered, [=]{ canvas->selectShape(canvas->ellipseAction); });

    shapeMenu->addAction(canvas->lineAction);
    shapeMenu->addAction(canvas->rectAction);
    shapeMenu->addAction(canvas->ellipseAction);

    QAction *selectAction = new QAction(QIcon(":select.png"), tr("Select Shape"), this);
    selectAction->setCheckable(true);
    shapeMenu->addAction(selectAction);
    connect(selectAction, SIGNAL(triggered()),canvas, SLOT(setSelect()) );







    this->statusBar();


}

void MainWindow::closeEvent(QCloseEvent *event){
    std::cout<<"Quit Clicked"<<std::endl;
    QMessageBox * messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("Confirm Action");
    messageBox->setText("Do you want to continue?");
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox->setDefaultButton(QMessageBox::No);
    int ret = messageBox->exec();
    if (ret == QMessageBox::Yes) {
        event->accept();
        qDebug() << "User clicked YES";
    } else {
        qDebug() << "User clicked NO";
        event->ignore();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

