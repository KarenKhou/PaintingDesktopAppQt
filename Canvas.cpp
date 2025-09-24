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
    currentWidth(5)
{}

void Canvas::paintEvent(QPaintEvent * paintEvent){
    QWidget::paintEvent(paintEvent);
    QPainter painter(this);

    // if (isDrawing && currentShape) {
    //     painter.setPen(currentShape->pen);
    //     painter.drawLine(currentShape->startPoint, currentShape->endPoint);
    // }

    for (auto shape :savedLines){
        painter.setPen(shape->pen);

        // painter.drawLine(shape->startPoint, shape->endPoint);
        // painter.drawRect(QRect(shape->startPoint,shape->endPoint));

        switch (shape->type) {
        case Shape::Line:
            painter.drawLine(shape->startPoint, shape->endPoint);
            break;
        case Shape::Rectangle:
            painter.drawRect(QRect(shape->startPoint, shape->endPoint));
            break;
        case Shape::Ellipse:
            painter.drawEllipse(QRect(shape->startPoint, shape->endPoint));
            break;
        }
    }



}

void Canvas::mousePressEvent(QMouseEvent* mouseEvent){
    if (mouseEvent->button() == Qt::LeftButton) {
        currentShape = new Shape();
        QPen pen;
        pen.setColor(currentColor);
        pen.setStyle(currentStyle);
        pen.setWidth(currentWidth);
        currentShape->startPoint = mouseEvent->pos();
        currentShape->endPoint = mouseEvent->pos();
        currentShape->pen = pen;
        isDrawing = true;
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *mouseEvent) {
    if (isDrawing) {
        currentShape->endPoint = mouseEvent->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *mouseEvent) {
    if (mouseEvent->button() == Qt::LeftButton && isDrawing) {
        currentShape->endPoint = mouseEvent->pos();
        currentShape->type= currentShapeType;
        isDrawing = false;
        update();
        savedLines.push_back(currentShape);
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
        currentShapeType = Shape::Line;
    } else if (shapeSelected == rectAction) {
        currentShapeType = Shape::Rectangle;
    } else if (shapeSelected == ellipseAction) {
        currentShapeType = Shape::Ellipse;
    }
}



void Canvas::selectWidth(int width) {
    currentWidth = width;
}

