//  Karen EL KHOURY

#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QAction>
#include <QColor>

#include "line.h"
#include "rectangle.h"
#include "ellipse.h"


Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    isDrawing(false),
    currentColor(Qt::black),
    currentStyle(Qt::SolidLine),
    currentWidth(5),
    currentShapeType(ShapeType::Line),
    selectOption(false),
    selectedShape(nullptr),
    objectSelected(false)
{}

Canvas::~Canvas(){
    for (auto shape : displayList){
        delete shape;
    }
    displayList.clear();
    currentShape = nullptr;
}

void Canvas::paintEvent(QPaintEvent * paintEvent){
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);

    if (isDrawing && currentShape) {
        currentShape->draw(painter);
    }
    if(selectOption){
        if (selectedShape!=nullptr){
            selectedShape->createSelectionHandles(painter);
        }
    }

    for (auto shape :displayList){
        shape->draw(painter);

    }

}

void Canvas::mousePressEvent(QMouseEvent* mouseEvent){
    qDebug() << "Press at" << mouseEvent->pos();
    qDebug() << "Move at" << mouseEvent->pos()
             << " handleIndex=" << handleIndex
             << " resizing=" << resizing
             << " moving=" << moving;

    if (mouseEvent->button() == Qt::LeftButton) {
            lastPos=mouseEvent->pos();
        if (selectOption){
            for(auto shape : displayList){
                if (shape->contains(mouseEvent->pos())){
                    selectedShape = shape;

                    int h = selectedShape->handleSelected(mouseEvent->pos());
                    if (h != -1) {
                        resizing = true;
                        handleIndex = h;
                        qDebug() << "Resize started on handle" << h;

                    } else {
                        moving = true;
                        lastPos = mouseEvent->pos();
                        qDebug() << "Move started";

                    }


                    objectSelected = true;
                    update();
                    return;
                }
            }
        }else{


        QPen pen;
        pen.setColor(currentColor);
        pen.setStyle(currentStyle);
        pen.setWidth(currentWidth);
        switch(currentShapeType){
            case ShapeType::Line:
                currentShape = new Line(
                    pen,
                    mouseEvent->pos(),
                    mouseEvent->pos()
                    );
                 break;
            case ShapeType::Rectangle:
                currentShape = new Rectangle(
                    pen,
                    mouseEvent->pos(),
                    mouseEvent->pos()
                    );
                 break;
            case ShapeType::Ellipse:
                currentShape = new Ellipse(
                    pen,
                    mouseEvent->pos(),
                    mouseEvent->pos()
                    );
                 break;
        }
        isDrawing = true;
        update();
    }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *mouseEvent) {
    qDebug() << "Press at" << mouseEvent->pos();
    qDebug() << "Move at" << mouseEvent->pos()
             << " handleIndex=" << handleIndex
             << " resizing=" << resizing
             << " moving=" << moving;

    QPoint mousePos = mouseEvent->pos();
    if (isDrawing) {
        currentShape->setEndPoint(mousePos);
        update();
    }else if(objectSelected){
        if (resizing) {
            selectedShape->resize(mousePos, handleIndex);
            qDebug() << "Resizing handle" << handleIndex;

        } else if (moving) {
            QPoint delta = mousePos - lastPos;
            selectedShape->move(delta);
            lastPos = mousePos;
            qDebug() << "Moving by" << delta;

        }
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *mouseEvent) {
    qDebug() << "Press at" << mouseEvent->pos();
    qDebug() << "Move at" << mouseEvent->pos()
             << " handleIndex=" << handleIndex
             << " resizing=" << resizing
             << " moving=" << moving;

    if (mouseEvent->button() ) {
        moving = false;
        resizing = false;
        handleIndex=-1;

        if(Qt::LeftButton && isDrawing){
        currentShape->setEndPoint(mouseEvent->pos());
        isDrawing = false;
        update();
        displayList.push_back(currentShape);
        }
    }
}

void Canvas::selectColor(QAction * colorAction) {
    if (colorAction == pinkAction) {
        currentColor = QColor(254, 1, 154);
    } else if (colorAction == blueAction) {
        currentColor = Qt::blue;
    }
    if(objectSelected){
        selectedShape->setColor(currentColor);
        update();
    }
}

void Canvas::selectStyle(QAction * styleSelected) {
    if (styleSelected == solidLine) {
        currentStyle = Qt::SolidLine;
    } else if (styleSelected == dashLine) {
        currentStyle = Qt::DashLine;
    } else if (styleSelected == dotLine) {
    currentStyle = Qt::DotLine;
    }
    if(objectSelected){
        selectedShape->setStyle(currentStyle);
        update();
    }
}

void Canvas::selectShape(QAction *shapeSelected) {
    if (shapeSelected == lineAction) {
        currentShapeType = ShapeType::Line;
    } else if (shapeSelected == rectAction) {
        currentShapeType = ShapeType::Rectangle;
    } else if (shapeSelected == ellipseAction) {
        currentShapeType = ShapeType::Ellipse;
    }
}

void Canvas::selectWidth(int width) {
    currentWidth = width;
    if(objectSelected){
        selectedShape->setWidth(currentWidth);
        update();
    }
}

void Canvas::setSelect(){
    selectOption = !selectOption;
    if (!selectOption){
        selectedShape=nullptr;
        objectSelected=false;
    }
}

