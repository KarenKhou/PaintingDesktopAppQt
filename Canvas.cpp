#include "Canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QAction>
#include <QColor>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    isDrawing(false),
    currentColor(Qt::black),
    currentStyle(Qt::SolidLine),
    currentWidth(5),
    currentShapeType(ShapeType::Line)
{}

Canvas::~Canvas(){
    for (auto shape : displayList){
        delete shape;
    }
    displayList.clear();

    delete currentShape;
    currentShape = nullptr;
}

void Canvas::paintEvent(QPaintEvent * paintEvent){
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);

    if (isDrawing && currentShape) {
        currentShape->draw(painter);
    }

    for (auto shape :displayList){
        shape->draw(painter);
    }

}

void Canvas::mousePressEvent(QMouseEvent* mouseEvent){
    if (mouseEvent->button() == Qt::LeftButton) {
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

void Canvas::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (isDrawing) {
        currentShape->setEndPoint(mouseEvent->pos());
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton && isDrawing) {
        currentShape->setEndPoint(mouseEvent->pos());
        isDrawing = false;
        update();
        displayList.push_back(currentShape);
    }
}

void Canvas::selectColor(QAction * colorAction) {
    if (colorAction == pinkAction) {
        currentColor = QColor(254, 1, 154);
    } else if (colorAction == blueAction) {
        currentColor = Qt::blue;
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
}

