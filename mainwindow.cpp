//  Karen EL KHOURY

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
#include <QToolButton>
#include <QHBoxLayout>
#include <QActionGroup>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Canvas * canvas = new Canvas(this);
    canvas->setMinimumSize(800,800);
    this->setCentralWidget(canvas);

    QMenuBar * menubar = this->menuBar();
    QMenu * colorMenu = menubar->addMenu(tr("&Color"));

    auto *colorGroup = new QActionGroup(this);

    canvas->pinkAction = new QAction(QIcon(":pink.png"),tr("Pink"), this);
    canvas->blueAction = new QAction(QIcon(":blue.png"),tr("Blue"), this);

    colorGroup->addAction(canvas->pinkAction);
    colorGroup->addAction(canvas->blueAction);
    connect(colorGroup, &QActionGroup::triggered, canvas, &Canvas::selectColor);

    colorMenu->addAction(canvas->pinkAction);
    colorMenu->addAction(canvas->blueAction);

    canvas->lineAction    = new QAction(QIcon(":line.png"), tr("Line"), this);
    canvas->rectAction    = new QAction(QIcon(":rect.png"), tr("Rectangle"), this);
    canvas->ellipseAction = new QAction(QIcon(":ellipse.png"), tr("Ellipse"), this);

    auto *shapeGroup = new QActionGroup(this);
    shapeGroup->addAction(canvas->lineAction);
    shapeGroup->addAction(canvas->rectAction);
    shapeGroup->addAction(canvas->ellipseAction);

    connect(shapeGroup, &QActionGroup::triggered, canvas, &Canvas::selectShape);

    QMenu * styleMenu = menubar-> addMenu(tr("Style"));
    canvas->solidLine = new QAction (QIcon(":solid.png"),tr("Solid Line") , this);
    canvas->dashLine = new QAction (QIcon(":dash.png"),tr("Dash Line") , this);
    canvas->dotLine = new QAction (QIcon(":dot.png"),tr("Dot Line"), this);
    QActionGroup *styleGroup = new QActionGroup(this);
    styleGroup->setExclusive(true);
    styleGroup->addAction(canvas->solidLine);
    styleGroup->addAction(canvas->dashLine);
    styleGroup->addAction(canvas->dotLine);

    connect(styleGroup, &QActionGroup::triggered,canvas, &Canvas::selectStyle);
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
    canvas->lineAction = new QAction(QIcon(":line.png"),tr("Line"), this);
    canvas->rectAction = new QAction(QIcon(":rect.png"),tr("Rectangle"), this);
    canvas->ellipseAction = new QAction(QIcon(":ellipse.png"),tr("Ellipse"), this);

    connect(canvas->lineAction,    &QAction::triggered, [=]{ canvas->selectShape(canvas->lineAction); });
    connect(canvas->rectAction,    &QAction::triggered, [=]{ canvas->selectShape(canvas->rectAction); });
    connect(canvas->ellipseAction, &QAction::triggered, [=]{ canvas->selectShape(canvas->ellipseAction); });

    shapeMenu->addAction(canvas->lineAction);
    shapeMenu->addAction(canvas->rectAction);
    shapeMenu->addAction(canvas->ellipseAction);

    QAction *selectAction = new QAction(QIcon(":select.png"), tr("Select Shape"), this);
    selectAction->setCheckable(true);

    connect(selectAction, &QAction::triggered, canvas, &Canvas::setSelect);


    QToolBar *toolbar = addToolBar(tr("Tools"));
    toolbar->addAction(selectAction);

    toolbar->addSeparator();

    QAction *pinkToolAction = toolbar->addAction(QIcon(":pink.png"), tr("Pink"));
    pinkToolAction->setToolTip("Select Pink color");
    connect(pinkToolAction, &QAction::triggered, [=]{ canvas->selectColor(canvas->pinkAction); });

    QAction *blueToolAction = toolbar->addAction(QIcon(":blue.png"), tr("Blue"));
    blueToolAction->setToolTip("Select Blue color");
    connect(blueToolAction, &QAction::triggered, [=]{ canvas->selectColor(canvas->blueAction); });

    toolbar->addSeparator();

    QAction *lineToolAction = toolbar->addAction(QIcon(":line.png"), tr("Line"));
    lineToolAction->setToolTip("Draw Line");
    connect(lineToolAction, &QAction::triggered, [=]{ canvas->selectShape(canvas->lineAction); });

    QAction *rectToolAction = toolbar->addAction(QIcon(":rect.png"), tr("Rectangle"));
    rectToolAction->setToolTip("Draw Rectangle");
    connect(rectToolAction, &QAction::triggered, [=]{ canvas->selectShape(canvas->rectAction); });

    QAction *ellipseToolAction = toolbar->addAction(QIcon(":ellipse.png"), tr("Ellipse"));
    ellipseToolAction->setToolTip("Draw Ellipse");
    connect(ellipseToolAction, &QAction::triggered, [=]{ canvas->selectShape(canvas->ellipseAction); });

    toolbar->addSeparator();

    QAction *solidToolAction = toolbar->addAction(QIcon(":solid.png"), tr("Solid Line"));
    solidToolAction->setToolTip("Solid Line");
    connect(solidToolAction, &QAction::triggered, [=]{ canvas->selectStyle(canvas->solidLine); });

    QAction *dashToolAction = toolbar->addAction(QIcon(":dash.png"), tr("Dashed Line"));
    dashToolAction->setToolTip("Dashed Line");
    connect(dashToolAction, &QAction::triggered, [=]{ canvas->selectStyle(canvas->dashLine); });

    QAction *dotToolAction = toolbar->addAction(QIcon(":dot.png"), tr("Dotted Line"));
    dotToolAction->setToolTip("Dotted Line");
    connect(dotToolAction, &QAction::triggered, [=]{ canvas->selectStyle(canvas->dotLine); });

    toolbar->addSeparator();

    QSpinBox *widthBoxToolbar = new QSpinBox(this);
    widthBoxToolbar->setRange(2, 20);
    widthBoxToolbar->setValue(5);
    widthBoxToolbar->setToolTip("Change line width");
    toolbar->addWidget(widthBoxToolbar);
    connect(widthBoxToolbar, SIGNAL(valueChanged(int)), canvas, SLOT(selectWidth(int)));

    //partie QT Designer optonelle

    connect(ui->sliderWidth, &QSlider::valueChanged,
            canvas, &Canvas::selectWidth);
    ui->comboShape->addItem("Line");
    ui->comboShape->addItem("Rectangle");
    ui->comboShape->addItem("Ellipse");


    connect(ui->comboShape, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [=](int index){
                if(index == 0) canvas->selectShape(canvas->lineAction);
                else if(index == 1) canvas->selectShape(canvas->rectAction);
                else if(index == 2) canvas->selectShape(canvas->ellipseAction);
            });



    connect(ui->btnSolid, &QPushButton::clicked, [=]{
        canvas->selectStyle(canvas->solidLine);
    });
    connect(ui->btnDash, &QPushButton::clicked, [=]{
        canvas->selectStyle(canvas->dashLine);
    });
    connect(ui->btnDot, &QPushButton::clicked, [=]{
        canvas->selectStyle(canvas->dotLine);
    });

    ui->btnSolid->setIcon(QIcon(":/solid.png"));
    ui->btnSolid->setIconSize(QSize(32,32));

    ui->btnDash->setIcon(QIcon(":/dash.png"));
    ui->btnDash->setIconSize(QSize(32,32));

    ui->btnDot->setIcon(QIcon(":/dot.png"));
    ui->btnDot->setIconSize(QSize(32,32));




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

